#include <stdio.h>
#include <stdlib.h>

// 定义链表中节点的结构
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

// 定义队列的结构
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// 创建一个新节点的函数
Node* createNode(void* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 创建一个空队列的函数
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// 检查队列是否为空的函数
int isEmpty(Queue* queue) {
    return (queue->front == NULL);
}

// 将元素入队的函数
void enqueue(Queue* queue, void* data) {
    Node* newNode = createNode(data);
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// 将元素出队的函数
void* dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("队列为空。\n");
        return NULL;
    } else {
        Node* temp = queue->front;
        void* data = temp->data;
        queue->front = queue->front->next;
        free(temp);
        return data;
    }
}

// 获取队列前端元素的函数
void* front(Queue* queue) {
    if (isEmpty(queue)) {
        printf("队列为空。\n");
        return NULL;
    } else {
        return queue->front->data;
    }
}

// 获取队列后端元素的函数
void* rear(Queue* queue) {
    if (isEmpty(queue)) {
        printf("队列为空。\n");
        return NULL;
    } else {
        return queue->rear->data;
    }
}

// 显示队列中的元素的函数
void display(Queue* queue) {
    if (isEmpty(queue)) {
        printf("队列为空。\n");
    } else {
        Node* current = queue->front;
        while (current != NULL) {
            printf("%p ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

// 释放队列所分配的内存的函数
void freeQueue(Queue* queue) {
    Node* current = queue->front;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(queue);
}

int main() {
    // 创建一个新队列
    Queue* queue = createQueue();

    // 将一些元素入队
    int num1 = 10;
    enqueue(queue, &num1);

    float num2 = 3.14;
    enqueue(queue, &num2);

    char ch = 'A';
    enqueue(queue, &ch);

    // 显示队列中的元素
    display(queue);

    // 将一个元素出队
    void* data = dequeue(queue);
    printf("出队元素: %p\n", data);

    // 出队后显示队列中的元素
    display(queue);

    // 释放队列所分配的内存
    freeQueue(queue);

    return 0;
}