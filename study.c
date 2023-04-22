#include<stdio.h>
int main() {
	printf("hello github\n");
	return 0;
}

//
////バブルソート冒泡排序
//void Bubble sort(a[NUM]) {
//    int i, j;
//    for (i = Num - 1; i > 0; i--) {
//        for (j = 0; j < i - 1; j++) {
//            if (a[j] > a[j + 1]) {
//                swap(&a[j], &a[j + 1]);//交换
//            }
//        }
//    }
//}
//swap(int* x, int* y) {
//    int temp;
//    temp = *x;
//    *x = *y;
//    *y = temp;
//}
//
////挿入法
//int nums[NUM];
//int len = sizeof(nums) / sizeof(num[0]);
//int i, j;
//int temp;
//for (int i = 1; i < len; i++) {
//    int temp = nums[i];
//    int j = i;
//    while (j > 0) {
//        if (temp < nums[i - 1]) {
//            nums[j] = nums[j - 1];
//        }
//        else {
//            break;
//        }
//        j--;
//    }
//    num[j] = temp;
//}
//
//for (i = 1; i < NUM; i++) {
//    tmp = a[i];
//    for (j = i - 1; j > 0; j--) {
//        if (a[j] > tmp)
//            a[j + 1] = a[j];
//        else
//            break;
//    }
//    a[j + 1] = tmp;
//}
////クイックソート
//void quick_sort(int a[], int left, int right) {
//    int pl = left;
//    int pr = right;
//    int pivot = (a[pl] + a[pr]) / 2;
//    while (1) {
//        while (a[pl] < pivot) { pl++; }
//        while (a[pr] > pviot) { pr--; }
//        if (pl > pr)
//            break;
//        swap(&a[pl], &a[pr]);
//        pl++;
//        pr--;
//
//    }
//
//    if (left < pr)
//        quick_sort(a, left, pr);
//    if (pl < right)
//        quick_sort(a, pl, right);
//}
////乱数
//#include<time.h>
//srand(time(NUll));
//n = rand() % NUM + 1;
////二分探索
//int binary_search(int a[],int key) {
//    int pl, pr, pc;
//    pl = 0; pr = NUM - 1;
//    while (pl <= pr) {
//        pc = (pr + pl) / 2;
//        if (a[pc] < key)
//            pl = pc + 1;
//        else if (a[pc] > key)
//            pr = pc - 1;
//        else if (a[pc] = key)
//            return pc;
//    }
//    return -1;
//}
////list
////Delete Insert 配列
//#include<stdio.h>
//#define MAX 15
//void ShowList(int[]);
//int InsertNode(int, int, int[]);
//int DeleteNode(int, int[]);
//void main() {
//    int data[] = {
//        2,4,5,6,7,8,-1,-1,-1,-1,-1
//    };
//    int no, insdata,id;
//    ShowList(data);
//    printf("the positon");
//    scanf("%d", &no);
//    id = DeleteNode(no, data);
//    if (id == -1)
//        printf("defeat");
//    else {
//        printf("the  deleted number:%d",id);
//        ShowList(data);
//    }
//}
//int DeleteNOde(int no, int data[]) {
//    int n, i, tmp;
//    for (n = 0; n < MAX; n++) {
//        if (data[n] == -1)
//            break;
//    }
//    if (no < 0 || n <= no)
//        return -1;
//    else {
//        tmp = data[no];
//        for (i = no + 1; i < n; i++) {
//            data[i - 1] = data[i];
//        }
//        data[n - 1] = -1;
//        return tmp;
//    }
//}
//int InsertNode(int no, int insdata, int data[]) {
//    int n;
//    for (i = 0; i < MAX; i++) {
//        if (data[i] == -1)
//            break;
//    }
//    if (n == MAX) {
//        return -1;
//    }
//    else if (n < no) {
//        return-1;
//    }
//    else {
//        for (int i = n - 1; i >= no; i--) {
//            data[i + 1] = data[i];
//
//    }
//        data[no] = insdata;
//        return 0;
//    }
//}
////list 構造体
//struct student {
//    int id;
//    char name[20];
//    float heghit;
//    float weight;
//    int next_index;//つながり情報
//};
//typedef struct {
//    int IntData;
//    int NextIndex;
//}Mylist;
//void main() {
//    Mylist data[MAX];
//    for (int i = 0; i < MAX; i++) {
//        data[i].IntData = -1;
//        data[i].NextIndex = -1;
//    }
//    data[0].IntData = 12; data[0].NextIndex = 3;
//
//    Showlist(data);
//}
//
//void ShowList(Mylist data[]) {
//    printf("list");
//    int i = 0;
//    while (1) {
//        printf("%d\n", data[i].NextIndex);
//        i = data[i].NextIndex;
//        if (i == -1) break;
//    }
//}
////スタック　逆ポーランド
//#define STACK_SIZE 5
//#define NO_DATA -1
//int stack[STACK_SIZE];
//int top = -1;
//void ShowStack();
//int Push(int data);
//int Pop();
//void ShowStack() {
//    int i;
//printf("Stack:");
//for (i = 0; i <= top; i++) {
//    printf("[%d]", stack[i]);
//}
//printf("\n");
//}
//int Push(int data) {
//    top++;
//    if (top == STACK_SIZE) {
//        top--;
//        return -1;
//    }
//    else {
//        stack[top] = data;
//        return 0;
//    }
//}
//int Pop() {
//    if (top < 0)
//        return -1;
//    else {
//        int data = stack[top];
//        top--;
//        return data;
//    }
//}
////  キュー FIFO
//#define    QUEUE_SIZE 8
//int queue[QUEUE_SIZE];
//int front = 0;
//int rear = 0;
//int num = 0;
//void ShowQueue();
//int EnQueue(int data);
//int DeQueue();
//void ShowQueue() {
//    int i;
//    printf("Queue:");
//    for (i = 0; i < QUEUE_SIZE; i++) {
//        if (queue[i] != NO_DATA) {
//            printf("%4d", queue[i]);
//        }
//        else {
//            printf("[]");
//        }
//    }
//}
//int EnQueue(int data) {
//    if (num = QUEUE_SIZE)
//        return -1;
//    else {
//        queue[rear] = data;
//        rear++;
//        num++;
//        if (rear = QUEUE_SIZE)//环状数组的实现
//            rear = 0;
//        return(0);
//    }
//}
//int DeQueue() {
//    if (num == 0)
//        return -1;
//    else {
//        int data = queue[front];
//        queue[front] = NO_DATA;
//        front++;
//        num--;
//            if (front == QUEUE_SIZE)
//                front = 0;
//        return (data);
//    }
//}