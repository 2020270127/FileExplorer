#include <filesystem>
#include <iostream>
#include <ctime>
#include "Algorithm/sort.hpp"
#include "Algorithm/fileinfo.hpp"
#include "Algorithm/search.hpp"
using namespace std;
int key = 0;
string pattern = "test"; //문자열 검증을 위한 값

std::string generateRandomString() {
    std::string chars = "abcdefghijklmnopqrstuvwxyz";
    std::string result;

    // 랜덤 시드 초기화
    static bool seedInitialized = false;
    if (!seedInitialized) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seedInitialized = true;
    }

    // 문자열 길이 50으로 설정
    while (result.length() < 50) {
        char randomChar = chars[std::rand() % chars.length()];
        result += randomChar;
    }

    key = std::rand() % 2;// "test"를 포함하는지 랜덤으로 결정
    if (key == 1) { //key 가 1이면 패턴을 포함하는 
        // "test"를 포함하는 경우, 랜덤한 위치에 삽입
        int position = std::rand() % (result.length() - 3);
        result.replace(position, 0, "test");
    }

    return result;
}// 문자열 검증을 위한 랜덤 문자열 함수

int main(){
    cout << "테스트 시작" << endl;
    //Sort 테스트
    // 임의의 구조체 배열 생성

    FileInfo fileArray[5]; // 구조체 배열을 선언합니다.
    std::time_t currentTime = std::time(nullptr);
    std::srand(static_cast<unsigned int>(currentTime));

    for (int i = 0; i < 5; ++i) {
        fileArray[i].name = "File" + std::to_string(rand());
        fileArray[i].size = std::rand() % 100000; 
        fileArray[i].is_directory = (std::rand() % 2 == 0);
        fileArray[i].modified_time = currentTime + (std::rand() % 3600);
    } //랜덤 구조체 생성

    // 3가지 정렬함수로 정렬 후 검사
    // quick_sort check
    quick_sort(fileArray, 0, 4, &FileInfo::modified_time, comp<int>);
    for (int i = 0; i < 4; i++) {
        if(fileArray[i].modified_time > fileArray[i+1].modified_time)
            printf("error on quick_sort(time)\n"); 
    }
    quick_sort(fileArray, 0, 4, &FileInfo::size, comp<int>);
    for (int i = 0; i < 4; i++) {
        if(fileArray[i].size > fileArray[i+1].size)
            printf("error on quick_sort(size)\n"); 
    }
    quick_sort(fileArray, 0, 4, &FileInfo::name, comp<string>);
    for (int i = 0; i < 4; i++) {
        if(fileArray[i].name > fileArray[i+1].name)
            printf("error on quick_sort(name)\n"); 
    }

    // merge_sort check
    merge_sort(fileArray, 0, 4, &FileInfo::modified_time, comp<int>);
    for (int i = 0; i < 4; i++) {
        if(fileArray[i].modified_time > fileArray[i+1].modified_time)
            printf("error on merge_sort(time)\n"); 
    }
    merge_sort(fileArray, 0, 4, &FileInfo::size, comp<int>);
    for (int i = 0; i < 4; i++) {
        if(fileArray[i].size > fileArray[i+1].size)
            printf("error on merge_sort(size)\n"); 
    }
    merge_sort(fileArray, 0, 4, &FileInfo::name, comp<string>);
    for (int i = 0; i < 4; i++) {
        if(fileArray[i].name > fileArray[i+1].name)
            printf("error on merge_sort(name)\n"); 
    }

    // head_sort check
    heap_sort(fileArray, 5, &FileInfo::modified_time, comp<int>);
    for (int i = 0; i < 4; i++) {
        if(fileArray[i].modified_time > fileArray[i+1].modified_time){
            printf("error on heap_sort(time)\n"); 
            printInfo(&fileArray[i],1);
            printInfo(&fileArray[i+1],1);
        }        
    }
    heap_sort(fileArray, 5, &FileInfo::size, comp<int>);
    for (int i = 0; i < 4; i++) {
        if(fileArray[i].size > fileArray[i+1].size){
            printf("error on heap_sort(size)\n"); 
            printInfo(&fileArray[i],1);
            printInfo(&fileArray[i+1],1);
        }
            
    }
    heap_sort(fileArray, 5, &FileInfo::name, comp<string>);
    for (int i = 0; i < 4; i++) {
        if(fileArray[i].name > fileArray[i+1].name)
        {
            printf("error on heap_sort(name)\n"); 
            printInfo(&fileArray[i],1);
            printInfo(&fileArray[i+1],1);
        }
            
    }

    for(int i = 0; i < 50; i++){
        string RandomString = generateRandomString();
    if(kmp(RandomString, pattern) + key  == 1) // key가 0이면 pattern이 없는 스트링
    {
        cout<<"kmp has error on string " + RandomString <<endl;
        cout<<kmp(RandomString, pattern)<<endl;
        cout<<key<<endl;
    }
        
    if((strstr(RandomString, pattern) == -1  && key == 1) || (strstr(RandomString,pattern)!=-1) && key == 0){
        cout<<"strstr has error on string " + RandomString <<endl;
        cout<<strstr(RandomString, pattern)<<endl;
        cout<<key<<endl;
        }
    }

    // STRSTR, KMP 테스트
    // 찾을 임의의 패턴 정하기
    // 특정 패턴이 포함된 문자열 케이스 생성
    // 패턴이 포함되지 않은 문자열 생성
    // 각 함수가 위 문자열에 적절한 값이 리턴되는 지 검사

    //DFS, BFS 검사
    // 최소 3단계 깊이의 폴더 구조 생성
    fs::path p = fs::current_path().string() + "\\..\\Algorithm\\test";
    cout << "DFS test" << endl;
    cout << p.string() << " path search" << endl;
    dfs(p, "df",KMP); //working
    

    cout << "BFS test" << endl;
    cout << p.string() << " path search" << endl;
    bfs(p, "hi", STRSTR); 

    // 깊이에 따라서 파일명 다르게 생성
    // DFS, BFS가 어떤 순서로 파일명을 출력하는지 검사
}
