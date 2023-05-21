#include <iostream>
#include <string>

using namespace std;

// int strcmp(string a, string b) {
//     int alen = a.length();
//     int blen = b.length();
//     int min_strlen = min(alen, blen);
//     for (int i = 0; i < min_strlen; i++) { // 더 작은 문자열 길이 만큼 비교
//         if (a.at(i) > b.at(i))
//             return 1;
//         else if (a.at(i) < b.at(i))
//             return 0;
//     }
//     // 문자열 모두 같은 경우 짧은게 우선
//     if (alen > blen)
//         return 1;
//     else if (alen < blen)
//         return 0;
//     else
//         return -1; // 같은 문자열인 경우 다른 속성 비교
// }

template <typename T> void swap(T *a, T *b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template <typename T> bool comp(T a, T b) {
    if (a > b)
        return 1;
    else
        return 0;
}

template <typename T, typename U, typename CmpFunc = bool (*)(U, U)>
void quick_sort(T array[], int left, int right, U value, CmpFunc cmp) {
    if (left < right) {
        int i = left, j = right;
        T tmp;
        T pivot = array[(left + right) / 2];

        while (i <= j) {
            while (cmp(pivot.*value, array[i].*value)) //
                i++;
            while (cmp(array[j].*value, pivot.*value))
                j--;
            if (i <= j) {
                swap(&array[i], &array[j]);
                i++;
                j--;
            }
        }
        if (left < j)
            quick_sort(array, left, j, value, cmp);
        if (i < right)
            quick_sort(array, i, right, value, cmp);
    }
}

template <typename T, typename U, typename CmpFunc = bool (*)(U, U)>
void merge(T *arr, int left, int mid, int right, U value, CmpFunc cmp) {
    int i = left, j = mid + 1, k = 0;
    T *tmp = new T[right - left + 1];

    while (i <= mid && j <= right) {
        if (cmp(arr[j].*value, arr[i].*value)) {
            tmp[k] = arr[i];
            k++;
            i++;

        } else {
            tmp[k] = arr[j];
            k++;
            j++;
        }
    }
    while (i <= mid) {
        tmp[k] = arr[i];
        k++;
        i++;
    }
    while (j <= right) {
        tmp[k] = arr[j];
        k++;
        j++;
    }

    for (int p = 0; p < k; p++) {
        arr[left + p] = tmp[p];
    }
}

template <typename T, typename U, typename CmpFunc = bool (*)(U, U)>
void merge_sort(T array[], int left, int right, U value, CmpFunc cmp) {
    int mid = (left + right) / 2;

    if (left < right) // 배열의 원소가 1개이면 재귀함수종료
    {
        int mid = (left + right) / 2;
        merge_sort(array, left, mid, value,
                   cmp); // 왼쪽 배열의 원소가 1개 될 때까지 나누는 작업
        merge_sort(array, mid + 1, right, value, cmp); // 오른쪽 배열
        merge(array, left, mid, right, value,
              cmp); // 왼쪽 배열과 오른쪽 배열 비교후 병합하는 작업
    }
}

template <typename T, typename U, typename CmpFunc = bool (*)(U, U)>
void heapify(T array[], int heapsize, int i, U value, CmpFunc cmp) {
    int parentNode = i;
    int leftChildNode = i * 2 + 1;
    int rightChildNode = i * 2 + 2;

    // 왼쪽 자식 노드가 존재하면서 부모노드와 값 비교.
    if (heapsize > leftChildNode &&
        cmp(array[leftChildNode].*value, array[parentNode].*value)) {
        parentNode = leftChildNode;
    }
    // 오른쪽 자식 노드가 존재하면서 부모노드와 값 비교.
    if (heapsize > rightChildNode &&
        cmp(array[rightChildNode].*value, array[parentNode].*value)) {
        parentNode = rightChildNode;
    }

    // 왼쪽 or 오른쪽 자식 노드 중 부모 노드보다 큰 값이 존재한 경우
    if (i != parentNode) {
        swap(&array[parentNode], &array[i]);
        // swap(&(array[parentNode].name), &(array[i].name));
        // swap(&(array[parentNode].size), &(array[i].size));
        // swap(&(array[parentNode].modified_time), &(array[i].modified_time));

        // 초기 부모노드가 제자리를 찾을 때까지 내려갑니다.
        heapify(array, heapsize, parentNode, value, cmp);
    }
}

template <typename T, typename U, typename CmpFunc = bool (*)(U, U)>
void heap_sort(T *arr, int size, U value, CmpFunc cmp) {
    // 제자리 정렬(추가 메모리 필요x), O(nlogn) 불안정 정렬
    // 배열 max heapify
    for (int i = (size - 1) / 2; i >= 0; i--) {
        heapify(arr, size - 1, i, value, cmp); // 밑에 있는 부모노드부터 heapify
    }
    // heap sort
    for (int i = size - 1; i > 0; i--) { // max heap을 size - 1번 뒤로 보내기
        // swap(&(arr[i].name), &(arr[0].name));          // max heap을 배열뒤로
        // 보낸다. swap(&(arr[i].size), &(arr[0].size));
        // swap(&(arr[i].modified_time), &(arr[0].modified_time));
        swap(&arr[i], &arr[0]);
        heapify(arr, i, 0, value, cmp);
    }
    return;
}

// int main() { // 테스트용
//     int arr[] = {5, 3, 4, 2, 1, 0, 67, 987, 3, 5};
//     string astr[] = {"hello", "hi", "hiru", "hired", "apple", "banana"};
//     for (auto i : arr) {
//         cout << i << " ";
//     }
//     cout << "\n";
//     quick_sort(arr, 0, 9, comp<int>);
//     for (auto i : arr) {
//         cout << i << " ";
//     }
//     cout << "\n";
//     for (auto i : astr) {
//         cout << i << " ";
//     }
//     cout << "\n";
//     merge_sort(astr,0,5, comp<string>);
//     for (auto i : astr) {
//         cout << i << " ";
//     }
// }
