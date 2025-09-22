#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE } bool;

typedef struct treeNode {
    int data;
    struct treeNode* left, * right;
    int is_thread;
} treeNode;

// Ʈ�� ����
treeNode n11 = { 11, NULL, NULL, 0 };
treeNode n10 = { 10, NULL, NULL, 0 };
treeNode n8 = { 8, NULL, NULL, 0 };
treeNode n6 = { 6, NULL, NULL, 0 };
treeNode n5 = { 5, NULL, NULL, 0 };
treeNode n4 = { 4, NULL, NULL, 0 };
treeNode n9 = { 9, &n10, &n11, 0 };
treeNode n7 = { 7, &n8, &n9, 0 };
treeNode n3 = { 3, &n4, &n5, 0 };
treeNode n2 = { 2, &n3, &n6, 0 };
treeNode n1 = { 1, &n2, &n7, 0 };
treeNode* root = &n1;

// �����ļ��ڸ� ã�� �Լ�
treeNode* find_successor(treeNode *p) {
    treeNode* q = p->right;
    if (q == NULL || p->is_thread == TRUE )
        return q;
    while (q->left != NULL)
        q = q->left;
    return q;
}

// ���� ��ȸ �Լ�
void thread_inorder(treeNode* p) {
    printf("1. ���� ��ȸ ��� \n");
    treeNode* q;
    q = p;
    while (q->left != NULL)
        q = q->left;
    do {
        printf("%d ", q->data);
        q = find_successor(q);
    } while (q);
}

// �θ� ��� ã�� �Լ�
treeNode* parent(treeNode* child) {
    treeNode* q = child->right;
    treeNode* ql = q->left;
    if (q == NULL)
        return;
    else if (q->left == child || q->right == child)
        return q->data;
    else if(ql->left == child || ql->right == child)
        return ql->data;
    else {
        printf("error");
        exit(1);
    }
}

int main(void) {
    // ������ ����
    n4.right = &n3;  n4.is_thread = 1;
    n5.right = &n2;  n5.is_thread = 1;
    n6.right = &n1;  n6.is_thread = 1;
    n8.right = &n7;  n8.is_thread = 1;
    n10.right = &n9; n10.is_thread = 1;

    thread_inorder(root);
    printf("\n");

    
    int n4p = parent(&n4);
    printf("2. Node4�� �θ� : %d \n", n4p);
    int n5p = parent(&n4);
    printf("3. Node5�� �θ� : %d \n", n5p);
    int n6p = parent(&n4);
    printf("4. Node6�� �θ� : %d \n", n6p);
    
    return 0;
}