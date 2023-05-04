#include "include/quickSort.hpp"
using namespace std;
namespace fs = std::filesystem;



template <typename T>
void printInfo(T *info_array, int size) {
    for (int i = 0; i < size; i++) {
        cout << "Name: " << info_array[i].name << endl;
        cout << "Path: " << info_array[i].path << endl;
        cout << "Size: " << info_array[i].size << endl;
        cout << "Modified time: " << std::asctime(std::localtime(&(info_array[i].modified_time)))<<std::endl;
        cout << "Type: " << (info_array[i].is_directory ? "directory" : "file") << endl;
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
FileInfo* getInfo() {
    int file_count = getSize();

    FileInfo *info_array = new FileInfo[file_count];
    int i = 0;

    for (auto& entry : fs::directory_iterator(fs::current_path())) {
        if (entry.is_regular_file() || entry.is_directory()) {
            struct stat st;
            info_array[i].name = entry.path().filename().string();
            info_array[i].path = entry.path().string();
            info_array[i].size = entry.is_directory() ? 0 : entry.file_size();
            if(stat(&(info_array[i].name)[0],&st) != 0){
                 std::cout << "Failed to get file status" << std::endl;
            }
            info_array[i].modified_time = st.st_mtime;
            info_array[i].is_directory = entry.is_directory();
            i++;
        }
    } 
    return info_array;
}

int main(){
    FileInfo* info_array = getInfo();
    int file_count = getSize();
    // quicksort(info_array, 0, file_count - 1,'t'); //시간순 정렬
    // printInfo(info_array, file_count);
    
    // quicksort(info_array, 0, file_count - 1,'n'); //이름순 정렬
    // printInfo(info_array, file_count);

    quicksort(info_array, 0, file_count - 1,'s'); //크기순 정렬
    printInfo(info_array, file_count);

    delete[] info_array; //할당 해제

    //deleteArray(info_array,file_count);
}
