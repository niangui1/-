#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // 检查字符是否为数字
#include <string.h>  // 字符串操作函数

// 链表节点结构体
typedef struct Node {
    int data;  // 节点数据
    struct Node *next;  // 指向下一个节点的指针
} Node;

// 链表结构体
typedef struct Stack {
    Node *top;  // 栈顶指针
} Stack;

// 初始化链表
void initStack(Stack *stack) {
    stack->top = NULL;  // 初始化栈顶指针为空
}

// 判断链表是否为空
int isEmpty(Stack *stack) {
    return stack->top == NULL;
}

// 入栈操作
void push(Stack *stack, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));  // 创建新节点
    newNode->data = data;  // 设置节点数据
    newNode->next = stack->top;  // 将新节点指向原栈顶
    stack->top = newNode;  // 更新栈顶指针
}

// 出栈操作
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("栈为空\n");
        exit(1);
    }
    int data = stack->top->data;  // 获取栈顶元素数据
    Node *temp = stack->top;  // 保存栈顶指针
    stack->top = stack->top->next;  // 更新栈顶指针
    free(temp);  // 释放原栈顶节点的内存
    return data;
}

// 获取栈顶元素
int top(Stack *stack) {
    if (isEmpty(stack)) {
        printf("栈为空\n");
        exit(1);
    }
    return stack->top->data;
}

// 释放链表内存
void clearStack(Stack *stack) {
    Node *current = stack->top;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}



// 定义操作数栈和操作符栈
Stack operandStack;
Stack operatorStack;

// 获取操作符的优先级
int getPriority(char op) {
    if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    return 0;
}

// 计算两个操作数的结果
int calculate(int num1, int num2, char op) {
    switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            return num1 / num2;
    }
    return 0;
}

// 对给定的四则运算表达式求值
int evaluateExpression(char expression[]) {
    int len = strlen(expression);
    int i = 0;
    while (i < len) {
        if (isspace(expression[i])) {  // 忽略空格字符
            i++;
            continue;
        }
        if (isdigit(expression[i])) {  // 处理数字
            int operand = 0;
            while (i < len && isdigit(expression[i])) {
                operand = operand * 10 + (expression[i] - '0');
                i++;
            }
            push(&operandStack, operand);  // 将操作数压入操作数栈
        } else if (expression[i] == '(') {  // 处理左括号
            push(&operatorStack, expression[i]);  // 左括号直接压入操作符栈
            i++;
        } else if (expression[i] == ')') {  // 处理右括号
            while (!isEmpty(&operatorStack) && top(&operatorStack) != '(') {
                // 弹出操作数栈中的两个操作数和操作符栈中的一个操作符进行计算
                int num2 = pop(&operandStack);
                int num1 = pop(&operandStack);
                char op = pop(&operatorStack);
                int result = calculate(num1, num2, op);
                push(&operandStack, result);  // 将计算结果压入操作数栈
            }
            if (!isEmpty(&operatorStack) && top(&operatorStack) == '(') {
                pop(&operatorStack);  // 弹出左括号
            }
            i++;
        } else {  // 处理操作符
            while (!isEmpty(&operatorStack) && getPriority(expression[i]) <= getPriority(top(&operatorStack))) {
                // 弹出操作数栈中的两个操作数和操作符栈中的一个操作符进行计算
                int num2 = pop(&operandStack);
                int num1 = pop(&operandStack);
                char op = pop(&operatorStack);
                int result = calculate(num1, num2, op);
                push(&operandStack, result);  // 将计算结果压入操作数栈
            }
            push(&operatorStack, expression[i]);  // 将当前操作符压入操作符栈
            i++;
        }
    }

    while (!isEmpty(&operatorStack)) {
        // 弹出操作数栈中的两个操作数和操作符栈中的一个操作符进行计算
        int num2 = pop(&operandStack);
        int num1 = pop(&operandStack);
        char op = pop(&operatorStack);
        int result = calculate(num1, num2, op);
        push(&operandStack, result);  // 将计算结果压入操作数栈
    }
    
    // 最终结果为栈顶元素
    return top(&operandStack);
}

int main() {
    char expression[100];
    printf("请输入四则运算表达式: ");
    scanf("%[^\n]", expression);

    initStack(&operandStack);
    initStack(&operatorStack);

    int result = evaluateExpression(expression);
    printf("结果为: %d\n", result);

    clearStack(&operandStack);
    clearStack(&operatorStack);

    return 0;
}
