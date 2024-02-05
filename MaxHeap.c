#include <stdio.h>

// 힙 구조체 정의 
typedef struct heap {
    int size;
    int arr[100001];
} Heap;

// 힙 초기화
void initHeap(Heap* heap) {
    heap->size = 0;
}

// 힙 출력
void displayHeap(Heap* heap) {
    printf("Heap: ");
    for (int i = 1; i <= heap->size; i++)
        printf("%d ", heap->arr[i]);
    printf("\n");
}

// 힙에 요소 삽입
void Insert(Heap* heap, int value) {
    // index의 초기 위치 - 배열의 맨 마지막 인덱스 + 1
    int index = heap->size + 1;
    // 부모와 비교하면서 올라가며 삽입 위치 찾기
    while (index != 1) {
        if (value > heap->arr[index / 2]) {          // 현재 노드 값이 부모 노드보다 큰 경우
            heap->arr[index] = heap->arr[index/2];  // 현재 노드에 부모 노드의 값 대입
            index /= 2;                             // 인덱스를 부모 노드로 이동
        }
        else                                        // 현재 노드 값이 부모 노드 값보다 작거나 같은 경우 루프 종료
            break;
    }
    heap->arr[index] = value;                        // 찾은 위치에 실제 노드 값 삽입
    heap->size++;                                   // 힙의 데이터 개수 증가
}

// 힙에서 요소 삭제
int Delete(Heap* heap) {
    int root = heap->arr[1];
    int last = heap->arr[heap->size--]; 

    int parent = 1; // 시작점 - 루트
    int leftChild, rightChild, maxIndex;

    while ((leftChild = parent * 2) <= heap->size) {    // 왼쪽 자식이 힙 범위 내에 있는 동안 반복
        rightChild = leftChild + 1;                     // 오른쪽 자식 계산

        // 마지막 노드가 왼쪽 자식만 있는 경우 또는 왼쪽, 오른쪽 자식이 모두 있는 경우
        maxIndex = (rightChild <= heap->size && heap->arr[leftChild] < heap->arr[rightChild]) ? rightChild : leftChild;

        // 마지막 노드가 선택된 자식보다 크면 교환
        if (last > heap->arr[maxIndex])
            break;
        else
            heap->arr[parent] = heap->arr[maxIndex];

        // 다음 레벨로 이동
        parent = maxIndex;
    }
    heap->arr[parent] = last;

    return root;
}

int main() {
    Heap heap;
    initHeap(&heap);

    // 요소 삽입
    Insert(&heap, 3);
    displayHeap(&heap);
    Insert(&heap, 5);
    displayHeap(&heap);
    Insert(&heap, 8);
    displayHeap(&heap);

    // 요소 삭제
    Delete(&heap);
    displayHeap(&heap);
    Delete(&heap);
    displayHeap(&heap);

    return 0;
}