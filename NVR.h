/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NVR.h
 * Author: tenevoi
 *
 * Created on 1 апреля 2020 г., 16:02
 */

#ifndef NVR_H
#define NVR_H

#include <vector>
#include <functional>
#include <experimental/bits/fs_path.h>

#include "Disk.h"
#include "Recorder.h"

namespace fs = std::experimental::filesystem;
using namespace std;

class NVR {
public:
    NVR();
    NVR(const NVR& orig);
    virtual ~NVR();
    bool AddDisk(const char* diskPath);
    string GetAllDiskInformation(); 
    bool SetRecorder(Recorder *rec);    
private:
    std::vector<Disk*> disks;
    Recorder *recorder = nullptr;
    static bool ResivedDataFromRecorder(NVR *nvr, uint64_t begin,uint64_t end,uint64_t size, uint8_t videoData);    
};

#endif /* NVR_H */

