/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Recorder.h
 * Author: tenevoi
 *
 * Created on 2 апреля 2020 г., 11:53
 */

#ifndef RECORDER_H
#define RECORDER_H

#include <cstdint>
#include "DataFromFFMpeg.hpp"


class Recorder {
public:
    Recorder();
    Recorder(const Recorder& orig);
    virtual ~Recorder();
    void Work();
    void (*onResive)(DataFromFFMpeg * data);
private:
    //void ResiveFromFF(DataFromFFMpeg &resivedData, int);
    virtual bool NetInit();
    uint8_t * videoData = nullptr;
    bool mComplited = false;
    int port = 6000;
    char buffer[1024]={0,};
    bool online;
    int mainSocket=0;
};

#endif /* RECORDER_H */

