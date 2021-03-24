//큐 - 연결리스트 이용
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct Node_q {
    int data;
    struct Node_q *next;
}Node_q;
 
typedef struct Queue {
    Node_q *front;    //맨 앞(꺼낼 위치)
    Node_q *rear;     //맨 뒤(보관할 위치)
    int count;      //보관 개수
}Queue;

void InitQueue(Queue *queue) {
    queue->front = queue->rear = NULL;  //front와 rear를 NULL로 설정
    queue->count = 0;                   //보관 개수를 0으로 설정
}
 
int IsEmpty_q(Queue *queue) {
    return queue->count == 0;           //보관 개수가 0이면 빈 상태
}
 
void Enqueue(Queue *queue, int data) {
    Node_q *now = (Node_q *)malloc(sizeof(Node_q)); //노드 생성
    now->data = data;//데이터 설정
    now->next = NULL;
 
    if (IsEmpty_q(queue)) {
        queue->front = now;//맨 앞을 now로 설정       
    }
    else {
        queue->rear->next = now;//맨 뒤의 다음을 now로 설정
    }
    queue->rear = now;          //맨 뒤를 now로 설정   
    queue->count++;             //보관 개수를 1 증가
}
 
int Dequeue(Queue *queue) {
    int re = 0;
    Node_q *now;
    if (IsEmpty_q(queue)) {
        return re;
    }

    now = queue->front;         //맨 앞의 노드를 now에 기억
    re = now->data;             //반환할 값은 now의 data로 설정
    queue->front = now->next;   //맨 앞은 now의 다음 노드로 설정
    free(now);                  //now 소멸
    queue->count--;             //보관 개수를 1 감소
    return re;
}