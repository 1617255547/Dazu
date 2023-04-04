#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<assert.h>
#define MAXSIZE 10                                                               //���峤�ȣ����޸Ľ��ж��ֲ���
void fileadd(long length, char numfile[]) {                                     //�����ݱ��ݽ����ļ��У��������Ը��������㷨������ʱ��
    FILE* fp;
    fopen_s(&fp, numfile, "w");
    if (fp == NULL) {
        printf("���ļ�ʧ��");
        return;
    }
    int* temp = (int*)malloc(sizeof(int) * length);
    srand(time(NULL));
    for (long i = 0; i < length; i++)
        temp[i] = rand() % MAXSIZE;                        //���ļ����length������������������ж��㷨ʱ�����������Ϊ  0����MAXSIZE/10�����޸�
    fwrite(temp, sizeof(int), length, fp);
    fclose(fp);
    free(temp);
    return;

}
void filepop(int arr[], long length, char numfile[]) {
    FILE* fp;
    fopen_s(&fp, numfile, "r+");
    if (fp == NULL) {
        printf("���ļ�ʧ��");
        return;
    }
    fread(arr, sizeof(int), length, fp);                    //���ļ��ж�ȡ���ݵ�������
    fclose(fp);
    return;
}
int Max(int arr[],long length) {                          //�����������ֵ����
    int max = 0;
    for (int j = 0; j < length; j++)
        if (max < arr[j])max = arr[j];
    return max;
}
void initarr(int arr[], long length) {                 //�������������
    srand(time(NULL));
    for (long i = 0; i < length; i++)
        arr[i] = rand() % (MAXSIZE)+1;                  //Ϊ������������������Ϊ  0����MAXSIZE/10�����޸�
    return;
}
void Showarr(int arr[], long length) {                  //������麯��
    for (long i = 0; i < length; i++)
        printf("%d ", arr[i]);
    return;
}
//��������
void InsertSort(int arr[], long length) {

    long i = 1, j, key;          //���ü���i���ƶ���꣬�ӵڶ������ֿ�ʼ��j�Ǽ�¼iǰ�������±꣬key����ʱ�����±�Ϊi������
    for (; i < length; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {              //�ж϶�Ӧ�±�j�����Ƿ��i�󣬴�����ǰһλ�ƶ�
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;                             //������a[i]С������ʱ���ͽ�a[i]�����ݷŵ�����ǰһλ�������ڵ�i������ǰ�����ݾ����к���
    }                                               //���η�����ֱ���������
    return;
}
//���ţ��ݹ�棩
void QuickSort(int arr[], long left, long right) {
    if (left >= right)return;                       //�������±���ڵ����ұߣ���֤��ֻ����һ�����ݣ�����Ҫ�����ˣ�ֱ������
    long i = left, j = right;                        //i��¼��߹�꣬j��¼�ұ߹��
    long pivot = arr[i];                             //ѡȡ�����Ϊ������
    while (i < j) {                                 //�����ָ��δ��������һֱ���в�����ֱ������
        while (i<j && arr[j]>pivot)j--;             //�ұ�ָ�����ƶ����ڲ�������Ѱ�ұ�������С����
        arr[i] = arr[j];                            //��������ݷŵ�a[i]��λ��
        while (i < j && arr[i] <= pivot)i++;        //�ұ�����һ�����ֵ�����ƶ����ڲ�������Ѱ�ұ�����������
        arr[j] = arr[i];                             //��������ݷŵ�a[j]��λ����
    }
    arr[i] = pivot;                                 //�����������ݷŵ������λ����
    QuickSort(arr, left, i - 1);                     //�ݹ�˼�룬���Ϸֽ⣬ֱ��ȫ���ź���
    QuickSort(arr, i + 1, right);
    return;
}
//������������
void RadixCountSort(int arr[], long length) {
    int max = Max(arr, length);                             //�����������ֵ
    int temp[10][MAXSIZE];
    for (int i = 0; i < 10; i++)                           //���帳��ֵ
        memset(temp[i], 0, sizeof(int) * MAXSIZE);
    int i, j, pow;                                          //��¼λ����iΪarr������±꣬powΪ��ά����temp�������꣬jΪ�����±�
    for (int k = 10; k <= max*10; k *= 10) {                 //�Ӹ�λ����ʼ�����δӵ͵���λ���м�������
        for (i = 0; i < length; i++) {                      //��ʱiΪ����arr�ı����±�
            j = 0;
            pow = arr[i] % k / (k / 10);                    //pow��Ϊ��ǰλ�������֣���13����λ��ȡ3��ʮλ��ȡ1
            while (temp[pow][j])                            //���ò۲�Ϊ0ʱ��j++
                j++;
            temp[pow][j] = arr[i];                          //����ʱ��arr�����ݴ����е�temp�����ά��������
        }
        i = 0;                                           
        for (pow = 0; pow < 10; pow++) {
            for (j = 0; j < length && temp[pow][j] != 0; j++) {       //���յ�ǰ��λ������С����ŵ�arr�����У�Ȼ���λ��temp��ֵΪ0
                arr[i++] = temp[pow][j];
                temp[pow][j] = 0;
            }
        }
    }
    return;
}
//��������
void CountSort(int arr[], long length) {
    int max = Max(arr, length);                             //�����������ֵ
    int* temp = (int*)malloc(sizeof(int) * (max+1));        //��������ռ�,Ҫ��0Ҳ�ӽ�ȥ��һ����
    memset(temp, 0, sizeof(int) * (max + 1));
    for (int i = 0; i < length; i++)                    //�������飬��¼���ݳ��ִ�������temp�����±�����¼
        temp[arr[i]]++;
    for (int i = 0, j = 0; i <= max; i++)                //�����ݷŻ������У�temp������Ϊ��ͽ���Ӧ�±������arr������
        while (temp[i]--)
            arr[j++] = i;
    free(temp);         //�ͷſռ�
    return;
}
//�鲢����
void merge(int arr[], long low, long middle, long height, int temp[]) {           //�鲢�����ĺϲ�������temp���ݴ����飬low��middle��heightΪ�ͣ��У���λ
    long i = low, j = middle + 1, k = low;                                     //���������֣���С����ֱ����
    while (i <= middle && j <= height)                                        //�����û����ͷ��������
        temp[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];                   //�ĸ�С�ĸ��ͷŵ�temp�����鿨λ�������������+1
    while (i <= middle)                                                     //ʣ��û�������Ԫ��ֱ�ӷŵ�temp�ݴ�����ĺ���
        temp[k++] = arr[i++];
    while (j <= height)
        temp[k++] = arr[j++];
    for (long i = low; i <= height; i++)
        arr[i] = temp[i];                                                 //���Ѿ��ź�������ݷ��ظ�ԭ����arr����
    return;
}
void Merge(int arr[], long low, long height, int temp[]) {                  //�ָ����麯�����ݹ�˼�룬�������Ϊ����Ԫ���������������
    if (low >= height)return;                                           //���Ԫ�طָ����һ������ֹͣ�ָ�
    long middle = low + (height - low) / 2;                            //�����м�λ��middle�����ã�low+height��/2��Ϊ�˷�ֹԽ��
    Merge(arr, low, middle, temp);                                     //�Ե�ǰ����ǰ�벿�ַָ�
    Merge(arr, middle + 1, height, temp);                             //�Ե�������ǰ�벿�ַָ�
    merge(arr, low, middle, height, temp);                          //�ָ���ɺ�Ե�ǰ���������Ϲ鲢����
    return;
}
void MergeSort(int arr[], long length) {                           //�鲢����ʼ����
    int* temp = (int*)malloc(sizeof(int) * MAXSIZE);              //����ռ䣬������ʱ�ݴ�����
    assert(temp);                                                //����ݴ�����Ƿ�������������жϳ���
    Merge(arr, 0, length - 1, temp);                              //��ʼ��֣��ϲ�������
    free(temp);                                                //�ͷ���ʱ����Ŀռ�
    return;
}
//�����˵�
void Menu()
{
    printf("\n=========[�����㷨�����˵�]============\n");
    printf("[A/a]-��������\n");
    printf("[B/b]���ŵݹ��\n");
    printf("[C/c]������������\n");
    printf("[D/d]��������\n");
    printf("[E/e]�鲢����\n");
    printf("[F/f]�޸Ľڵ�����\n");
    printf("[�ո�]-�˳�\n");
    printf("=================================\n");
    printf("\n�����Ҫ���ĺ����㷨\n");
}
int main() {
    long n, length; int arr[MAXSIZE];
    n = sizeof(arr) / sizeof(arr[0]);           //�������鳤��n
    char numfile[100] = "C:/Users/86180/Desktop/numfile.txt";           //�������������ļ�
    printf("\n�Ƿ���Ҫ����������ļ�����Ҫ�����롮0��\n");
    if (getchar() == '0') {
        printf("\n��������Ҫ�����������\n");
        scanf_s("%d", &length);
        if (length < n) {
            printf("\n��������������������������鳤�ȣ�����\n");
            return 0;
        }
        fileadd(length, numfile);                         //��������������ļ���                      
    }
    printf("\n�Ƿ�ֱ�Ӵ��ļ���ȡ���ݣ����롮1��\n�����������������\n");
    getchar();                                                                      //����Ϊʲô��ô������õ�getchar��������ǰ��getchar�Ժ����жϵ�Ӱ��
    if (getchar() == '1')
        filepop(arr, n, numfile);                                                //���ļ��ж�ȡ��������۲첻ͬ�㷨����һ������ʱ����ʱ
    else
        initarr(arr, n);
    getchar();                                                                   //Ϊ����arr������������������Ե�һ�㷨ʱʹ��
    Showarr(arr, n);                                                           //չʾ�����ʼ״̬
    Menu();                                                                   //չʾ���ܲ˵�
    clock_t start = 0, time = 0;                                                 //��������ʱ�䣬����ʱ�亯��
    switch (getchar())                                                         //ѡ��һ���������
    {
    case 'A':
    case 'a':  start = clock();                                             //��start = clock(); ���ں���ʵ��ǰ��ʹ����ʱ���¼����׼ȷ
        InsertSort(arr, n);                     //��������
        break;
    case 'B':
    case 'b':  start = clock();
        QuickSort(arr, 0, n - 1);               //���ŵݹ�����
        break;
    case 'C':
    case 'c':  start = clock();
        RadixCountSort(arr, n);                 //������������
        break;
    case 'D':
    case 'd':  start = clock();
        CountSort(arr, n);                      //��������
        break;
    case 'E':
    case 'e': start = clock();
        MergeSort(arr, n);                      //�鲢����
        break;
    case 'F':
    case 'f':                                   //����
        break;
    }
    time = clock() - start;
    printf("\n\n����ʱ��Ϊ��%d  ms\n\n", time);
    Showarr(arr, n);
    return 0;
}