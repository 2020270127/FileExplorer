#pragma once

#ifndef __FILESYSTEM__
#include <filesystem>
#endif

#ifndef __IOSTREAM__
#include <iostream>
#endif

#ifndef __SYS_STAT_H__
#include <sys/stat.h>
#endif

#ifndef KMP
#define KMP 0
#endif

#ifndef STRSTR
#define STRSTR 1
#endif

namespace fs = std::filesystem;
struct FileInfo {
    std::string name;
    std::string path;
    uintmax_t size;
    bool is_directory;
    std::time_t modified_time;
    struct stat st;
};

int getSize(fs::path path);

int printSortedArr(char method, char standard);

int printSearchedInDir(fs::path const &dirpath, std::string pattern,
                       int method);

FileInfo *getInfoArray();
FileInfo *getInfo(fs::path filepath);

void searchFile(const fs::path &p, const std::string &target, int method,
                int algorithm);

void printInfo(FileInfo *info_array, int size);
void printAInfo(FileInfo *info_array);