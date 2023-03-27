#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LENGTH 20      // 假设最长输入的数字长度不超过 20 位,设定空间

typedef struct {
    int top;               // 栈顶位置
    int data[MAX_LENGTH];  // 栈中存的数据，数组模式表达
} Stack;

void init(Stack* s) {
    s->top = -1;           // 初始化栈顶位置为 -1
}

int empty(Stack* s) {    //判别栈是否为空
    return s->top == -1;
}

// 压栈操作
void push(Stack* s, int x) {
    s->top++;
    s->data[s->top] = x;            //将数据入栈
}

// 弹栈操作
int pop(Stack* s) {
    if (empty(s)) {
        printf("Error: stack is empty.\n");         //判别是否为空
        exit(-1);
    }
    int x = s->data[s->top];                    //赋值出栈数据
    s->top -= 1;
    return x;
}

// 获取栈顶元素
int top(Stack* s) {
    if (empty(s)) {
        printf("Error: stack is empty.\n");
        exit(-1);
    }
    return s->data[s->top];                     //仅仅是获取栈顶数据
}

// 判断是否为运算符函数
int  is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// 比较运算符的优先级
int compare_priority(char op1, char op2) {
    // 返回值小于 0 表示 op1 优先级更低，大于 0 表示 op1 优先级更高，等于 0 表示 op1 和 op2 优先级相同
    if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/')) {
        return -1;
    }
    else if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-')) {
        return 1;
    }
    else {
        return 0;
    }
}

// 计算表达式中的一项，返回结果
int calculate_stack_item(Stack* num_stack, Stack* op_stack) {
    char op = pop(op_stack);                            //弹出一个运算符
    int num2 = pop(num_stack);                          //弹出数字
    int num1 = pop(num_stack);
    int result;
    switch (op) {
    case '+':
        result = num1 + num2;
        break;
    case '-':
        result = num1 - num2;
        break;
    case '*':
        result = num1 * num2;
        break;
    case '/':
        if (!num2) {
            printf("\n0不能作为除数,输出结果错误。\n"); return 0;        //判断不合法算子式
        }
        result = num1 / num2;
        break;
    default:
        break;
    }
    return result;
}

//将中缀表达式换为后缀表达式
int calculate_rpn(char* rpn) {
    Stack num_stack;                            //设立两个栈区，这个是数字
    Stack op_stack;                             //这个是字符栈区
    init(&num_stack);
    init(&op_stack);

    for (int i = 0; rpn[i] != '\0'; i++) {
        if (isdigit(rpn[i])) {
            // 如果是数字，则将连续的数字字符转换为数字压入数字栈中
            int num = 0;
            while (isdigit(rpn[i])) {                          //引用判断数字的函数 isdigit，在#include <ctype.h>库内
                num = num * 10 + (rpn[i] - '0');
                i += 1;
            }
            i -= 1;
            push(&num_stack, num);
        }
        else if (is_operator(rpn[i])) {                      // 如果是运算符，则判断其优先级并与运算符栈中的运算符比较，决定是否将其压入运算符栈中
            while (!empty(&op_stack) && compare_priority(top(&op_stack), rpn[i]) >= 0) {
                int result = calculate_stack_item(&num_stack, &op_stack);
                push(&num_stack, result);
            }
            push(&op_stack, rpn[i]);
        }
    }

    // 对数字栈和运算符栈中剩余的元素进行计算，直到运算符栈为空为止
    while (!empty(&op_stack)) {                                 //只要栈顶不为空，一直计算
        int result = calculate_stack_item(&num_stack, &op_stack);
        push(&num_stack, result);
    }

    return top(&num_stack);
}

int main() {
    char rpn[MAX_LENGTH];                               //设立输出储存式子
    printf("\n请输入中缀表达式: \n");
    fgets(rpn, MAX_LENGTH, stdin);
    int result = calculate_rpn(rpn);                    //将中缀表达式转为后缀表达式并计算
    printf("Result: %d\n", result);
    return 0;
}