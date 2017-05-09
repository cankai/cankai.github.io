/*************************************************************************
	> File Name: head_sort.c
	> Brief: 
	> Author: Chen Kai(ischenkai@qq.com)
	> Home: http://www.chenkai.me
	> Created Time: 2017年05月08日 星期一 10时25分50秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#define LENGTH(array) ( (sizeof(array)) / (sizeof(array[0])) )
#define swap(a,b) (a^=b,b^=a,a^=b)
void maxheapdown(int a[], int start, int end)
{
    #if 0
    int c = start;            // 当前(current)节点的位置
    int l = 2*c + 1;        // 左(left)孩子的位置
    int tmp = a[c];            // 当前(current)节点的大小
    for (; l <= end; c=l,l=2*l+1)
    {
        // "l"是左孩子，"l+1"是右孩子
        if ( l < end && a[l] < a[l+1])
            l++;        // 左右两孩子中选择较大者，即m_heap[l+1]
        if (tmp >= a[l])
            break;        // 调整结束
        else            // 交换值
        {
            a[c] = a[l];
            a[l]= tmp;
        }
    }
    #endif
    #if 1
    int c = start;
    int l = 2*c + 1;
    int tmp = a[c];
    for(; l <= end; c = l, l = 2*l+1)
    {
        if(l<end && a[l] < a[l+1])
            l++;
        if(tmp >= a[l])
            break;
        else
        {
            a[c] = a[l];
            a[l] = tmp;
        }
    }
    #endif
}

void heapsort(int array[], int n)
{
    int i;
    //build heap
    for(i = n/2-1; i >= 0; --i)
    {
        maxheapdown(array, i, n-1);
    }
    printf("\n");
    for (i=0; i<8; i++)
        printf("%d ", array[i]);
    printf("\n");
    for(int i = n-1; i>0; --i)
    {
        swap(array[0], array[i]);
        maxheapdown(array, 0, i-1);
    }
}


int main()
{
    int i;
    int a[] = {20,30,90,40,70,110,60,10,100,50,80};
    int ilen = LENGTH(a);

    printf("before sort:");
    for (i=0; i<ilen; i++)
        printf("%d ", a[i]);
    printf("\n");

    heapsort(a, ilen);            // 升序排列
    //heap_sort_desc(a, ilen);        // 降序排列

    printf("after  sort:");
    for (i=0; i<ilen; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
