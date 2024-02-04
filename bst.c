// 이진 탐색 트리
#include <stdio.h>
#include <stdlib.h>

// 이진 트리 노드 구조체
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
}Node;

// 노드 생성
Node* create() {    
    int data;
    printf("Enter data (-1 for no node): ");
    scanf("%d", &data);

    if (data == -1)
        return NULL;

    Node *newnode = (Node*)malloc(sizeof(Node));
    newnode->data = data;
    
    printf("Enter left child of %d", data);    
    newnode->left = create();             
    printf("Enter right child of %d", data);   
    newnode->right = create();

    return newnode;     // 루트 노드의 주소 반환
}

// 전위 순회 (Root - L - R)
void Preorder(Node *root) {
    if (root == NULL)               
        return;                     // 루트가 NULL (0) 인 경우 뒤로 돌아가기
    printf("%d", root->data);     
    Preorder(root->left);         
    Preorder(root->right);
}

// 중위 순회 (L - Root - R)
void Inorder(Node *root) {          
    if (root == NULL) 
        return;
    Inorder(root->left);           
    printf("%d", root->data);       
    Inorder(root->right);           
}

// 후위 순회 (L - R - Root)
void Postorder(Node *root) {
    if (root == NULL)
        return;
    Postorder(root->left);
    Postorder(root->right);
    printf("%d", root->data);
}

// 최솟값 출력
Node* findMin(Node *currentNode) {
    if (currentNode == NULL)     
        return NULL;                        // 빈 트리인 경우 NULL 반환         
    while (currentNode->left != NULL)       // 현재 노드의 left가 NULL이 아니면
        currentNode = currentNode->left;    // 가장 왼쪽 노드로 이동
    return currentNode;                     // 최솟값을 갖는 노드의 주소 반환
}

// 최댓값 출력
Node* findMax(Node *currentNode) {
    if (currentNode == NULL)
        return NULL;
    while (currentNode->right != NULL)
        currentNode = currentNode->right;
    return currentNode;
}

// 1. **삽입**: 새로운 키를 삽입할 때, 루트에서 시작하여 올바른 위치를 찾기 위해 키들을 비교합니다.
Node* insert(Node *currentNode, int key) {
    if (currentNode == NULL)               // 빈 트리일 경우 새로운 노드 생성해서 반환
        return create(key);
    if (key < currentNode->data)           // 키가 현재 노드의 키보다 작으면 왼쪽 서브트리에 삽입
        currentNode->left = insert(currentNode->left, key);
    else if (key > currentNode->data)      // 키가 현재 노드의 키보다 크면 오른쪽 서브트리에 삽입
        currentNode->right = insert(currentNode->right, key);
    return currentNode;                    // 트리 구조 유지하기 위해 새로운 노드 반환
}

// 2. **검색**: 루트에서 시작하여 원하는 노드를 찾기 위해 아래로 이동하며 키들을 비교합니다.
Node* search(Node *currentNode, int key) {
    if (currentNode == NULL || currentNode->data == key)    // 빈 트리이거나 키 찾은 경우 현재 노드 반환
        return currentNode;                                 // 해당 노드의 주소값 리턴
    if (key < currentNode->data)                            // 키가 현재 노드의 키보다 작은 경우 왼쪽 서브트리에서 검색
        return search(currentNode->left, key);
    else if (key > currentNode->data)                       // 키가 현재 노드의 키보다 큰 경우 오른쪽 서브트리에서 검색
        return search(currentNode->right, key);        
}

// 3. **삭제**: 리프 노드 삭제, 한 자식을 가진 노드 삭제, 두 자식을 가진 노드 삭제의 세 가지 경우를 다뤄야 합니다.
Node* delete(Node *currentNode, int key) {
    if (currentNode == NULL)       // 빈 트리면 널 리턴
        return NULL;

    // 1. 삭제할 노드를 찾는 과정
    if (key < currentNode->data)           // 루트 데이터보다 key가 작으면 왼쪽으로 이동
        currentNode->left = delete(currentNode->left, key);
    else if (key > currentNode->data)      // 루트 데이터보다 key가 크면 오른쪽으로 이동
        currentNode->right = delete(currentNode->right, key);

    // 2. 삭제할 노드를 찾았을 때
    else {
        if (currentNode->left == NULL) {        // 왼쪽 자식이 없는 경우
            Node *temp = currentNode->right;
            free(currentNode);
            return temp;
        }
        else if (currentNode->right == NULL) {  // 오른쪽 자식이 없는 경우
            Node *temp = currentNode->left;
            free(currentNode);
            return temp;
        }

        // 3. 두 자식을 가진 노드의 경우
        Node *temp = findMin(currentNode->right);     // 오른쪽 서브트리에서 최솟값 찾기
        currentNode->data = temp->data;                // 찾은 최솟값으로 현재 노드 데이터 교체
        currentNode->right = delete(currentNode->right, temp->data);  // 최솟값을 가진 노드 삭제
    }
    return currentNode;
}

// 이진 탐색 트리의 높이
int getHeight(Node *currentNode) {
    if (currentNode == NULL)
        return -1;              // 빈 트리의 높이: -1
    int leftHeight = getHeight(currentNode->left);
    int rightHeight = getHeight(currentNode->right);
    // 왼쪽과 오른쪽 서브트리 중 더 높은 높이에 + 1 한 것이 현재 노드 포함한 트리의 높이
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// 오른쪽 자식 출력
Node* get_right_chlid(Node* node) {
    if (node != NULL)
        return node->right;
    return NULL;
}

// 왼쪽 자식 출력
Node* get_left_child(Node* node) {
    if (node != NULL)
        return node->left;
    return NULL;
}

// 노드 개수 출력
int count_node(Node *currentNode) {
    if (currentNode == NULL)
        return 0;
    // 루트 노드 개수 + 왼쪽 서브트리 노드 개수 + 오른쪽 서브트리 노드 개수
    return 1 + count_node(currentNode->left) + count_node(currentNode->right);      
}

// 트리 비우기
void clear(Node** currentNode) {
    if (*currentNode == NULL)
        return;
    clear(&((*currentNode)->left));     
    clear(&((*currentNode)->right));    
    free(*currentNode);                 // 현재 노드 해제
    *currentNode = NULL;                // 루트를 NULL로 설정
}

int main() {
    Node* root = NULL;
    int choice, key;

    do {
        printf("\n------ Binary Search Tree Operations ------\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Preorder Traversal\n");
        printf("5. Inorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Height of the Tree\n");
        printf("8. Count Nodes\n");
        printf("9. Clear Tree\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                Node* result = search(root, key);
                if (result)
                    printf("Key %d found in the tree.\n", key);
                else
                    printf("Key %d not found in the tree.\n", key);
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = delete(root, key);
                break;
            case 4:
                printf("Preorder Traversal: ");
                Preorder(root);
                printf("\n");
                break;
            case 5:
                printf("Inorder Traversal: ");
                Inorder(root);
                printf("\n");
                break;
            case 6:
                printf("Postorder Traversal: ");
                Postorder(root);
                printf("\n");
                break;
            case 7:
                printf("Height of the Tree: %d\n", getHeight(root));
                break;
            case 8:
                printf("Number of Nodes: %d\n", count_node(root));
                break;
            case 9:
                clear(&root);
                printf("Tree cleared.\n");
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 0 and 9.\n");
        }
    } while (choice != 0);

    return 0;
}