#include <iostream>
#include <string>

using namespace std;

struct Data { // 테스트용 구조체
    int a;
    string b;
    int size;
};

bool cmp(const Data &d1, const Data &d2) {  //정렬기준을 구조체의 멤버 중 어느걸로 할 지 정하는 코드
    return d1.b < d2.b;     //테스트에서는 멤버 b를 기준으로 정렬
}

template <typename T>
void merge(T *arr, int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    T tmp[right - left + 1];

    while (i <= mid && j <= right) {
        if (cmp(arr[i], arr[j])) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = arr[i++];
    }
    while (j <= right) {
        tmp[k++] = arr[j++];
    }

    for (int p = 0; p < k; p++) {
        arr[left + p] = tmp[p];
    }
}

template <typename T>
void merge_sort(T *arr, int left, int right) {   //병합함수 구현 파트
    
    int mid = (left + right) / 2;
    
    if (left < right)  //배열의 원소가 1개이면 재귀함수종료
    {
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid); // 왼쪽 배열의 원소가 1개 될 때까지 나누는 작업
        merge_sort(arr, mid + 1, right); // 오른쪽 배열
        merge(arr, left, mid, right); // 왼쪽 배열과 오른쪽 배열 비교후 병합하는 작업
    }
}

// 테스트용 코드
int main() {
    Data arr[] = {
        {10, "apple", 5},
        {7, "banana", 3},
        {15, "orange", 8},
        {3, "grape", 2},
        {22, "pear", 6}
    };

    int n = sizeof(arr) / sizeof(Data); //배열의 크기

    merge_sort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << arr[i].a << " " << arr[i].b << " " << arr[i].size << endl;
    }

    return 0;
}
