/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NVR.cpp
 * Author: tenevoi
 * 
 * Created on 1 апреля 2020 г., 16:02
 */

#include <vector>
#include <iostream>
#include <experimental/filesystem>

#include "NVR.h"
#include "Disk.h"

using namespace std;
namespace fs = std::experimental::filesystem;

NVR::NVR() {
}

NVR::NVR(const NVR& orig) {
}

NVR::~NVR() {
}


bool NVR::AddDisk(const char* diskPath) {
    Disk *newdisk = new Disk(diskPath);
    disks.push_back(newdisk);
    return false;
}

string NVR::GetAllDiskInformation() {
    string info = "Number of drives = ";
    info = info + to_string( disks.size());
    info = info +"\r\n";
    int disknumber = 0;
    for (Disk* &elem : disks) {
        disknumber++;
        info = info + "Drive №" + to_string(disknumber) + ": ["+elem->path+"]\r\n";
        info = info + elem->GetDiskInfo();
    }
    return info;

}

bool NVR::SetRecorder(Recorder* rec){
    this->recorder = rec;
    //rec->onResive = [this](DataFromFFMpeg *data) mutable { disks.clear();};
    return false;
}

bool NVR::ResivedDataFromRecorder(NVR * nvr,uint64_t begin,uint64_t end,uint64_t size, uint8_t videoData){
    std::cout << "Resived Some Data ";
    return false;
 }