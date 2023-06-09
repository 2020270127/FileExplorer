#include "search.hpp"
#include "sort.hpp"
#include <ctime>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <sys/stat.h>

#define DFS 0
#define BFS 1

namespace fs = std::filesystem;

struct FileInfo {
    std::string name;
    // std::string path;
    uintmax_t size;
    bool is_directory;
    std::time_t modified_time;
};

void printInfo(FileInfo *info_array, int size) {
    const int fieldWidth = 27;

    for (int i = 0; i < size; i++) {
        std::ostringstream oss;
        // memcpy(&info_array[i].modified_time, nullptr, sizeof(info_array[i].modified_time));

        oss << "Name: " << std::left << std::setw(fieldWidth)
            << info_array[i].name << "Size: " << std::left
            << std::setw(fieldWidth) << info_array[i].size
            << "Modified time: " << std::left
            << std::put_time(std::localtime(&(info_array[i].modified_time)),
                             "%c")
            << "         Type: " << std::left << std::setw(fieldWidth)
            << (info_array[i].is_directory ? "directory" : "file");

        std::cout << oss.str() << std::endl << std::endl;
    }
   
    delete[] info_array;
}

void printAInfo(FileInfo *info_array) {
    const int fieldWidth = 27;


    std::ostringstream oss;
    // memcpy(&info_array[i].modified_time, nullptr, sizeof(info_array[i].modified_time));

    oss << "Name: " << std::left << std::setw(fieldWidth)
        << info_array->name << "Size: " << std::left
        << std::setw(fieldWidth) << info_array->size
        << "Modified time: " << std::left
        << std::put_time(std::localtime(&(info_array->modified_time)),
                            "%c")
        << "         Type: " << std::left << std::setw(fieldWidth)
        << (info_array->is_directory ? "directory" : "file");

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
            struct stat st;
            info_array[i].name = entry.path().filename().string();
            // info_array[i].path = entry.path().string();
            info_array[i].size = entry.is_directory() ? 0 : entry.file_size();
            // if (stat(&(info_array[i].name)[0], &st) != 0) {
            //     std::cout << "Failed to get file status" << std::endl;
            // }
            info_array[i].modified_time = st.st_mtime;
            info_array[i].is_directory = entry.is_directory();
            i++;
        }
    }
    return info_array;
}

FileInfo *getInfo(fs::path filepath) {

    
    FileInfo *info = new FileInfo; // memory leak
    fs::directory_entry entry = fs::directory_entry(filepath);

    if (entry.is_regular_file() || entry.is_directory()) {
        struct stat st;
      
        info->name = entry.path().filename().string(); //memory leak!
        
        // info_array[i].path = entry.path().string();
        info->size = entry.is_directory() ? 0 : entry.file_size();
        // if (stat(&(info->name)[0], &st) != 0) {
        //     std::cout << "Failed to get file status" << std::endl;
        // }
        info->modified_time = st.st_mtime;
        info->is_directory = entry.is_directory();
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
            // case 'p' : quick_sort(arr, 0, size-1,&FileInfo::path
            // ,comp<string>);
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
            // case 'p' : merge_sort(arr, 0, size-1,&FileInfo::path
            // ,comp<string>);
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
            // case 'p' : heap_sort(arr, size, &FileInfo::path ,comp<string>);
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
                if (kmp(entry.path().filename().string(), pattern) != -1)
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
        // std::cout << entry.path().filename().string() << std::endl; // 파일명 출력
    }
    return 0;
}

void searchFile(const fs::path& p, const std::string& target, int method, int algorithm){
    switch(algorithm){
        case BFS:
            bfs(p, target,method);
            break;
        case DFS:
            dfs(p, target,method);
        break;
        default:
            cout<<"Wrong search algoritm"<<endl;
    }
}

// int main() { // test code
//     string path = "./";
//     printSearchedInDir(path, "li", KMP);
// }
