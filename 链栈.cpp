#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include<conio.h>
//链栈结构
typedef int ElemType;            //自定义数据类型
typedef struct StackNode
{
	ElemType data;              //栈里数据，由自己在代码头部定义
	struct StackNode* next;     //储存新入的节点地址
}StackNode, * LinkStackPtr;

typedef  struct  LinkStack
{
	LinkStackPtr top;	     //栈顶指针
	int		 count;             //栈中元素个数
}LinkStack;
// 初始化链栈
void initStackt(LinkStack* stack) {
    stack->top = NULL;
    stack->count = 0;
}
//判断链栈是否为空和返回大小
int isEmptyStack(LinkStack* stack) {
    if (stack->top == NULL) {
        printf("\n该链栈为空\n栈节点数为：0");
        return 0;
    }
    else {
        printf("\n该链栈不为空\n栈节点数为：%d\n",stack->count);
        return 1;
    }
}
//得到栈顶元素
ElemType getTopStack(LinkStack* stack) {
    return stack->top->data;
}
// 入栈
void pushStack(LinkStack* stack, ElemType data) {                    //输入栈顶指针和需要添加栈内的数据
    // 创建新节点
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->data = data;
    node->next = stack->top;                                  //将栈顶地址赋值给新节点储存
    stack->top = node;                                       //将节点元素储存至栈顶
    stack->count++;                                         //栈数加1
    return;
}
// 出栈
ElemType popStack(LinkStack* stack) {                    //输入栈顶指针
    if (!isEmptyStack(stack))return 0;                //如果链栈为空，则返回退出           
    ElemType i;
    StackNode* node = stack->top;
    stack->top = node->next;
    stack->count--;
    i = node->data;                               //保存出栈数据
    printf("\n出栈元素为：%d\n", node->data);//输出出栈数据
    free(node);                                     //释放空间
    return i;                                       //返回出栈数据
}
//销毁栈
void destoryStack(LinkStack* stack) {
    StackNode*q,*p = stack->top;
    stack->top = NULL;
    while (p!= NULL) {
        q = p;
        p->data = 0;                    //先把数据请空，防止泄露
        p = p->next;
        free(q);                       //释放空间
    }
    printf("/n该链栈已经被销毁,其销毁栈数为：%d/n", stack->count);
    stack->count = 0;
    return;
}
// 清空栈
void clearStcck(LinkStack* stack) {
    while (stack->top != NULL)  popStack(stack);
}
// 打印输出链栈全部数据
void printStack(LinkStack* stack) {                     //检查栈内数据
    if (stack->top == NULL) {
        printf("\n该链栈为空\n栈节点数为：0");
        return;
    }
    StackNode* p = stack->top;
    printf("\nStack: ");
    while (p!= NULL) {
        printf("%d   ", p->data);                       //输出要改输出类型
        p = p->next;
    }
    printf("\n当前栈节点数为：\n%d\n", stack->count);
    return;
}
//操作菜单
void Menu()
{
    printf("\n=========[链栈操作菜单]============\n");
    printf("[A/a]-打印输出链栈全部数据\n");
    printf("[B/b]入栈\n");
    printf("[C/c]出栈\n");
    printf("[D/d]清空栈\n");
    printf("[E/e]销毁栈\n");
    printf("[F/f]查看链栈状态\n");
    printf("[空格]-退出\n");
    printf("=================================\n");
}
// 主函数
int main() {
    LinkStack stack;

    initStackt(&stack);        // 初始化链栈

    pushStack(&stack, 1);          //增加入栈数据
    pushStack(&stack, 2);
    pushStack(&stack, 3);
    pushStack(&stack, 4);
    pushStack(&stack, 5);

    printStack(&stack);       // 打印初始链栈数据

    printf("\n链表本身已经存在数据，如上所示，请进行下一步操作\n");
    ElemType el;            //存储输入节点数和数据，当链表数据
    char c = '0';
    do
    {
        Menu();
        printf("\n请选择你需要的操作\n");
        switch (c = _getch())
        {
        case 'A':
        case 'a':printStack(&stack);                    //输出链栈数据
            break;
        case 'B':
        case 'b':printf("\n请输入入栈的数据\n，然后回车\n");
            scanf_s("%d", &el);                 //当链表数据类型发生变化时，此处需修改输入类型
            pushStack(&stack, el);               //入栈
            break;
        case 'C':
        case 'c':popStack(&stack);                  //出栈
            break;
        case 'D':
        case 'd':clearStcck(&stack);            //清空栈
            break;
        case 'E':
        case 'e':destoryStack(&stack);    //销毁栈
            break;
        case 'F':
        case 'f':isEmptyStack(&stack);             //查看链栈状态
            break;
        }
    } while (c != ' ');

    return 0;
}