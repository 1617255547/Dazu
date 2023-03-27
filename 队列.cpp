#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    void* data;  // �� void* ���͵�ָ����ʵ�ַ���
    struct node* next;
} Node;

typedef struct queue {
    Node* front; // ��ͷָ��
    Node* tail;  // ��βָ��
} Queue;

// ��Ӳ�����������������ָ����������
void EnGueue(Queue* q, void* data) {
    // ����һ���µĽڵ�
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;  // ������ָ��洢���½ڵ���
    new_node->next = NULL;

    // �������Ϊ�գ����½ڵ���Ϊ��ͷ�Ͷ�β
    if (q->front == NULL) {
        q->front = q->tail = new_node;
    }
    // �����½ڵ���뵽��β�������¶�βָ��
    else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
}

// ���Ӳ��������������е�Ԫ�ز�����������ָ��
void* DeGueue(Queue* q) {
    // �������Ϊ�գ����� NULL
    if (q->front == NULL) {
        return NULL;
    }
    // ������ͷԪ�أ�������������ָ��
    void* data = q->front->data;
    Node* temp = q->front;
    q->front = q->front->next;
    free(temp);
    // ������б�Ϊ�գ�����βָ����Ϊ NULL
    if (q->front == NULL) {
        q->tail = NULL;
    }
    // ���ص���������ָ��
    return data;
}

// �鿴���ж�����Ԫ�أ�����������ָ�룬��������
void* GetHeadGueue(Queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    return q->front->data;
}
// �ж϶����Ƿ�Ϊ��,Ϊ���򷵻�1
int IsEmptyGueue(Queue* q) {
    return q->front == NULL;
}
// �ж϶����Ƿ�Ϊ��
int IsFullGueue(Queue* q) {
    return q->tail == NULL;
}
//���ٶ���
void DestroyQueue(Queue* q) {
    if (!IsEmptyGueue(q))DeGueue(q);                    //��Ϊ�վ�һֱ����
    return;
}
// �鿴���г���
int LengthGueue(Queue* q) {
    int i = 0;
    struct node* p = q->front;
    if (p!= NULL) {
        i++;
        p = p->next;
    }
    return i;
}
//��������
void TraverseGueue(Queue* q) {
    struct node* p = q->front;
    if (p != NULL) {
        printf("DeGueue: %d\n", *(int*)DeGueue(q));
        p = p->next;
    }
    return;
}
int main() {
    Queue q;                                                             // ����һ���ն���
    q.front = q.tail = NULL;                                            // ��ʼ����ͷ�Ͷ�βָ��
    int int_data = 10;                                                 // ���� int ���͵�����
    float float_data = 3.14;                                          // ���� float ���͵�����
    char char_data = 'a';                                            // ���� char ���͵�����
    EnGueue(&q, &int_data);                                         // �� int ���͵����ݲ������
    EnGueue(&q, &float_data);                                      // �� float ���͵����ݲ������
    EnGueue(&q, &char_data);                                      // �� char ���͵����ݲ������
    EnGueue(&q, &int_data);                                      // �� int ���͵����ݲ������
    printf("DeGueue: %d\n", *(int*)DeGueue(&q));                // ��������� int ���͵�����
    printf("DeGueue: %f\n", *(float*)DeGueue(&q));             // ��������� float ���͵�����
    printf("DeGueue: %c\n", *(char*)DeGueue(&q));             // ��������� char ���͵�����
    TraverseGueue(&q);                                       //��������
    DestroyQueue(&q);                                       //���ٶ���
    printf("Is empty? %d\n", IsEmptyGueue(&q));            // ��������Ƿ�Ϊ��
    return 0;
}
