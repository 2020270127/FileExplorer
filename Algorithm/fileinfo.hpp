#pragma once
#include <string>
#include <sys/stat.h>

#define KMP 0
#define STRSTR 1

namespace fs = std::filesystem;
struct FileInfo {
    std::string name;
    uintmax_t size;
    bool is_directory;
    std::time_t modified_time;
};

template <typename T> void printInfo(T *info_array, int size) {
    const int fieldWidth = 27;

    for (int i = 0; i < size; i++) {
        std::ostringstream oss;

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
}

int getSize();

int getSize(fs::path path);

int printSortedArr(char method, char standard);

int printSearchedInDir(fs::path const &dirpath, string pattern, int method);

FileInfo *getInfoArray();
