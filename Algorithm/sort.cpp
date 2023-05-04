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
    if (alen > blen)
        return 1;
    else if (alen < blen)
        return 0;
    else
        return -1; // 같은 문자열인 경우 다른 속성 비교
}

template <typename T> void swap(T *a, T *b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template <typename T, typename CmpFunc = T (*)(T, T)>
void quick_sort(T array[], int left, int right, CmpFunc cmp) {
    if (left < right) {
            int i = left, j = right;
            T tmp;
            T pivot = array[(left + right) / 2];

            while (i <= j) {
                while (cmp(pivot,array[i]))//
                    i++;
                while (cmp(array[j],pivot))
                    j--;
                if (i <= j) {
                    tmp = array[i];
                    array[i] = array[j];
                    array[j] = tmp;
                    i++;
                    j--;
                }
            }
            if (left < j)
                quick_sort(array, left, j, cmp);
            if (i < right)
                quick_sort(array, i, right, cmp);
        }
}

template <typename T> bool comp(T a, T b) {
    if (a > b)
        return 1;
    else 
        return 0;
}

template <typename T, typename CmpFunc = T (*)(T, T)>
void heapify(T array[], int heapsize, int i, CmpFunc cmp) {
    int parentNode = i;
    int leftChildNode = i * 2 + 1;
    int rightChildNode = i * 2 + 2;

    // 왼쪽 자식 노드가 존재하면서 부모노드와 값 비교.
    if (heapsize > leftChildNode &&
        cmp(array[leftChildNode], array[parentNode])) {
        parentNode = leftChildNode;
    }
    // 오른쪽 자식 노드가 존재하면서 부모노드와 값 비교.
    if (heapsize > rightChildNode &&
        cmp(array[rightChildNode], array[parentNode])) {
        parentNode = rightChildNode;
    }

    // 왼쪽 or 오른쪽 자식 노드 중 부모 노드보다 큰 값이 존재한 경우
    if (i != parentNode) {
        swap(&array[parentNode], &array[i]);
        // 초기 부모노드가 제자리를 찾을 때까지 내려갑니다.
        heapify(array, heapsize, parentNode, cmp);
    }
}


template <typename T, typename CmpFunc = T (*)(T, T)>
void heap_sort(T *arr, int size, CmpFunc cmp) {
    // 제자리 정렬(추가 메모리 필요x), O(nlogn) 불안정 정렬
    // 배열 max heapify
    for (int i = (size - 1) / 2; i >= 0; i--) {
        heapify(arr, size - 1, i, cmp); // 밑에 있는 부모노드부터 heapify
    }
    // heap sort
    for (int i = size - 1; i > 0; i--) { // max heap을 size - 1번 뒤로 보내기
        swap(&arr[i], &arr[0]);          // max heap을 배열뒤로 보낸다.
        heapify(arr, i, 0, cmp);
    }
    return;
}

template <typename T> void merge_sort(T *arr, int left, int right) { return; }

int main() { // 테스트용
    int arr[] = {5, 3, 4, 2, 1, 0, 67, 987, 3, 5};
    string astr[] = {"hello", "hi", "hiru", "hired", "apple", "banana"};
    for (auto i : arr) {
        cout << i << " ";
    }
    cout << "\n";
    quick_sort(arr, 0, 9, comp<int>);
    for (auto i : arr) {
        cout << i << " ";
    }
    cout << "\n";
    for (auto i : astr) {
        cout << i << " ";
    }
    cout << "\n";
    heap_sort(astr, 6, strcmp);
    for (auto i : astr) {
        cout << i << " ";
    }
}
