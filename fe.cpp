#include "include/argparse.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <filesystem>

#define BUF_SIZE 4096
using namespace std;

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("FileExplorer");

    // Args list
    program.add_argument("-dir").default_value("./").help("target dir");
    program.add_argument("-mkdir").help("make dir"); //폴더 생성
    program.add_argument("-rm").help("remove file or dir"); //파일 혹은 폴더 삭제 
    program.add_argument("-touch").help("touch"); //파일 생성
    program.add_argument("-cp").help("copy src to dst"); //파일 혹은 폴더 복사
    program.add_argument("-mv").help("move and"); //이동
    program.add_argument("-sort").help("sort list [algorithm]"); //정렬
    program.add_argument("-ss").help("search by substring"); //검색


  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

    if (program.is_used("-rm")) {
    std::string path_to_remove = program.get<string>("-rm");

    try {
        if (std::filesystem::exists(path_to_remove)) {
            std::filesystem::remove_all(path_to_remove);
        } else {
            std::cerr << "Path not found: " << path_to_remove << std::endl;
            return 1;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error removing path: " << path_to_remove << ", error: " << ex.what() << std::endl;
        return 1;
    }
}
    
    else if (program.is_used("-dir")) {
        cout << program.get<string>("-dir");
    }
    else if (program.is_used("-mkdir")) {
        //mkdir
    }
    else if (program.is_used("-cp")) {
        //cp
    }
    else if (program.is_used("-sort")) {
        //sort
    }
    else if (program.is_used("-ss")) {
        //ss
    }

    exit(0);
}