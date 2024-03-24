#include <stdio.h>
#include <stdlib.h>

// 定义链栈的结点结构
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 初始化链栈
void initStack(Node** top) {
    *top = NULL;
}

// 判断链栈是否为空
int isEmpty(Node* top) {
    return top == NULL;
}

// 入栈操作
void push(Node** top, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

// 出栈操作
int pop(Node** top) {
    if (isEmpty(*top)) {
        printf("Stack is empty.\n");
        return -1;
    }
    int data = (*top)->data;
    Node* temp = *top;
    *top = (*top)->next;
    free(temp);
    return data;
}

// 获取栈顶元素
int peek(Node* top) {
    if (isEmpty(top)) {
        printf("Stack is empty.\n");
        return -1;
    }
    return top->data;
}

// 打印链栈中的元素
void printStack(Node* top) {
    if (isEmpty(top)) {
        printf("Stack is empty.\n");
        return;
    }
    Node* current = top;
    printf("Stack elements: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node* top;
    initStack(&top);

    push(&top, 10);
    push(&top, 20);
    push(&top, 30);

    printStack(top);

    printf("Top element: %d\n", peek(top));

    printf("Popped element: %d\n", pop(&top));

    printStack(top);

    return 0;
}