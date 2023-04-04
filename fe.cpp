#include "include/argparse.hpp"
#include <filesystem>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 4096
using namespace std;

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("FileExplorer");

    // Args list
    program.add_argument("-dir").default_value("./").help("target dir");
    program.add_argument("-mkdir").help("make dir");
    program.add_argument("-rm").help("remove file or dir");
    program.add_argument("-touch").help("touch");
    program.add_argument("-cp").help("copy src to dst");
    program.add_argument("-mv").help("move and");
    program.add_argument("-sort").help("sort list [algorithm]");
    program.add_argument("-ss").help("search by substring");

    program.parse_args(argc, argv);

    if(program.is_used("-rm")){

    }
    else if(program.is_used("-dir")){
        printf("%s", program.get<string>("-dir"));
    }


    exit(0);
}