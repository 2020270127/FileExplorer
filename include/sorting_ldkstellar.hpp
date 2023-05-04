#include <iostream>
using namespace std;
#include <iostream>
#include <string>
using namespace std;
template <typename T>
void quicksort(T **data ,int col ,int start, int end){// 파라미터 설명 data는 더블포인터 변수,행번호 , 행번호 파라미터의 시작 인덱스 , 열번호 파라미터의 마지막 인덱스 
   if(start >= end){
    //원소가 1개인 
        return ; 
    }
    int pivot = start;
    int i = pivot + 1; 
    // 왼쪽 출발 지점 
    int j = end; 
    // 오른쪽 출발 지점
    char* temp;
    
    while(i <= j){
        // 포인터가 엇갈릴때까지 반복
        while(i <= end && data[i][col] <= data[pivot][col]){
            i++;
        }
        while(j > start && data[j][col] >= data[pivot][col]){
            j--;
        }
        if(i > j){
            // 엇갈림
            temp = data[j];
            data[j] = data[pivot];
            data[pivot] = temp;
        }
        else{
            // i번째와 j번째를 스왑
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    quicksort(data, col,start, j - 1);// low part 정렬
    quicksort(data, col,j + 1, end);  //high part 정렬
}

template <typename T> 
void sorting(T **p, int col ,int first,int end){ //파라미터 배열 , 열 번호 ,행의 첫번째 인덱스,행의 마지막 인덱스 
    
     quicksort(p,col,first,end); //첫번째 열에서 퀵소트 진행
            //중복 검색 기능
            int rear = first; //중복문자열의 마지막 값을 의미
            int front = first; //중복 문자열의 시작 값을 의미
        
    for (int j = 0; j <= end; j++)// 
    { 
        if (front == rear && p[front][col] !=p[j][col]){// 꼬리와 대가리가 같고  대가리의 행의 값과 j행의 값이 다르면 
                rear = j;// j 인덱스로 다 이동
                front =j;// j
            }
        else if (p[rear][col]== p[j][col]){//꼬리의 행의 값과 j의 행의 값이 일치하면 
                rear = j;// 인덱스이동
                if(rear ==end) // 만약 rear이랑 마지막 인덱스랑 동일하면
                    sorting(p,col+1,front,rear);//재귀함수 실행
            }
            
        else if(front != rear &&  p[rear][col] != p[j][col] ){// 대가리의 인덱스와 꼬리인덱스가 동일하지 않고  꼬리의 값과 j의 값이 다르면 
                sorting(p,col+1,front,rear);// 재귀함수실행
                front =j; // 재귀함수 실행후 나머지 함수 진행시 front값을 rear값을 현재 j의 값으로 초기화
                rear=j;
            }
           
        }
}
