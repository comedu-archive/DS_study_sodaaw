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

// 새로운 큐 만드는 함수 (매개변수로 큐의 최대 크기를 받음)
queue* new_queue(int max_size) {
    queue* que = malloc(sizeof(queue));
    if (que == NULL) {
        printf("Not enough memory");
        exit(EXIT_FAILURE);
    }
    que->size = 0;      // 큐의 크기 0으로 초기화
    que->front = NULL;     // 큐의 첫 요소 (NULL 대입은 비어있는 포인터라는 뜻)
    que->rear = NULL;
    que->max_size = max_size;   // 큐의 최대 크기 초기화
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

// 큐에 새 노드 추가 (큐는 새로 들어온 노드가 뒤에 추가됨 - rear에 추가)
void enqueue(queue* que, int x){     
    node* newnode = new_node(x);    // 새 노드 생성, 데이터 추가
    
    if(is_empty(que)){    // 비어있는 큐인 경우
        que->front = que->rear = newnode;     // front, rear에 newnode의 주소 대입
    }
    else{                           // 비어있지 않은 큐인 경우
        que->rear->next = newnode;       
        que->rear = newnode;
    }
    que->size += 1;     // 큐의 크기 증가 - 큐가 비어있을 때에도 늘어남
}

// 큐에서 노드 삭제 (큐는 먼저 들어온 순서대로 삭제됨 - front 노드 삭제)
void dequeue(queue* que){
    node* temp = que->front;   // 이동 위한 임시 노드 temp가 맨 앞을 가리키게 함
    if (is_empty(que)){       // 큐가 비어있는 경우
        printf("Queue is empty");
        que->front = que->rear = NULL;   // front와 rear를 다시 NULL로 초기화
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
    if (que == NULL){   // 비어있는 큐인 경우
        printf("유효하지 않은 큐!");
        return true;
    }
        return que->front == NULL;  // 한쪽만 검사 (큐가 비어 있을 때는 front, back 둘 다 null)
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
void replace_rear(queue* que, const char target){
    if(is_empty(que)) return;
    que->rear->data = target;
}

int main() {
    // 큐 생성
    queue* myQueue = new_queue(5);

    // 큐에 데이터 추가
    enqueue(myQueue, 'A');
    enqueue(myQueue, 'B');
    enqueue(myQueue, 'C');

    // 큐의 상태 출력
    printf("Queue after enqueuing: ");
    display(myQueue);
    printf("\n");

    // 큐에서 데이터 제거
    dequeue(myQueue);

    // 큐의 상태 출력
    printf("Queue after dequeuing: ");
    display(myQueue);
    printf("\n");

    // 큐의 front 요소 출력
    printf("Front element: ");
    peek(myQueue);
    printf("\n");

    // 큐의 사이즈 출력
    printf("Queue size: %d\n", size(myQueue));

    // 특정 값이 큐에 있는지 확인
    char target = 'B';
    if (is_member(myQueue, target)) {
        printf("%c is in the queue.\n", target);
    } else {
        printf("%c is not in the queue.\n", target);
    }

    // 큐의 rear 값을 변경하고 출력
    replace_rear(myQueue, 'X');
    printf("Queue after replacing rear: ");
    display(myQueue);
    printf("\n");

    // 큐 비우기
    clear_queue(&myQueue);

    return 0;
}
