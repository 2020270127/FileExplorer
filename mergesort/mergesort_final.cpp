#include <iostream>
#include <string>

using namespace std;

//파일정보 구조체 들어갈 자리
struct Fruit {
    int a;
    string b;
};

//파일정보 중 어떤 걸 기준으로 할 지 정하는 코드
bool compareA(const Fruit &f1, const Fruit &f2) {
    return f1.a < f2.a;
}

bool compareB(const Fruit &f1, const Fruit &f2) {
    return f1.b < f2.b;
}

//병합 정렬 구현
template <typename T>
void merge(T *arr, int left, int mid, int right, bool (*compare)(const T&, const T&)) {
    int i = left, j = mid + 1, k = 0;
    T tmp[right - left + 1];

    while (i <= mid && j <= right) {
        if (compare(arr[i], arr[j])) {
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
void merge_sort(T *arr, int left, int right, bool (*compare)(const T&, const T&)) {
    if (left >= right) {//배열의 원소가 1개이면 함수종료
        return;
    }
    int mid = (left + right) / 2;
    merge_sort(arr, left, mid, compare);
    merge_sort(arr, mid + 1, right, compare);
    merge(arr, left, mid, right, compare);
}

//TEST용 코드
int main() {
    Fruit arr[3];
    arr[0].a = 10;
    arr[0].b = "apple";
    arr[1].a = 5;
    arr[1].b = "banana";
    arr[2].a = 3;
    arr[2].b = "orange";

    cout << "sort by memebe of a"<<endl;
    merge_sort(arr, 0, 2, compareA);

    for (int i = 0; i < 3; i++) {
        cout << arr[i].a << ", " << arr[i].b << endl;
    }
    cout <<"\n";

    cout << "sort by member of b"<<endl;
    merge_sort(arr, 0, 2, compareB);

    for (int i = 0; i < 3; i++) {
        cout << arr[i].a << ", " << arr[i].b << endl;
    }
    
    return 0;
}