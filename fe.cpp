#include <filesystem>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 4096
using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: fe [command] -d [dirname]\n");
        exit(0);
    }

    exit(0);
}