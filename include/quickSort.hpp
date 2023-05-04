#include <iostream>
#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <ctime>

struct FileInfo {
    std::string name;
    std::string path;
    uintmax_t size;
    bool is_directory;
    std::time_t modified_time;
};

bool sizeCompare(const FileInfo& lhs, const FileInfo& rhs) {
    return lhs.size < rhs.size;
}
bool stringCompare(const FileInfo& lhs, const FileInfo& rhs) {
    return lhs.name < rhs.name;
}
bool timeCompare(const FileInfo& lhs, const FileInfo& rhs) {
    return lhs.modified_time < rhs.modified_time;
}

void quicksort(FileInfo* arr, int left, int right, char standard) {
    switch(standard){
        case 's': //size
            if (left < right) {
            int i = left, j = right;
            FileInfo tmp;
            FileInfo pivot = arr[(left + right) / 2];

            while (i <= j) {
                while (sizeCompare(arr[i], pivot))
                    i++;
                while (sizeCompare(pivot, arr[j]))
                    j--;
                if (i <= j) {
                    tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                    i++;
                    j--;
                }
            }
            if (left < j)
                quicksort(arr, left, j, 's');
            if (i < right)
                quicksort(arr, i, right, 's');
        }
        break;

        case 'n': //name
            if (left < right) {
            int i = left, j = right;
            FileInfo tmp;
            FileInfo pivot = arr[(left + right) / 2];

            while (i <= j) {
                while (stringCompare(arr[i], pivot))
                    i++;
                while (stringCompare(pivot, arr[j]))
                    j--;
                if (i <= j) {
                    tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                    i++;
                    j--;
                }
            }
            if (left < j)
                quicksort(arr, left, j, 'n');
            if (i < right)
                quicksort(arr, i, right, 'n');
        }
        break;

        case 't': //modified_time
            if (left < right) {
            int i = left, j = right;
            FileInfo tmp;
            FileInfo pivot = arr[(left + right) / 2];

            while (i <= j) {
                while (timeCompare(arr[i], pivot))
                    i++;
                while (timeCompare(pivot, arr[j]))
                    j--;
                if (i <= j) {
                    tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                    i++;
                    j--;
                }
            }
            if (left < j)
                quicksort(arr, left, j, 't');
            if (i < right)
                quicksort(arr, i, right, 't');
        }
        break;
    }
    
    
}
