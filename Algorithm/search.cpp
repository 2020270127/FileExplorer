#include <cstring>
#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

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
    return 0;

    
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

//테스토용
// int main() {
//     // 구조체 배열 초기화
//     Fileinfo arr[MAX_STRUCT_COUNT] = {
//         {"Hello World", 11},
//         {"This is a test", 14},
//         {"Goodbye", 7},
//         {"Programming", 11},
//         {"This is KMP algorithm", 13}
//     };

//     int arr_len = sizeof(arr) / sizeof(Fileinfo);

//     char pattern[MAX_PATTERN_LENGTH + 1];  // 패턴 문자열
//     printf("파일 이름을 입력하시오 : ");
//     scanf("%[^\n]", pattern);              // %[^\n] --> 패턴 문자열의 공백 제거

//     // 구조체 배열에서 패턴 문자열 찾기
//     for (int i = 0; i < arr_len; i++) {
//         if (kmp(arr[i].name, pattern)) {
//             std::cout<<arr[i].name<<" 파일은 "<<i+1<<"번째에 있습니다."<<std::endl;
//         }
//     }

//     return 0;
// } 
