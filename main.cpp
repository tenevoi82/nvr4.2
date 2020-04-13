/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: tenevoi
 *
 * Created on 26 марта 2020 г., 17:23
 */

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <thread>
//#include <functional>

#include "Disk.h"
#include "NVR.h"
#include "Recorder.h"

#include <thread>
#include <chrono>

using namespace std;

NVR nvr;
/*
 * 
 */

int main(int argc, char** argv) {
    system("systemctl restart ordinus_nvr");
    system("systemctl start ordinus_nvr");
    nvr.AddDisk("/var/www/video/archive/disk1/");
    nvr.AddDisk("/var/www/video/archive/disk2");
    cout << nvr.GetAllDiskInformation();
    Recorder *rec = new Recorder();
    
    rec->Work();
    
    //Disk sda("/var///www/video/archive/disk1///");
    //Disk sdb("/var/www/video/archive/disk2");
    
    //nvr.disks.push_back(Disk("/var///www/video/archive/disk1///"));
//    nvr.disks.push_back(sdb);
//    
//    sda.tmp = 1;
//    
//////    for (Disk &cur : nvr.disks) {
//////        std::cout << "disk " << cur.tmp << "\r\n";
//////    }
//    sda.tmp = 2;
//    Disk &g = *nvr.disks[0];
//    cout << "disk " << g.tmp << "\r\n";
//    int j = nvr.disks[0]->tmp;

    
    return 0;
}

