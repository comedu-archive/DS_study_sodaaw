// 연결리스트를 활용한 큐 구현

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 노드 구조체
typedef struct node{    
    char data;
    struct node* next;
}node;

// 큐 구조체
typedef struct queue{   
    node* front;
    node* rear;
    int size;
    int max_size;   // 큐의 최대 크기
}queue;

// 함수 사용 전 선언
bool is_empty(const queue* que);
bool is_full(const queue* que);

// 새로운 큐 만드는 함수
queue* new_queue() {
    queue* que = malloc(sizeof(queue));
    if (que == NULL) {
        printf("Not enough memory");
        exit(EXIT_FAILURE);
    }
    que->size = 0;      // 큐의 크기 0으로 초기화
    que->front = NULL;     // 큐의 첫 요소 
    que->rear = NULL;
    return que;
}

// 새로운 데이터를 넣을 노드를 만드는 함수
node* new_node(const char data){
    node* another = malloc(sizeof(node));
    if (another == NULL){
        printf("Not enough memory");
        exit(EXIT_FAILURE);
    }
    another->data = data;
    another->next = NULL;
    return another;
}

// head 노드, tail 노드의 주소 초기화
node* front = 0;
node* rear = 0;

// 큐에 새 노드 추가 (큐는 새로 들어온 노드가 뒤에 추가됨 - rear에 추가)
void enqueue(queue* que, int x){     
    node* newnode = new_node(x);    // 새 노드 생성, 데이터 추가
    
    if(is_empty(que)){    // 비어있는 큐인 경우
        que->front = que->rear = newnode;     // front, rear에 newnode의 주소 대입
    }
    else{                           // 비어있지 않은 큐인 경우
        que->rear->next = newnode;       
        que->rear = newnode;
        que->size += 1;
    }
}

// 큐에서 노드 삭제 (큐는 먼저 들어온 순서대로 삭제됨 - front 노드 삭제)
void dequeue(queue* que){
    node* temp;     // 이동 위한 임시 노드
    temp = que->front;   // temp 노드가 맨 앞을 가리키게 설정
    if (is_empty(que)){       // 큐가 비어있는 경우
        printf("Queue is empty");
        return;
    }
    else{                               // 큐가 비어있지 않은 경우
        que->front = que->front->next;
        free(temp);
        que->size -= 1;
    }
}

// 큐가 비어있는지 알려주는 함수
bool is_empty(const queue* que){
    return que->front == NULL && que->rear == NULL;
}

// 큐가 가득 차 있는지 알려주는 함수
bool is_full(const queue* que) {
    return que->size == que->max_size;
}

// 큐의 요소 출력
void display(queue *que){
    node* temp;     // 이동 위한 임시 노트
    if(is_empty(que)){
        printf("Queue is empty");
    }
    else{
        temp = que->front;       // temp 노드가 맨 앞을 가리키게 설정
        while(temp != 0){   // 맨 끝까지 진행
            printf("%c", temp->data);   // 노드의 데이터 출력
            temp = temp->next;          // 다음 노드로 이동
        }
    }
}

// 큐의 front 요소 출력
void peek(const queue* que){
    if(is_empty(que)){
        printf("Queue is empty");
    }
    else{
        printf("%c", que->front->data);
    }
}

// 큐 안에 값이 몇 개 들어 있는지 알려주는 함수
int size(const queue* que){
    if (is_empty(que)) return 0;
    return que->size;
}

// target 문자가 큐 안에 존재하는지 알려주는 함수
bool is_member(const queue* que, const char target){
    if(is_empty(que)) return false;

    node* temp = que->front;    // temp 노드에 맨 앞 주소 저장
    while (temp != 0) {         // 끝 부분까지 실행
        if (temp->data == target) break;    // 원하는 문자를 찾은 경우
        else temp = temp->next;             // 찾지 못한 경우 다음 노드로 이동
    }

    if (temp) return true;      // null이 아닌 모든 값은 true 취급
    return false;               // 찾지 못했을 경우
}

// 다 쓴 큐를 삭제하는 함수
void clear_queue(queue** que){
    while(!is_empty(*que))
        dequeue(*que);
    free(*que);
    *que = NULL;
}

// 마지막 값을 바꾸는 함수
void replace_rear(const queue* que, const char target){
    if(is_empty(que)) return;
    que->rear->data = target;
}

int main() {
    // 새로운 큐 생성, 최대 크기를 3으로 가정
    queue* myQueue = new_queue();
    myQueue->max_size = 3;

    // 큐에 노드 추가
    enqueue(myQueue, 'A');
    enqueue(myQueue, 'B');
    enqueue(myQueue, 'C');

    // 큐의 상태 출력
    printf("Queue after enqueuing: ");
    display(myQueue);
    printf("\n");

    // 큐가 가득 차 있는지 확인
    if (is_full(myQueue)) {
        printf("Queue is full.\n");
    } else {
        printf("Queue is not full.\n");
    }

    // 큐의 맨 앞 요소 출력
    printf("Front element of the queue: ");
    peek(myQueue);
    printf("\n");

    // 큐의 크기 출력
    printf("Size of the queue: %d\n", size(myQueue));

    // 'B'가 큐 안에 있는지 확인
    char target = 'B';
    if (is_member(myQueue, target)) {
        printf("%c is in the queue.\n", target);
    } else {
        printf("%c is not in the queue.\n", target);
    }

    // 큐에서 노드 삭제
    dequeue(myQueue);

    // 큐의 상태 출력
    printf("Queue after dequeuing: ");
    display(myQueue);
    printf("\n");

    // 마지막 값 'C'를 'X'로 변경
    char newTarget = 'X';
    replace_rear(myQueue, newTarget);
    printf("Queue after replacing the last element: ");
    display(myQueue);
    printf("\n");

    // 큐가 가득 차 있는지 확인
    if (is_full(myQueue)) {
        printf("Queue is full.\n");
    } else {
        printf("Queue is not full.\n");
    }

    // 큐 삭제
    clear_queue(&myQueue);

    return 0;
}
