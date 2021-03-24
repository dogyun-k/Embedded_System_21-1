#include <stdio.h>
 
typedef struct Node_s {
    int data;
    struct Node_s *next;
}Node_s;
 
typedef struct Stack {
    Node_s *top;    
}Stack;

void InitStack(Stack *stack);       //스택 초기화
int IsEmpty_s(Stack *stack);          //스택이 비었는지 확인
void Push(Stack *stack, int data);  //스택에 보관
int Pop(Stack *stack);              //스택에서 꺼냄