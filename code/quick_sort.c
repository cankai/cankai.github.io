/*************************************************************************
	> File Name: quick_sort.c
	> Brief: 
	> Author: Chen Kai(ischenkai@qq.com)
	> Home: http://www.chenkai.me
	> Created Time: 四  5/11 10:25:30 2017
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>

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
    qsort(a, sizeof(a)/sizeof(a[0]), sizeof(a[0]), compareInts);
    print_array(a, sizeof(a)/sizeof(a[0]));
}
