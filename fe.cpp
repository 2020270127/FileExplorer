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
            cout << "-rm used";
    } 
    else if (program.is_used("-dir")) {
        cout << program.get<string>("-dir");
    }
    else if (program.is_used("-mkdir")) {
        cout << program.get<string>("-dir");
    }
    else if (program.is_used("-cp")) {
        cout << program.get<string>("-dir");
    }
    else if (program.is_used("-sort")) {
        cout << program.get<string>("-dir");
    }
    else if (program.is_used("-ss")) {
        cout << program.get<string>("-dir");
    }

    exit(0);
}