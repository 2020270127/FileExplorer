#include "search.hpp"
#include "sort.hpp"

#ifndef __CTIME__
#include <ctime>
#endif

#ifndef __FILESYSTEM__
#include <filesystem>
#endif

#ifndef __IOSTREAM__
#include <iostream>
#endif

#ifndef __SSTREAM__
#include <sstream>
#endif

#ifndef __SYS_STAT_H__
#include <sys/stat.h>
#endif

#ifndef DFS
#define DFS 0
#endif

#ifndef BFS
#define BFS 1
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

void printInfo(FileInfo *info_array, int size) {
    const int fieldWidth = 25;

    for (int i = 0; i < size; i++) {
        std::ostringstream oss;
      
        oss << "Name: " << std::left << std::setw(fieldWidth)
            << info_array[i].name << "Size: " << std::left
            << std::setw(fieldWidth) << info_array[i].size
            << "Modified time: " << std::left
            << std::put_time(std::localtime(&(info_array[i].modified_time)),
                             "%c") <<std::endl
            << "Type: " << std::left << std::setw(fieldWidth)
            << (info_array[i].is_directory ? "directory" : "file")
            << "Path: " << std::left << std::setw(fieldWidth)
            << info_array[i].path;
        std::cout << oss.str() << std::endl << std::endl;
    }
   
    delete[] info_array;
}

void printAInfo(FileInfo *info_array) {
    const int fieldWidth = 27;


    std::ostringstream oss;
    
    oss << "Name: " << std::left << std::setw(fieldWidth)
        << info_array->name << "Size: " << std::left
        << std::setw(fieldWidth) << info_array->size
        << "Modified time: " << std::left
        << std::put_time(std::localtime(&(info_array->modified_time)),
                            "%c") <<std::endl
        << "Type: " << std::left << std::setw(fieldWidth)
        << (info_array->is_directory ? "directory" : "file")
        << "Path: " << std::left << std::setw(fieldWidth)
            << info_array->path;

    std::cout << oss.str() << std::endl << std::endl;

   
    delete info_array;
}



int getSize(fs::path path) {
    int file_count = 0;
    for (auto &entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file() || entry.is_directory()) {
            file_count++;
        }
    }
    return file_count;
}

FileInfo *getInfoArray() {
    int file_count = getSize(fs::current_path());

    FileInfo *info_array = new FileInfo[file_count];
    int i = 0;

    for (auto &entry : fs::directory_iterator(fs::current_path())) {
        if (entry.is_regular_file() || entry.is_directory()) {
            info_array[i].name = entry.path().filename().string();
            info_array[i].size = entry.is_directory() ? 0 : entry.file_size();
            if(stat(entry.path().c_str(),&info_array->st) != 0){
                 std::cout << "Failed to get file status" << std::endl;
            }
            info_array[i].modified_time = info_array->st.st_mtime;
            info_array[i].is_directory = entry.is_directory();
            info_array[i].path = entry.path().string();
            i++;
        }
    }
    return info_array;
}

FileInfo *getInfo(fs::path filepath) {

    
    FileInfo *info = new FileInfo; 
    fs::directory_entry entry = fs::directory_entry(filepath);

    if (entry.is_regular_file() || entry.is_directory()) {
        info->name = entry.path().filename().string(); 
        info->size = entry.is_directory() ? 0 : entry.file_size();
            if (stat(entry.path().c_str(), &(info->st)) != 0) {
            std::cout << "Failed to get file status" << std::endl;
        }
        info->modified_time = info->st.st_mtime;
        info->is_directory = entry.is_directory();
        info->path = entry.path().string();
    }

    return info;
}





int printSortedArr(char method, char standard) {
    FileInfo *arr = getInfoArray();
    int size = getSize(fs::current_path());

    switch (method) {
    case 'q':
        switch (standard) {
        case 't':
            quick_sort(arr, 0, size - 1, &FileInfo::modified_time, comp<int>);
            break;
        case 's':
            quick_sort(arr, 0, size - 1, &FileInfo::size, comp<int>);
            break;
        case 'n':
            quick_sort(arr, 0, size - 1, &FileInfo::name, comp<string>);
            break;

        default:
            return -1;
        }
        break;

    case 'm':
        switch (standard) {
        case 't':
            merge_sort(arr, 0, size - 1, &FileInfo::modified_time, comp<int>);
            break;
        case 's':
            merge_sort(arr, 0, size - 1, &FileInfo::size, comp<int>);
            break;
        case 'n':
            merge_sort(arr, 0, size - 1, &FileInfo::name, comp<string>);
            break;

        default:
            return -1;
        }
        break;

    case 'h':
        switch (standard) {
        case 't':
            heap_sort(arr, size, &FileInfo::modified_time, comp<int>);
            break;
        case 's':
            heap_sort(arr, size, &FileInfo::size, comp<int>);
            break;
        case 'n':
            heap_sort(arr, size, &FileInfo::name, comp<string>);
            break;
        default:
            return -1;
        }
        break;
    default:
        return -1;
    }
    printInfo(arr, size);
    return 0;
}

int printSearchedInDir(fs::path const &dirpath, string pattern, int method) {
    for (const auto &entry : fs::directory_iterator(dirpath)) {
        if (entry.is_directory())
            continue; // 디렉토리는 skip
        switch(method){
            case KMP:
                if (kmp(entry.path().filename().string(), pattern))
                    printInfo(getInfo(entry.path()), 1);
            break;
            case STRSTR:
                if (strstr(entry.path().filename().string(), pattern) != -1)
                    printInfo(getInfo(entry.path()), 1);
            break;
            default:
                cout << "Wrong Search Method" << endl;
                return -1;
            break;
        }   
    }
    return 0;
}

void searchFile(const fs::path& p, const std::string& target, int method, int algorithm){
    switch(method){
        case BFS:
            bfs(p, target,algorithm);
            break;
        case DFS:
            dfs(p, target,algorithm);
        break;
        default:
            cout<<"Wrong search method"<<endl;
    }
}

