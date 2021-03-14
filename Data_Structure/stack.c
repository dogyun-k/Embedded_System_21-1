//스택 - 연결리스트로 구현
#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node_s {
    int data;
    struct Node_s *next;
}Node_s;
 
typedef struct Stack {
    Node_s *top;    //맨 앞 노드(가장 최근에 생성한 노드)
}Stack;

void InitStack(Stack *stack) {
    stack->top = NULL; //스택 초기화에서는 top을 NULL로 설정
}
 
int IsEmpty_s(Stack *stack) {
    return stack->top == NULL;    //top이 NULL이면 빈 상태    
}

void Push(Stack *stack, int data) {
    Node_s *now = (Node_s *)malloc(sizeof(Node_s)); //노드 생성
    now->data = data;//데이터 설정
    now->next = stack->top;//now의 next링크를 현재 top으로 설정   
    stack->top = now;   //스택의 맨 앞은 now로 설정
}

int Pop(Stack *stack) {
    Node_s *now;
    int re;
    if (IsEmpty_s(stack))
    {
        return 0;
    }
    now = stack->top;       //now를 top으로 설정
    re = now->data;         //꺼낼 값은 now의 data로 설정
 
    stack->top = now->next; //top을 now의 next로 설정
    free(now);              //필요없으니 메모리 해제
    return re;
}