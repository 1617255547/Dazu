#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include<conio.h>
//��ջ�ṹ
typedef int ElemType;            //�Զ�����������
typedef struct StackNode
{
	ElemType data;              //ջ�����ݣ����Լ��ڴ���ͷ������
	struct StackNode* next;     //��������Ľڵ��ַ
}StackNode, * LinkStackPtr;

typedef  struct  LinkStack
{
	LinkStackPtr top;	     //ջ��ָ��
	int		 count;             //ջ��Ԫ�ظ���
}LinkStack;
// ��ʼ����ջ
void initStackt(LinkStack* stack) {
    stack->top = NULL;
    stack->count = 0;
}
//�ж���ջ�Ƿ�Ϊ�պͷ��ش�С
int isEmptyStack(LinkStack* stack) {
    if (stack->top == NULL) {
        printf("\n����ջΪ��\nջ�ڵ���Ϊ��0");
        return 0;
    }
    else {
        printf("\n����ջ��Ϊ��\nջ�ڵ���Ϊ��%d\n",stack->count);
        return 1;
    }
}
//�õ�ջ��Ԫ��
ElemType getTopStack(LinkStack* stack) {
    return stack->top->data;
}
// ��ջ
void pushStack(LinkStack* stack, ElemType data) {                    //����ջ��ָ�����Ҫ���ջ�ڵ�����
    // �����½ڵ�
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->data = data;
    node->next = stack->top;                                  //��ջ����ַ��ֵ���½ڵ㴢��
    stack->top = node;                                       //���ڵ�Ԫ�ش�����ջ��
    stack->count++;                                         //ջ����1
    return;
}
// ��ջ
ElemType popStack(LinkStack* stack) {                    //����ջ��ָ��
    if (!isEmptyStack(stack))return 0;                //�����ջΪ�գ��򷵻��˳�           
    ElemType i;
    StackNode* node = stack->top;
    stack->top = node->next;
    stack->count--;
    i = node->data;                               //�����ջ����
    printf("\n��ջԪ��Ϊ��%d\n", node->data);//�����ջ����
    free(node);                                     //�ͷſռ�
    return i;                                       //���س�ջ����
}
//����ջ
void destoryStack(LinkStack* stack) {
    StackNode*q,*p = stack->top;
    stack->top = NULL;
    while (p!= NULL) {
        q = p;
        p->data = 0;                    //�Ȱ�������գ���ֹй¶
        p = p->next;
        free(q);                       //�ͷſռ�
    }
    printf("/n����ջ�Ѿ�������,������ջ��Ϊ��%d/n", stack->count);
    stack->count = 0;
    return;
}
// ���ջ
void clearStcck(LinkStack* stack) {
    while (stack->top != NULL)  popStack(stack);
}
// ��ӡ�����ջȫ������
void printStack(LinkStack* stack) {                     //���ջ������
    if (stack->top == NULL) {
        printf("\n����ջΪ��\nջ�ڵ���Ϊ��0");
        return;
    }
    StackNode* p = stack->top;
    printf("\nStack: ");
    while (p!= NULL) {
        printf("%d   ", p->data);                       //���Ҫ���������
        p = p->next;
    }
    printf("\n��ǰջ�ڵ���Ϊ��\n%d\n", stack->count);
    return;
}
//�����˵�
void Menu()
{
    printf("\n=========[��ջ�����˵�]============\n");
    printf("[A/a]-��ӡ�����ջȫ������\n");
    printf("[B/b]��ջ\n");
    printf("[C/c]��ջ\n");
    printf("[D/d]���ջ\n");
    printf("[E/e]����ջ\n");
    printf("[F/f]�鿴��ջ״̬\n");
    printf("[�ո�]-�˳�\n");
    printf("=================================\n");
}
// ������
int main() {
    LinkStack stack;

    initStackt(&stack);        // ��ʼ����ջ

    pushStack(&stack, 1);          //������ջ����
    pushStack(&stack, 2);
    pushStack(&stack, 3);
    pushStack(&stack, 4);
    pushStack(&stack, 5);

    printStack(&stack);       // ��ӡ��ʼ��ջ����

    printf("\n�������Ѿ��������ݣ�������ʾ���������һ������\n");
    ElemType el;            //�洢����ڵ��������ݣ�����������
    char c = '0';
    do
    {
        Menu();
        printf("\n��ѡ������Ҫ�Ĳ���\n");
        switch (c = _getch())
        {
        case 'A':
        case 'a':printStack(&stack);                    //�����ջ����
            break;
        case 'B':
        case 'b':printf("\n��������ջ������\n��Ȼ��س�\n");
            scanf_s("%d", &el);                 //�������������ͷ����仯ʱ���˴����޸���������
            pushStack(&stack, el);               //��ջ
            break;
        case 'C':
        case 'c':popStack(&stack);                  //��ջ
            break;
        case 'D':
        case 'd':clearStcck(&stack);            //���ջ
            break;
        case 'E':
        case 'e':destoryStack(&stack);    //����ջ
            break;
        case 'F':
        case 'f':isEmptyStack(&stack);             //�鿴��ջ״̬
            break;
        }
    } while (c != ' ');

    return 0;
}