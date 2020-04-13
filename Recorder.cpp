/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Recorder.cpp
 * Author: tenevoi
 * 
 * Created on 2 апреля 2020 г., 11:53
 */

#include "Recorder.h"

#include <sys/types.h>        
#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/ip.h>

#include <string.h>

#include <thread>
#include <chrono>
#include <iostream>
#include <unistd.h>
#include <mutex>
#include <experimental/filesystem>
#include <cstdio>
#include <cstdlib>
#include "DataFromFFMpeg.hpp"

using namespace std;
namespace fs = std::experimental::filesystem;

Recorder::Recorder() {
}

Recorder::Recorder(const Recorder& orig) {
}

Recorder::~Recorder() {
}

bool Recorder::NetInit() {
    struct sockaddr_in serv_addr;
    int enable = 1;
    int count = 0;
    mainSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mainSocket < 0)
        return true;
    memset((char *) &serv_addr, 0, sizeof (serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if (setsockopt(mainSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof (int)) < 0)
        return true;
    if (bind(mainSocket, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
        return true;
    }
    if (listen(mainSocket, SOMAXCONN) == -1)
        return 1;
    return false;
}

void ddd(){
    cout << "ddd OK\r\n";
}

void ResiveFromFF(int connectedSocket, std::mutex *m, DataFromFFMpeg * Data,void func(),Recorder * recorder) {
    DataFromFFMpeg &resivedData = *Data;
    size_t bufferSize = 4096;
    char buf[bufferSize];
    size_t resivedByte = read(connectedSocket, buf, bufferSize);
    close(connectedSocket);
    connectedSocket = -1;

    if (resivedByte == bufferSize || resivedByte == -1) {
        cerr << "Error1\r\n";
        m->unlock();
        return;
    }
    buf[resivedByte] = 0; //Добавим 0 для символа конца строки.
    if (sscanf(buf,
            "c:%s\ti:%d\tf:%s\ts:%Lf\td:%f\te:%Lf\tdir:%s",
            resivedData.camname, &resivedData.index, resivedData.filename,
            &resivedData.start, &resivedData.duration, &resivedData.end, resivedData.source_dir) == EOF) {
        cerr << "Error2\r\n";
        m->unlock();
        return;
    }
    fs::path t = resivedData.source_dir;
    t.append(resivedData.filename);
    std::uintmax_t sizeoffile = fs::file_size(t);
    char * filebuffer = new char[sizeoffile];

    //recorder->onResive(0,0,0,0);

    delete filebuffer;
    filebuffer = nullptr;
    cerr << "\r\ndeleting file (" << sizeoffile << ")" << t;
    int deltrycount = 10;
    fs::remove(t);
    cerr << " ok\r\n";
    func();
    int delay = rand() % 15;
    //this_thread::sleep_for(chrono::seconds(delay));
    m->unlock();
    return;
}

void Recorder::Work() {
    int max_connections = 30;
    using namespace std;
    port = 6000;
    if (NetInit()) {
        cout << "NetInit Error\r\n";
        cerr << strerror(errno);
        return;
    }
    thread * t[max_connections];
    mutex *m = new mutex[max_connections];
    int subsocket[max_connections];
    DataFromFFMpeg data[max_connections];
    cerr << "Resiving:\r\n";
    for (int i = 0; true; i++) {
        i = (i >= max_connections) ? 0 : i;
        if (!m[i].try_lock()) {
            //            cout << "tread " << i << " is locked, trying next thread \r";
            //            fflush(stdout);
            //this_thread::sleep_for(100ms);
            continue;
        } else {
            subsocket[i] = accept(mainSocket, 0, 0);
            //cerr << "Incoming new connection " << i << "\r\n";
            t[i] = new thread(ResiveFromFF, subsocket[i], &m[i], &data[i],ddd,this);
            t[i]->detach();
            //t[i]->join();   
        }

    }
}
