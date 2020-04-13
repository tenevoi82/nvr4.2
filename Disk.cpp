/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Disk.cpp
 * Author: tenevoi
 * 
 * Created on 26 марта 2020 г., 17:23
 */

#include <cstring>
#include <cstdio>
#include <experimental/filesystem>
#include <math.h>
#include <vector>

#include "Disk.h"
#include "ms.hpp"
namespace fs = std::experimental::filesystem;
using namespace std;


Disk::Disk(fs::path fullpath) {
    //    try {
    //        CutLastSlash(this->path, fullpath);
    //        
    //        printf("Dir - %s\r\n",this->path);
    //        if(fs::create_directories(this->path))
    //        {
    //            printf("The Directory %s was created suchesfull.\r\n",this->path);
    //        }
    //        GetDiskInfo();
    //    } catch (exception &e) {
    //        fprintf(stderr, "%s\r\n", e.what());
    //        exit(0);
    //    }
    //    PrintDiskInfo();
}

Disk::Disk(const char *fullpath) {
    try {
        CutLastSlash(this->path, fullpath);
        if (fs::create_directories(this->path)) {
            printf("The Directory %s was created suchesfull.\r\n", this->path);
        }
        UpdateDiskInfo();
    } catch (exception &e) {
        fflush(stdout);
        fprintf(stderr, "%s\r\n", e.what());
        exit(1);
    }
}

void Disk::PrintDiskInfo() {
    printf("Всего %s ", (char*) ms(this->info.totalSpaseSize));
    printf(" из них использованно %s ", (char*) ms(this->info.usedSpaceSize));
    printf(" и доступно %s\r\n", (char*) ms(this->info.aviableSpaceSize));
}

string Disk::GetDiskInfo() {
    std::string str;
    str = "Всего ";
    str = str + (char*)ms(this->info.totalSpaseSize);
    str = str + " из них использованно " + (char*)ms(this->info.usedSpaceSize);
    str = str + " и доступно " + (char*)ms(this->info.aviableSpaceSize) + "\r\n" ;
    return str;
}

//Disk::Disk(const Disk& orig) {
//}

Disk::~Disk() {
    delete this->path;
}

bool Disk::CutLastSlash(char* &dst, const char* src) {
    /*очистить все  слэши в конце*/
    if (src == NULL || src == nullptr)
        throw invalid_argument("source не может быть NULL");
    if (dst == src)
        throw invalid_argument("Указатели на source и dst совподают.");
    int len = strlen(src);
    if (!len)
        throw invalid_argument("source не может быть пустым");
    char* tmp = new char[len + 1];
    memcpy(tmp, src, len + 1);

    for (int i = len - 1; i > 0; i--)
        if (tmp[i] == '/')
            tmp[i] = 0;
        else {
            break;
        }
    len = strlen(tmp);
    dst = new char[len+1];
    for (int i = len+1; i >= 0; i--)
        dst[i] = tmp[i];
    delete tmp;
    return false;
}

bool Disk::UpdateDiskInfo() {
    fs::path p = this->path;
    fs::space_info info = fs::space(p);
    this->info.totalSpaseSize = info.capacity;
    this->info.aviableSpaceSize = info.available;
    this->info.usedSpaceSize = info.capacity - info.free;
}