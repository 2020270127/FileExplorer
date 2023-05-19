#include <cstring>
#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <string>
#include <queue>
#include <unordered_set>
#include <vector>
namespace fs = std::filesystem;
using namespace std;
#define KMP 1
#define STRSTR 0
#define MAX_STRING_LENGTH 100  // 파일이름의 최대 길이
#define MAX_PATTERN_LENGTH 100  // 찾을 파일이름의 최대 길이
#define MAX_STRUCT_COUNT 100   // 파일정보 구조체 배열의 최대 크기


int strstr(string str, string key){
    int keyptr = 0;
    while (keyptr + key.length() < str.length()) {
        int same = 1;
        for (int i = 0; i < key.length(); i++) {
            if (str[keyptr + i] != key[i]) {
                same = 0;
                break;
            }
        }
        if (same) {
            return keyptr; // 같을 경우 keyptr 리턴
        }
        keyptr++;
    }
    return -1;

    
}

int strstr(char str[], char key[]) {
    // str에서 key 패턴을 탐색함. 슬라이딩 윈도우 알고리즘 이용
    int keyptr = 0;
    while (keyptr + strlen(key) < strlen(str)) {
        int same = 1;
        for (int i = 0; i < strlen(key); i++) {
            if (str[keyptr + i] != key[i]) {
                same = 0;
                break;
            }
        }
        if (same) {
            return keyptr; // 같을 경우 keyptr 리턴
        }
        keyptr++;
    }
    return 0;
}


// 테스트용 구조체 정의
typedef struct Fileinfo{
    char name[MAX_STRING_LENGTH + 1];  // 파일 이름
    int size;                          // 파일 크기
}Fileinfo;

// KMP 알고리즘 함수
bool kmp(char text[], char pattern[]) {

    int fail[strlen(pattern)];               // 실패 함수
    int j = 0;                               // 패턴 문자열의 인덱스

    // 실패 함수 구하기
    fail[0] = -1;       // 실패함수의 0인덱스의 값은 항상 -1
    for (int i = 1; i < strlen(pattern); i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = fail[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            fail[i] = ++j;
        } else {
            fail[i] = 0;
        }
    }

    // 문자열 검색하기
    j = 0;
    for (int i = 0; i < strlen(text); i++) {
        while (j > 0 && text[i] != pattern[j]) { 
            j = fail[j - 1];           
        }
        if (text[i] == pattern[j]) {
            if (++j == strlen(pattern)) {
                return true;
            }
        }
    }

    return false;
}

bool kmp(string text, string pattern) {

    int fail[pattern.length()];               // 실패 함수
    int j = 0;                               // 패턴 문자열의 인덱스

    // 실패 함수 구하기
    fail[0] = -1;       // 실패함수의 0인덱스의 값은 항상 -1
    for (int i = 1; i < pattern.length(); i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = fail[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            fail[i] = ++j;
        } else {
            fail[i] = 0;
        }
    }

    // 문자열 검색하기
    j = 0;
    for (int i = 0; i < text.length(); i++) {
        while (j > 0 && text[i] != pattern[j]) { 
            j = fail[j - 1];           
        }
        if (text[i] == pattern[j]) {
            if (++j == pattern.length()) {
                return true;
            }
        }
    }

    return false;
}

void drecursive_k(const fs::path& p, const std::string& target, std::vector<std::string>& dic) {
    for (const auto& entry : fs::directory_iterator(p)) {
        if (entry.is_directory()) {
            if (kmp(entry.path().filename().string(), target)) {
                dic.push_back(entry.path().string());
            } else {
                drecursive_k(entry.path(), target, dic);
            }
        }
    }
}

void drecursive_s(const fs::path& p, const std::string& target, std::vector<std::string>& dic) {
    for (const auto& entry : fs::directory_iterator(p)) {
        if (entry.is_directory()) {
            if (strstr(entry.path().filename().string(), target) != -1) {
                dic.push_back(entry.path().string());
            } else {
                drecursive_s(entry.path(), target, dic);
            }
        }
    }
}

void dfs(const std::string& target, int method) {
    std::vector<std::string> dic;
    fs::path p = fs::current_path();
    switch(method){
        case KMP:
            drecursive_k(p,target,dic);
            break;
        case STRSTR:
            drecursive_s(p,target,dic);
    }
    
    for (const auto& folder : dic) {
        std::cout << folder << std::endl;
    }
}


void bfs(const std::string& keyword, int method) {
    std::queue<std::string> q;
    std::unordered_set<std::string> visited;

	const std::string& rootPath = fs::current_path();
    q.push(rootPath);
    visited.insert(rootPath);

    while (!q.empty()) {
        std::string currentPath = q.front();
        q.pop();

        // 현재 디렉토리에 대한 작업 수행
        std::cout << currentPath << std::endl;

        for (const auto& entry : fs::directory_iterator(currentPath)) {
            std::string entryPath = entry.path().string();

            if (entry.is_directory()) {
                if (visited.find(entryPath) == visited.end()) {
                    q.push(entryPath);
                    visited.insert(entryPath);
                }
            } else if (entry.is_regular_file()) {
				switch(method){
					case KMP:
						if (kmp(entryPath,keyword)) {
                    // 특정 문자열을 가지고 있는 파일을 찾았을 때 작업 수행
                    	std::cout << "Found: " << entryPath << std::endl;
						break;
					case STRSTR:
						if (strstr(entryPath,keyword)) {
                    // 특정 문자열을 가지고 있는 파일을 찾았을 때 작업 수행
                    	std::cout << "Found: " << entryPath << std::endl;
                }
                }
				}
                
            }
        }
    }
}




int main(){
	dfs("df",KMP); //working
    bfs("df",STRSTR); // not working
	return 0;
}
