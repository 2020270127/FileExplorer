#ifndef __CSTRING__
#include <cstring>
#endif

#ifndef __FILESYSTEM__
#include <filesystem>
#endif

#ifndef __IOSTREAM__
#include <iostream>
#endif

#ifndef __STRING__
#include <string>
#endif

#ifndef __QUEUE__
#include <queue>
#endif

#ifndef __UNORDERED_SET__
#include <unordered_set>
#endif

#ifndef __VECTOR__
#include <vector>
#endif

#ifndef __FILEINFO_HPP__
#include "fileinfo.hpp"
#endif

namespace fs = std::filesystem;
using namespace std;

#define MAX_STRING_LENGTH 100  // 파일이름의 최대 길이
#define MAX_PATTERN_LENGTH 100  // 찾을 파일이름의 최대 길이
#define MAX_STRUCT_COUNT 100   // 파일정보 구조체 배열의 최대 크기


int strstr(string str, string key){
    int keyptr = 0;
    while (keyptr + key.length() <= str.length()) {
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
    while (keyptr + strlen(key) <= strlen(str)) {
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
    return -1;
}



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
            j = fail[j];           
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
            j = fail[j];           
        }
        if (text[i] == pattern[j]) {
            if (++j == pattern.length()) {
                return true;
            }
        }
    }

    return false;
}

void drecursive_k(const fs::path& p, const std::string& target) {
    for (const auto& entry : fs::directory_iterator(p)) {
        if (entry.is_directory()) {
            if (kmp(entry.path().filename().string(), target))
                printAInfo(getInfo(entry.path()));
            drecursive_k(entry.path(), target);
        } else{
            if (kmp(entry.path().filename().string(), target)) {
                printAInfo(getInfo(entry.path()));
            } 
        }
    }
}

void drecursive_s(const fs::path& p, const std::string& target) {
    for (const auto& entry : fs::directory_iterator(p)) {
        if (entry.is_directory()) {
            if (strstr(entry.path().filename().string(), target) != -1) 
                printAInfo(getInfo(entry.path()));
            drecursive_s(entry.path(), target);
            
        } else {
             if (strstr(entry.path().filename().string(), target) != -1) {
                printAInfo(getInfo(entry.path()));
            }
        }
    }
}

void dfs(const fs::path& p, const std::string& target, int method) {
    switch(method){
        case KMP:
            drecursive_k(p,target);
            break;
        case STRSTR:
            drecursive_s(p,target);
            break;
        default:
            cout << "dfs method error" << endl;
            return;
    }
}
queue<fs::path> que;// 큐는 항상 유지
void bfs(const fs::path& p, const std::string& target, int method) {
    
	std::error_code ec; //예외사항을 잡아내기위한 클래스
	fs::directory_iterator iter(p, ec);
    
   	//만약 값이 없다면, 함수종료
    	//참고로, std::error_code의 value함수는 예외사항이 발생하면 0이 아닌 값을 반환합니다.
	if (ec.value() != 0) return ;

	for (auto& i = iter; i != fs::end(iter); i++) {// 디렉토리내의 for문 
		switch(method){
        case KMP:
            if (kmp(i->path().filename().string(), target)){
                printAInfo(getInfo(i->path())); // memory leak!
            }
            break;
        case STRSTR:
            if (strstr(i->path().filename().string(), target) != -1){
                printAInfo(getInfo(i->path()));
            }
            break;
        }   
    	//만약 폴더인경우, 해당경로로 큐에 push하여 대기열 저장
		if (i->is_directory()){
            que.push(i->path());
        }
    }
	if (que.empty())
		return;
	else if(!que.empty()){
		fs::path nextDir = que.front();
		que.pop();
		if(fs::exists(nextDir))  bfs(nextDir, target, method); // 큐 순서대로 큐 빌때까지 반복 //memory leaked
	}
}




