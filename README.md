# 태수의 피드백


## 전역변수

```c++
node* front = 0;
node* rear = 0;
```

- 구조체 자료형 안에 다 선언해 두었으면서 새로 전역변수를 만들 이유가 전혀 없다.
- 또한 포인터 변수를 0으로 초기화해도 문제는 없지만 비어있는 포인터라는 것을 코드를 읽는 입장에서 이해하기 쉽게 하려면 `NULL`을 넣으셈
- 게다가, 전역변수는 모든 함수에서 접근할 수 있기에, 저장된 값이 어디서 어떻게 바뀌고 사용되는지 추적하기 대단히 어렵다. 복잡한 프로그램을 만들 때는 사용하지 않는 것이 좋다.
- 구조체 내의 변수와 전역변수는 전혀 다른 것임을 기억할것


## new_queue

```c++
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
```

- queue 구조체 자료형에 멤버 변수 max_size가 있던데, 매개변수로 값을 받은 뒤, 같이 초기화 해 주는 것이 어땠을까?
- 현재 상황에서라면 max_size의 초기화를 깜빡했을 때, 문제가 생길 수 있다.
- 기능을 함수로 따로 빼는 상황은 이런 머리 아픈 문제를 신경쓰지 않게 하기 위해서인데, 이러면 의미가 없지


## enqueue

```c++
void enqueue(queue* que, int x){     
    node* newnode = new_node(x);
    
    if(is_empty(que)){
        que->front = que->rear = newnode;
    }
    else{
        que->rear->next = newnode;       
        que->rear = newnode;
        que->size += 1;
    }
}
```

- `que->size` 변수는 큐가 비어있을 때에도 늘어나야 한다.


## dequeue

```c++
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
```

- `node* temp = que->front` 같이 한 줄에 작성할 수도 있다. 이 편이 더 깔끔하지 않은가?
- 게다가, 값을 삭제한 뒤, 연결리스트에 값이 더이상 존재하지 않는다면, q->front와 q->rear가 가리키는 메모리는 어떤 메모리일까?
- q->front와 q->rear은 이제 가리킬 연결 리스트가 없으니, 다시 NULL로 초기화 해주어야 하지 않을까?
- 이 과정이 없으면, 이후의 큐 사용에서 버그가 생길 수 있으며, 무엇보다 isempty 함수의 정상작동이 보장되지 않는다.


## is_empty

```c++
bool is_empty(const queue* que){
    return que->front == NULL && que->rear == NULL;
}
```

- 만약 위의 dequeue에서 `que->front`와 `que->back`을 `NULL`로 초기화 해주었다면, 둘 중 하나만 검사해도 됐을 것이다.
- 논리적으로, 둘 중 하나의 포인터 변수만 무언가 의미있는 메모리 주소를 가리키고 있을 수 있는가? 
- 기능을 조금 더 보완하자면, `que->front`나 `que->back`을 검사하기 전에 `que` 포인터 변수가 비어있지는 않은지 검사할 수도 있을 것이다.


## clear_queue

```c++
void clear_queue(queue** que){
    while(!is_empty(*que))
        dequeue(*que);
    free(*que);
    *que = NULL;
}
```

- 테스트를 하면서 에러가 자꾸 나지 않던가?
- 이 함수 자체에는 문제가 없지만, 다른 함수들의 버그로 인해 제대로 작동하지 않는다.
- 왜 작동하지 않는지 곰곰히 생각해보고, 고쳐볼것. 답은 피드백 내에 있다.





