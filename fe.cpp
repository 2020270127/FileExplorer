#include "include/argparse.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
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
  }

    if (program.is_used("-rm")) {  //파일 삭제기능, 강제 삭제 디폴트
    std::string path_to_remove = program.get<string>("-rm");

    try {
        if (std::filesystem::exists(path_to_remove)) {
            std::filesystem::remove_all(path_to_remove);
        } else {
            std::cerr << "Path not found: " << path_to_remove << std::endl;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error removing path: " << path_to_remove << ", error: " << ex.what() << std::endl;
    }
}
    
    else if (program.is_used("-dir")) { //현재 경로 출력
        cout << program.get<string>("-dir");
    }

    else if (program.is_used("-mkdir")) { // 폴더 생성
    std::string path_to_create = program.get<string>("-mkdir");
    try {
        if (std::filesystem::create_directory(path_to_create)) {
            std::cout << "Directory created: " << path_to_create << std::endl;
        } else {
            std::cerr << "Directory already exists: " << path_to_create << std::endl;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error creating directory: " << path_to_create << ", error: " << ex.what() << std::endl;
      }

    }
    else if (program.is_used("-touch")) { //파일 생성
    std::string file_path = program.get<string>("-touch");
    try {
        std::ofstream file(file_path);
        if (file.is_open()) {
            file.close();
            std::cout << "File created: " << file_path << std::endl;
        } else {
            std::cerr << "Error creating file: " << file_path << std::endl;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error creating file: " << file_path << ", error: " << ex.what() << std::endl;
    }
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