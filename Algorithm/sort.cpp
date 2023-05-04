#include <iostream>
#include <string>

using namespace std;

int strcmp(string a, string b) {
    int alen = a.length();
    int blen = b.length();
    int min_strlen = min(alen, blen);
    for (int i = 0; i < min_strlen; i++) { // 더 작은 문자열 길이 만큼 비교
        if (a.at(i) > b.at(i))
            return 1;
        else if (a.at(i) < b.at(i))
            return 0;
    }
    // 문자열 모두 같은 경우 짧은게 우선
    if (alen < blen)
        return 1;
    else if (blen < alen)
        return 0;
    else
        return -1; // 같은 문자열인 경우 다른 속성 비교
}

template <typename T> void swap(T *a, T *b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template <typename T>
void quick_sort(T *arr, int left, int right, bool (*cptr)(T, T)) {

    return;
}


template <typename T>
bool comp(T a, T b){
    if(a > b)
        return 1;
    else if(b < a)
        return 0;
    else return 0;    
}


template <typename T, typename CmpFunc =  T (*)(T, T)>
void heapify(T array[], int heapsize, int i, CmpFunc cmp) {
    int parentNode = i;
    int leftChildNode = i * 2 + 1;
    int rightChildNode = i * 2 + 2;

    // 왼쪽 자식 노드가 존재하면서 부모노드와 값 비교.
    if ( cmp (heapsize, leftChildNode) && cmp(array[leftChildNode], array[parentNode])) {
        parentNode = leftChildNode;
    }
    // 오른쪽 자식 노드가 존재하면서 부모노드와 값 비교.
    if (cmp (heapsize, rightChildNode) && cmp(array[rightChildNode], array[parentNode])) {
        parentNode = rightChildNode;
    }

    // 왼쪽 or 오른쪽 자식 노드 중 부모 노드보다 큰 값이 존재한 경우
    if (i != parentNode) {
        swap(&array[parentNode], &array[i]);
        // 초기 부모노드가 제자리를 찾을 때까지 내려갑니다.
        heapify(array, heapsize, parentNode, cmp);
    }
}

template <typename T, typename CmpFunc =  T (*)(T, T)>
void heap_sort(T *arr, int size, CmpFunc cmp) {
    // 제자리 정렬(추가 메모리 필요x), O(nlogn) 불안정 정렬
    // 배열 max heapify
    for (int i = (size - 1) / 2; i >= 0; i--) {
        heapify(arr, size, i, cmp); // 밑에 있는 부모노드부터 heapify
    }
    // heap sort
    for (int i = size - 1; i > 0; i--) { // max heap을 size - 1번 뒤로 보내기
        swap(&arr[i], &arr[0]); // max heap을 배열뒤로 보낸다.
        heapify(arr, i , 0, cmp);
    }
    return;
}

template <typename T> void merge_sort(T *arr, int left, int right) { return; }

int main() { // 테스트용
    int arr[] = {5, 3, 4, 2, 1, 0,67, 987, 3, 5};
    for (auto i : arr) {
        cout << i << " ";
    }
    cout << "\n";
    heap_sort(arr, 6, comp<int>);
    for (auto i : arr) {
        cout << i << " ";
    }
}