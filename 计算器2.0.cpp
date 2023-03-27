#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LENGTH 20      // �������������ֳ��Ȳ����� 20 λ,�趨�ռ�

typedef struct {
    int top;               // ջ��λ��
    int data[MAX_LENGTH];  // ջ�д�����ݣ�����ģʽ���
} Stack;

void init(Stack* s) {
    s->top = -1;           // ��ʼ��ջ��λ��Ϊ -1
}

int empty(Stack* s) {    //�б�ջ�Ƿ�Ϊ��
    return s->top == -1;
}

// ѹջ����
void push(Stack* s, int x) {
    s->top++;
    s->data[s->top] = x;            //��������ջ
}

// ��ջ����
int pop(Stack* s) {
    if (empty(s)) {
        printf("Error: stack is empty.\n");         //�б��Ƿ�Ϊ��
        exit(-1);
    }
    int x = s->data[s->top];                    //��ֵ��ջ����
    s->top -= 1;
    return x;
}

// ��ȡջ��Ԫ��
int top(Stack* s) {
    if (empty(s)) {
        printf("Error: stack is empty.\n");
        exit(-1);
    }
    return s->data[s->top];                     //�����ǻ�ȡջ������
}

// �ж��Ƿ�Ϊ���������
int  is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// �Ƚ�����������ȼ�
int compare_priority(char op1, char op2) {
    // ����ֵС�� 0 ��ʾ op1 ���ȼ����ͣ����� 0 ��ʾ op1 ���ȼ����ߣ����� 0 ��ʾ op1 �� op2 ���ȼ���ͬ
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

// ������ʽ�е�һ����ؽ��
int calculate_stack_item(Stack* num_stack, Stack* op_stack) {
    char op = pop(op_stack);                            //����һ�������
    int num2 = pop(num_stack);                          //��������
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
            printf("\n0������Ϊ����,����������\n"); return 0;        //�жϲ��Ϸ�����ʽ
        }
        result = num1 / num2;
        break;
    default:
        break;
    }
    return result;
}

//����׺���ʽ��Ϊ��׺���ʽ
int calculate_rpn(char* rpn) {
    Stack num_stack;                            //��������ջ�������������
    Stack op_stack;                             //������ַ�ջ��
    init(&num_stack);
    init(&op_stack);

    for (int i = 0; rpn[i] != '\0'; i++) {
        if (isdigit(rpn[i])) {
            // ��������֣��������������ַ�ת��Ϊ����ѹ������ջ��
            int num = 0;
            while (isdigit(rpn[i])) {                          //�����ж����ֵĺ��� isdigit����#include <ctype.h>����
                num = num * 10 + (rpn[i] - '0');
                i += 1;
            }
            i -= 1;
            push(&num_stack, num);
        }
        else if (is_operator(rpn[i])) {                      // ���������������ж������ȼ����������ջ�е�������Ƚϣ������Ƿ���ѹ�������ջ��
            while (!empty(&op_stack) && compare_priority(top(&op_stack), rpn[i]) >= 0) {
                int result = calculate_stack_item(&num_stack, &op_stack);
                push(&num_stack, result);
            }
            push(&op_stack, rpn[i]);
        }
    }

    // ������ջ�������ջ��ʣ���Ԫ�ؽ��м��㣬ֱ�������ջΪ��Ϊֹ
    while (!empty(&op_stack)) {                                 //ֻҪջ����Ϊ�գ�һֱ����
        int result = calculate_stack_item(&num_stack, &op_stack);
        push(&num_stack, result);
    }

    return top(&num_stack);
}

int main() {
    char rpn[MAX_LENGTH];                               //�����������ʽ��
    printf("\n��������׺���ʽ: \n");
    fgets(rpn, MAX_LENGTH, stdin);
    int result = calculate_rpn(rpn);                    //����׺���ʽתΪ��׺���ʽ������
    printf("Result: %d\n", result);
    return 0;
}