#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    void* data;  // 用 void* 类型的指针来实现泛型
    struct node* next;
} Node;

typedef struct queue {
    Node* front; // 队头指针
    Node* tail;  // 队尾指针
} Queue;

// 入队操作，将给定的数据指针插入队列中
void EnGueue(Queue* q, void* data) {
    // 创建一个新的节点
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;  // 将数据指针存储在新节点中
    new_node->next = NULL;

    // 如果队列为空，将新节点设为队头和队尾
    if (q->front == NULL) {
        q->front = q->tail = new_node;
    }
    // 否则将新节点插入到队尾，并更新队尾指针
    else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
}

// 出队操作，弹出队列中的元素并返回其数据指针
void* DeGueue(Queue* q) {
    // 如果队列为空，返回 NULL
    if (q->front == NULL) {
        return NULL;
    }
    // 弹出队头元素，并保存其数据指针
    void* data = q->front->data;
    Node* temp = q->front;
    q->front = q->front->next;
    free(temp);
    // 如果队列变为空，将队尾指针设为 NULL
    if (q->front == NULL) {
        q->tail = NULL;
    }
    // 返回弹出的数据指针
    return data;
}

// 查看队列顶部的元素，返回其数据指针，但不弹出
void* GetHeadGueue(Queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    return q->front->data;
}
// 判断队列是否为空,为空则返回1
int IsEmptyGueue(Queue* q) {
    return q->front == NULL;
}
// 判断队列是否为满
int IsFullGueue(Queue* q) {
    return q->tail == NULL;
}
//销毁队列
void DestroyQueue(Queue* q) {
    if (!IsEmptyGueue(q))DeGueue(q);                    //不为空就一直出队
    return;
}
// 查看队列长度
int LengthGueue(Queue* q) {
    int i = 0;
    struct node* p = q->front;
    if (p!= NULL) {
        i++;
        p = p->next;
    }
    return i;
}
//遍历函数
void TraverseGueue(Queue* q) {
    struct node* p = q->front;
    if (p != NULL) {
        printf("DeGueue: %d\n", *(int*)DeGueue(q));
        p = p->next;
    }
    return;
}
int main() {
    Queue q;                                                             // 创建一个空队列
    q.front = q.tail = NULL;                                            // 初始化队头和队尾指针
    int int_data = 10;                                                 // 创建 int 类型的数据
    float float_data = 3.14;                                          // 创建 float 类型的数据
    char char_data = 'a';                                            // 创建 char 类型的数据
    EnGueue(&q, &int_data);                                         // 将 int 类型的数据插入队列
    EnGueue(&q, &float_data);                                      // 将 float 类型的数据插入队列
    EnGueue(&q, &char_data);                                      // 将 char 类型的数据插入队列
    EnGueue(&q, &int_data);                                      // 将 int 类型的数据插入队列
    printf("DeGueue: %d\n", *(int*)DeGueue(&q));                // 弹出并输出 int 类型的数据
    printf("DeGueue: %f\n", *(float*)DeGueue(&q));             // 弹出并输出 float 类型的数据
    printf("DeGueue: %c\n", *(char*)DeGueue(&q));             // 弹出并输出 char 类型的数据
    TraverseGueue(&q);                                       //遍历队列
    DestroyQueue(&q);                                       //销毁队列
    printf("Is empty? %d\n", IsEmptyGueue(&q));            // 输出队列是否为空
    return 0;
}
