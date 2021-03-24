typedef struct Node_q //노드 정의
{
    int data;
    struct Node_q *next;
}Node_q;
 
 
typedef struct Queue //Queue 구조체 정의
{
    Node_q *front; //맨 앞(꺼낼 위치)
    Node_q *rear; //맨 뒤(보관할 위치)
    int count;//보관 개수
}Queue;
 

void InitQueue(Queue *queue);//큐 초기화
int IsEmpty_q(Queue *queue); //큐가 비었는지 확인
void Enqueue(Queue *queue, int data); //큐에 보관
int Dequeue(Queue *queue); //큐에서 꺼냄
 