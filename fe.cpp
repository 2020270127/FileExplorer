#include "include/argparse.hpp"
#include "Algorithm/fileinfo.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <filesystem>

#define BUF_SIZE 4096
using namespace std;

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("FileExplorer");

    // Args list
    program.add_argument("-dir").default_value("./").help("print current location").nargs(0);
    program.add_argument("-mkdir").help("USAGE : -mkdir [FOLDERNAME to create]"); //폴더 생성
    program.add_argument("-rm").help("USAGE : -rm [WHAT to remove]"); //파일 혹은 폴더 삭제 
    program.add_argument("-touch").help("USAGE : -touch [FILENAME to create]"); //파일 생성
    program.add_argument("-cp").help("USAGE : -cp [WHAT to copy] [WHERE to copy]").nargs(2); //파일 혹은 폴더 복사
    program.add_argument("-mv").help("USAGE : -mv [WHAT to move] [WHERE to move]").nargs(2); //이동
    program.add_argument("-sort").help("USAGE : -sort [q for quick, m for merge, h for heap] [n for name, s for size, t for time]").nargs(2); //정렬
    program.add_argument("-ss").help("USAGE : -ss [dfs or bfs] [kmp or strstr] [what to search]").nargs(3);
    program.add_argument("-path").help("where to search").nargs(1); //검색

   
  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
  }
    
    if (program.is_used("-dir")) { //현재 경로 출력
        cout << filesystem::current_path() << endl;
    }

    else if (program.is_used("-rm")) {  //파일 삭제기능, 강제 삭제 디폴트
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

    namespace fs = std::filesystem;


    std::string file_name = program.get<std::vector<string>>("-cp")[0];
    
    std::string destination_path = program.get<std::vector<string>>("-cp")[1];

    fs::path source = fs::current_path();
    fs::path destination(destination_path);

    if (!fs::exists(source / file_name)) // 소스 경로에 파일이나 폴더가 존재하지 않는 경우
    {
        std::cout << "Cannot copy file or folder: " << source / file_name << " (not found)" << std::endl;
        return 1;
    }

    try
    {
        if (fs::is_directory(source / file_name)) // 폴더를 복사하는 경우
        {
            fs::create_directories(destination / file_name);
            for (const auto& file : fs::recursive_directory_iterator(source / file_name))
            {
                fs::path current(file.path());
                fs::path target(destination / file_name / current.lexically_relative(source / file_name));
                if (fs::is_directory(current)) // 하위 폴더를 만들어줌
                {
                    fs::create_directory(target);
                }
                else // 파일을 복사함
                {
                    fs::copy_file(current, target, fs::copy_options::overwrite_existing);
                }
            }
        }
        else // 파일을 복사하는 경우
        {
            fs::copy_file(source / file_name, destination / file_name, fs::copy_options::overwrite_existing);
        }

        std::cout << "File or folder copied successfully" << std::endl;
        return 0;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
}

    else if (program.is_used("-mv")) {

    namespace fs = std::filesystem;

    std::string file_name = program.get<std::vector<string>>("-mv")[0];
    std::string destination_path = program.get<std::vector<string>>("-mv")[1];

    fs::path current_path = fs::current_path();
    fs::path source_file = current_path / file_name;
    fs::path destination_file = current_path / destination_path / file_name;

    try {
        fs::rename(source_file, destination_file);
        std::cout << "File moved successfully!" << std::endl;
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
    }
}


    

    else if (program.is_used("-sort")) {
        auto sortArgs = program.get<std::vector<std::string>>("-sort");
        char method = sortArgs[0][0];
        char algorithm = sortArgs[1][0];
      
        if(printSortedArr(method,algorithm) == -1){
            cout<<"wrong argument"<<endl;
        }
        //sort
    }
    
    else if (program.is_used("-ss")) {
        auto sortArgs = program.get<std::vector<std::string>>("-ss");
        auto Path = program.get<std::vector<std::string>>("-path");

        int method = sortArgs[0] == "DFS" ? 0:1;
        int algorithm = sortArgs[1] == "KMP" ? 0:1;
        std::string pattern = sortArgs[2];
        std::string path = Path.empty() ? std::filesystem::current_path().string() : Path[0];

        searchFile(path, pattern, method, algorithm);
        //method >> kmp or strstr , algorithm >> dfs or bfs
        //./fe -ss KMP DFS "df"  
        //ss
    }

    exit(0);
}
