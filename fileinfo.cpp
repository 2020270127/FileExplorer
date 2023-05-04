#include <iostream>
#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <ctime>
#include "include/sorting_ldkstellar.hpp"
using namespace std;
namespace fs = std::filesystem;

struct FileInfo {
    string name;
    string path;
    uintmax_t size;
    bool is_directory;
    std::time_t modified_time;
};

template <typename T>
void printInfo(T **info_array, int size) {
    for (int i = 0; i < size; i++) {
        cout << "Name: " << info_array[i]->name << endl;
        cout << "Path: " << info_array[i]->path << endl;
        cout << "Size: " << info_array[i]->size << endl;
        cout << "Modified time: " << std::asctime(std::localtime(&(info_array[i]->modified_time)))<<std::endl;
        cout << "Type: " << (info_array[i]->is_directory ? "directory" : "file") << endl;
        cout << endl;
    }
}

int getSize(){
    int file_count = 0;
    for (auto& entry : fs::directory_iterator(fs::current_path())) {
        if (entry.is_regular_file() || entry.is_directory()) {
            file_count++;
        }
    }
    return file_count;
}
FileInfo** getInfo() {
    int file_count = getSize();

    FileInfo **info_array = new FileInfo *[file_count];
    int i = 0;

    for (auto& entry : fs::directory_iterator(fs::current_path())) {
        if (entry.is_regular_file() || entry.is_directory()) {
            struct stat st;
            info_array[i] = new FileInfo;
            info_array[i]->name = entry.path().filename().string();
            info_array[i]->path = entry.path().string();
            info_array[i]->size = entry.is_directory() ? 0 : entry.file_size();
            if(stat(&(info_array[i]->name)[0],&st) != 0){
                 std::cout << "Failed to get file status" << std::endl;
            }
            info_array[i]->modified_time = st.st_mtime;
            info_array[i]->is_directory = entry.is_directory();
            i++;
        }
    }


    //**deleting array**

    // for (int i = 0; i < file_count; i++) {
    //     delete info_array[i];
    // }
    // delete[] info_array; 
    return info_array;

}
int main(){
    FileInfo** arr;
    arr = getInfo();
    int array_size = getSize();
    printInfo(arr, array_size);
    sorting(arr, 0, 0, array_size - 1); // 첫 번째 열(즉, name 속성)로 정렬
    printInfo(arr, array_size);
}
