/*************************************************************************
	> File Name: quick_sort.c
	> Brief: 
	> Author: Chen Kai(ischenkai@qq.com)
	> Home: http://www.chenkai.me
	> Created Time: 四  5/11 10:25:30 2017
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
void swap(int *a, int *b)
{
        int tmp = *a;
        *a = *b;
        *b = tmp;

}

void quick_sort(int array[], int n)
{
        if(n <= 1)//递归终点
            return;
        int key = array[0];//key 设置为数组第一个元素，可以随机设置，确保算法下限不至于崩掉
        int last = 0;//分割线，last左边小于等于key，last到i大于key
        for(int i = 1; i < n; ++i)
        {
                if(array[i] < array[0])
                    swap(&array[i], &array[++last]);
            
        }
        swap(&array[0], &array[last]);
        quick_sort(array, last);
        quick_sort(array + last + 1, n - last - 1);

}

void print_array(int array[], int size)
{
    for(int i = 0; i < size; ++i)
    {
        printf(" %d",array[i]);
    }
    printf("\n");
}
int compareInts(const void* a, const void* b)
{
    return *(const int *)a - *(const int *)b;
}
int main()
{
    int a[]={7, 8, 4, 2, 7, 8, 6, 2, 6, 7, 6, 7, 4, 3};
    print_array(a, sizeof(a)/sizeof(a[0]));
    quick_sort(a, sizeof(a)/sizeof(int));
    //qsort(a, sizeof(a)/sizeof(a[0]), sizeof(a[0]), compareInts);
    print_array(a, sizeof(a)/sizeof(a[0]));
}
