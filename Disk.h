/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Disk.h
 * Author: tenevoi
 *
 * Created on 26 марта 2020 г., 17:23
 */

#ifndef DISK_H
#define DISK_H

#include <vector>
#include <cstdint>
#include <stddef.h>
#include <experimental/filesystem>
#include <openssl/opensslconf.h>

using namespace std;

class Disk {
public:
    int tmp = 0;
    Disk(const char *path);
    
    Disk(std::experimental::filesystem::path fullpath);
   // Disk(const Disk& orig);
    virtual ~Disk();

    struct Channel {
        int channelNumber;
        char channelName[128] = {0,};
        uint64_t firstStartTime;
        uint64_t firstStartFile;
        uint64_t lastEndTime;
        uint64_t lastEndFile;
    };

    struct DiskInfo {
        uint64_t usedSpaceSize =0;
        uint64_t aviableSpaceSize =0;
        uint64_t totalSpaseSize=0;
    };

    struct File {
        char fullPath[128] = {0,};
        bool finished;
        bool opened;
        uint64_t size;

        struct Fragment {
            int channelNumber;
            bool saved;
            bool saveinprogress;
            uint64_t beginposition;
            uint64_t endposition;
            uint64_t size;
            uint64_t begintime;
            uint64_t endtime;
            double duration;
            char *data = NULL;
        };
        std::vector<Fragment> fragmetsData;

        struct SavedData {
            int version;
            int channelCount;
            uint64_t startPositionData;

            struct ChannelDiscription {
                int channelNumber;
                uint64_t firstStartFragmentTime;
                uint64_t firstStartFragmentPosition;
                uint64_t fragmentsCount;
            };
            ChannelDiscription * chDescriptions;
            
            struct FragmentsDescription {
                uint64_t startPozition;
                uint64_t endPozition;
                uint64_t size;
            };
            FragmentsDescription * frDescriptions;
        };
    };
    char * path =NULL;
    std::vector<File> videoDataFiles;
    std::vector<Channel> channels;
    DiskInfo info;
    void PrintDiskInfo();
    string GetDiskInfo();
private:

    /*cut last slsh from path*/
    bool CutLastSlash(char* &dst, const char* src);
    bool UpdateDiskInfo();

};

#endif /* DISK_H */

