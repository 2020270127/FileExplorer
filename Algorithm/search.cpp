#include <cstring>
#include <filesystem>
#include <iostream>
// template 사용하여 여러 type에 대응 가능하도록 함수 설계

template <typename T> void swap(T *a, T *b) {
    T *tmp = a;
    a = b;
    b = tmp;
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
}
