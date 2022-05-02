#include <stdio.h>
#include <stdlib.h>

typedef char data;
typedef struct _Node{
    char key;
    struct _Node *left; // _ 구조체는 Node 구조체가 담긴 메모리를 가리키는 left라는 포인터를 멤버로 갖는다.
    struct _Node *right;
} Node;

Node *searchBST(Node *root, char x){
    Node *p = root;
    while (p != NULL){
        if (p->key == x)
            return p;
        else if (p->key < x) // 찾는 값이 큰 경우
            p = p->right; // 오른쪽으로 내려감
        else // 찾는 값이 작은 경우
            p = p->left; // 왼쪽으로 내려감
    }
    return NULL; // 찾는 값이 없는 경우
}

Node *insertBST(Node *root, char x){ // Node의 포인터를 리턴하는 이유는 무엇? void여도 되지 않나 -> 첫 노드를 넣을때 초기화 때문인듯
    Node *p = root;
    Node *parent = NULL;
    // Node *new_node = {x, NULL, NULL}; // key, left, right -> 이렇게 만들면 함수가 종료되면 변수가 사라짐

    while (p != NULL){
        parent = p;
        if (p->key == x){
            printf("이미 있는 값을 넣었네유? 그러면 돼유 안돼유?\n");
            return p;
        }
        else if (p->key < x){
            p = p->right;
        }
        else{
            p = p->left;
        }
    }
    Node *newNode = (Node*)malloc(sizeof(Node)); // 할당이 실패했을 경우에는 어째야 한다구..?
    newNode->key = x;
    newNode->left = newNode->right = NULL;

    if (parent != NULL){
        if (parent->key < x)
            parent->right = newNode; // 부모 자식 관계 설정
        else
            parent->left = newNode;
    }

    return newNode;
}


Node *deleteBST(Node *root, char x){ // 트리의 root 포인터를 넣었을 때 root가 없어지는 경우를 대비해서 새로운 root노드의 포인터를 리턴해준다.
    Node *p = root;
    Node *parent = NULL;

    // 삭제할 노드 p 찾기
    while (p != NULL && p->key != x){ // key와 같은 값을 찾거나 말단에 도달할 때까지
        parent = p;
        if (p->key < x)
            p = p->right;
        else
            p = p->left;
    }
    
    if (p == NULL){ // 삭제할 노드를 찾지 못한 경우
        printf("삭제하려는 노드가 없네요!\n");
        return root;
    }
    
    if (p->left == NULL && p->right == NULL){ // 삭제할 노드가 leaf노드인 경우
        if (parent == NULL) // 그리고 삭제할 노드가 root인 경우
            root = NULL;
        else{
            if (parent->left == p) // 찾은 노드가 왼쪽 자식인 경우
                parent->left = NULL;
            else
                parent->right = NULL;
        }
    }
    else if(p->left == NULL || p->right == NULL){ // 삭제할 노드의 자식이 하나인 경우
    // 삭제할 노드의 자식을 부모와 이어준다.
        Node *child = (p->left != NULL) ? p->left:p->right; // 삼항연산자
        if (parent == NULL) // 삭제할 노드가 root인 경우
            root = child;
        else{
            if (parent->left == p)
                parent->left = child;
            else
                parent->right = child;
        }
    }
    else{ // 삭제할 노드의 자식이 둘인 경우
        Node *succ_parent = p;
        Node *succ = p->right;
        while (succ->left != NULL){
            succ_parent = succ;
            succ = succ->left;
        }
        p->key = succ->key; // 자리 바꿔치기
        if (succ_parent->left == succ)
            succ_parent->left = succ->right;
        else
            succ_parent->right = succ->right;
        p = succ; // 삭제할 succ 노드를 free시키기 위해서        
    }
    free(p); // 할당한 메모리를 자유롭게 해줌

    return root;
}

void Inorder(Node *root){
    if (root==NULL)
        return;
    Inorder(root->left);
    printf("%c ", root->key);
    Inorder(root->right);
}


int main(){
    printf("-------------BST file was executed.-------------\n");

    Node *root = insertBST(NULL, 'D'); // bst 초기화
    insertBST(root, 'I');
    insertBST(root, 'F');
    insertBST(root, 'A');
    insertBST(root, 'G');
    insertBST(root, 'C');
    Inorder(root);  printf("\n");

    root = deleteBST(root, 'C');
    Inorder(root);  printf("\n");

    return 0;
}