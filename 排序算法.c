#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<assert.h>
#define MAXSIZE 10                                                               //定义长度，可修改进行多种测试
void fileadd(long length, char numfile[]) {                                     //将数据备份进入文件中，后续测试各个排序算法的排序时间
    FILE* fp;
    fopen_s(&fp, numfile, "w");
    if (fp == NULL) {
        printf("打开文件失败");
        return;
    }
    int* temp = (int*)malloc(sizeof(int) * length);
    srand(time(NULL));
    for (long i = 0; i < length; i++)
        temp[i] = rand() % MAXSIZE;                        //向文件填充length个随机数，后续方便判定算法时间快慢，区间为  0——MAXSIZE/10，可修改
    fwrite(temp, sizeof(int), length, fp);
    fclose(fp);
    free(temp);
    return;

}
void filepop(int arr[], long length, char numfile[]) {
    FILE* fp;
    fopen_s(&fp, numfile, "r+");
    if (fp == NULL) {
        printf("打开文件失败");
        return;
    }
    fread(arr, sizeof(int), length, fp);                    //从文件中读取数据到数组中
    fclose(fp);
    return;
}
int Max(int arr[],long length) {                          //查找数组最大值函数
    int max = 0;
    for (int j = 0; j < length; j++)
        if (max < arr[j])max = arr[j];
    return max;
}
void initarr(int arr[], long length) {                 //设置数组随记数
    srand(time(NULL));
    for (long i = 0; i < length; i++)
        arr[i] = rand() % (MAXSIZE)+1;                  //为数组填充随机数，区间为  0——MAXSIZE/10，可修改
    return;
}
void Showarr(int arr[], long length) {                  //输出数组函数
    for (long i = 0; i < length; i++)
        printf("%d ", arr[i]);
    return;
}
//插入排序
void InsertSort(int arr[], long length) {

    long i = 1, j, key;          //设置计数i，移动光标，从第二个数字开始，j是记录i前的数字下标，key是暂时储存下标为i的数据
    for (; i < length; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {              //判断对应下标j数据是否比i大，大则往前一位移动
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;                             //遇到比a[i]小的数字时，就将a[i]的数据放到他的前一位，这样在第i个数据前的数据就排列好了
    }                                               //依次反复，直到排序完成
    return;
}
//快排（递归版）
void QuickSort(int arr[], long left, long right) {
    if (left >= right)return;                       //如果左边下标大于等于右边，就证明只存在一个数据，不需要排序了，直接跳出
    long i = left, j = right;                        //i记录左边光标，j记录右边光标
    long pivot = arr[i];                             //选取最左端为中心轴
    while (i < j) {                                 //如果两指针未相遇，则一直进行操作，直至相遇
        while (i<j && arr[j]>pivot)j--;             //右边指针先移动，在不相遇，寻找比中心轴小的数
        arr[i] = arr[j];                            //将这个数据放到a[i]的位置
        while (i < j && arr[i] <= pivot)i++;        //右边走了一步，轮到左边移动，在不相遇，寻找比中心轴大的数
        arr[j] = arr[i];                             //将这个数据放到a[j]的位置上
    }
    arr[i] = pivot;                                 //将中心轴数据放到两光标位置上
    QuickSort(arr, left, i - 1);                     //递归思想，不断分解，直到全部排好序
    QuickSort(arr, i + 1, right);
    return;
}
//基数计数排序
void RadixCountSort(int arr[], long length) {
    int max = Max(arr, length);                             //求出数组的最大值
    int temp[10][MAXSIZE];
    for (int i = 0; i < 10; i++)                           //集体赋初值
        memset(temp[i], 0, sizeof(int) * MAXSIZE);
    int i, j, pow;                                          //记录位数，i为arr数组的下标，pow为二维数组temp的行坐标，j为列数下标
    for (int k = 10; k <= max*10; k *= 10) {                 //从个位数开始，依次从低到高位进行计数排序
        for (i = 0; i < length; i++) {                      //此时i为数组arr的遍历下标
            j = 0;
            pow = arr[i] % k / (k / 10);                    //pow作为当前位数的数字，如13，个位就取3，十位就取1
            while (temp[pow][j])                            //当该槽不为0时，j++
                j++;
            temp[pow][j] = arr[i];                          //将此时的arr数据暂存排列到temp这个二维数组里面
        }
        i = 0;                                           
        for (pow = 0; pow < 10; pow++) {
            for (j = 0; j < length && temp[pow][j] != 0; j++) {       //按照当前的位数，从小到大放到arr数组中，然后该位置temp赋值为0
                arr[i++] = temp[pow][j];
                temp[pow][j] = 0;
            }
        }
    }
    return;
}
//计数排序
void CountSort(int arr[], long length) {
    int max = Max(arr, length);                             //求出数组的最大值
    int* temp = (int*)malloc(sizeof(int) * (max+1));        //申请计数空间,要把0也加进去当一个数
    memset(temp, 0, sizeof(int) * (max + 1));
    for (int i = 0; i < length; i++)                    //遍历数组，记录数据出现次数，用temp数组下标来记录
        temp[arr[i]]++;
    for (int i = 0, j = 0; i <= max; i++)                //将数据放回数组中，temp计数不为零就将对应下标填到数组arr中排序
        while (temp[i]--)
            arr[j++] = i;
    free(temp);         //释放空间
    return;
}
//归并排序
void merge(int arr[], long low, long middle, long height, int temp[]) {           //归并函数的合并函数，temp是暂存数组，low，middle，height为低，中，高位
    long i = low, j = middle + 1, k = low;                                     //数组两部分，从小到大分别组合
    while (i <= middle && j <= height)                                        //如果都没到尽头，则运行
        temp[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];                   //哪个小哪个就放到temp的数组卡位，并且其遍历数+1
    while (i <= middle)                                                     //剩余没遍历完的元素直接放到temp暂存数组的后面
        temp[k++] = arr[i++];
    while (j <= height)
        temp[k++] = arr[j++];
    for (long i = low; i <= height; i++)
        arr[i] = temp[i];                                                 //将已经排好序的数据返回给原数组arr【】
    return;
}
void Merge(int arr[], long low, long height, int temp[]) {                  //分割数组函数，递归思想，将数组分为单个元素再组合起来排序
    if (low >= height)return;                                           //如果元素分割仅有一个，则停止分割
    long middle = low + (height - low) / 2;                            //设置中间位置middle，不用（low+height）/2是为了防止越界
    Merge(arr, low, middle, temp);                                     //对当前数组前半部分分割
    Merge(arr, middle + 1, height, temp);                             //对当后数组前半部分分割
    merge(arr, low, middle, height, temp);                          //分割完成后对当前数组进行组合归并排序
    return;
}
void MergeSort(int arr[], long length) {                           //归并排序开始函数
    int* temp = (int*)malloc(sizeof(int) * MAXSIZE);              //申请空间，创建临时暂存数组
    assert(temp);                                                //检测暂存输出是否出错，出错立即中断程序
    Merge(arr, 0, length - 1, temp);                              //开始拆分，合并，排序
    free(temp);                                                //释放临时数组的空间
    return;
}
//操作菜单
void Menu()
{
    printf("\n=========[排列算法操作菜单]============\n");
    printf("[A/a]-插入排序\n");
    printf("[B/b]快排递归版\n");
    printf("[C/c]基数计数排序\n");
    printf("[D/d]计数排序\n");
    printf("[E/e]归并排序\n");
    printf("[F/f]修改节点数据\n");
    printf("[空格]-退出\n");
    printf("=================================\n");
    printf("\n输出需要检测的函数算法\n");
}
int main() {
    long n, length; int arr[MAXSIZE];
    n = sizeof(arr) / sizeof(arr[0]);           //测量数组长度n
    char numfile[100] = "C:/Users/86180/Desktop/numfile.txt";           //储存排序数的文件
    printf("\n是否需要重置随机数文件？需要则输入‘0’\n");
    if (getchar() == '0') {
        printf("\n请输入需要的随机数个数\n");
        scanf_s("%d", &length);
        if (length < n) {
            printf("\n随机数个数不得少于需排序数组长度！！！\n");
            return 0;
        }
        fileadd(length, numfile);                         //将随机数先输入文件中                      
    }
    printf("\n是否直接从文件读取数据？输入‘1’\n否则随机数输入数组\n");
    getchar();                                                                      //至于为什么那么间隔无用的getchar，是消除前面getchar对后者判断的影响
    if (getchar() == '1')
        filepop(arr, n, numfile);                                                //从文件中读取随记数，观察不同算法对于一样排序时的用时
    else
        initarr(arr, n);
    getchar();                                                                   //为数组arr【】放入随机数，测试单一算法时使用
    Showarr(arr, n);                                                           //展示数组初始状态
    Menu();                                                                   //展示功能菜单
    clock_t start = 0, time = 0;                                                 //计算运行时间，运用时间函数
    switch (getchar())                                                         //选择一个排序测试
    {
    case 'A':
    case 'a':  start = clock();                                             //将start = clock(); 放在函数实现前，使运行时间记录更加准确
        InsertSort(arr, n);                     //插入排序
        break;
    case 'B':
    case 'b':  start = clock();
        QuickSort(arr, 0, n - 1);               //快排递归排序
        break;
    case 'C':
    case 'c':  start = clock();
        RadixCountSort(arr, n);                 //基数计数排序
        break;
    case 'D':
    case 'd':  start = clock();
        CountSort(arr, n);                      //计数排序
        break;
    case 'E':
    case 'e': start = clock();
        MergeSort(arr, n);                      //归并排序
        break;
    case 'F':
    case 'f':                                   //排序
        break;
    }
    time = clock() - start;
    printf("\n\n所用时间为：%d  ms\n\n", time);
    Showarr(arr, n);
    return 0;
}