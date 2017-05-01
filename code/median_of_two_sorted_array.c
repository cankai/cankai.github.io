/*************************************************************************
	> File Name: median_of_two_sorted_array.c
	> Brief:
	> Author: Chen Kai(ischenkai@qq.com)
	> Home: http://www.chenkai.me
	> Created Time: 2017年05月01日 星期一 16时38分17秒
 ************************************************************************/

/*************************************************************************
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    //merge the two arrays into one then return the middle
    if(nums1Size == 0 && nums2Size ==0) return 0.0;
    int *new_array = (int*)malloc(sizeof(int) * (nums1Size + nums2Size));
    int i = 0, j = 0;
    int *back = NULL;
    for(; i < nums1Size && j < nums2Size;)
    {
        if(nums1[i] < nums2[j])
        {
            new_array[i + j] = nums1[i];
            ++i;
        }
        else
        {
            new_array[i + j] = nums2[j];
            ++j;
        }
    }
    int new_array_last = i + j - 1;
    if(i < nums1Size)
    {
        while(i < nums1Size)
        {
            new_array[++new_array_last] = nums1[i++];
        }
    }
    else if(j < nums2Size)
    {
        while(j < nums2Size)
        {
            new_array[++new_array_last] = nums2[j++];
        }
    }
    if(new_array_last % 2 == 0)
    {
        return new_array[new_array_last/2];
    }
    else
    {
        return (new_array[new_array_last/2] + new_array[new_array_last/2 + 1])/2.0;
    }
}

int main()
{
    int a[3] = {1,2,3};
    int b[6] = {1,2,3,4,5,6};
    printf("%f\n",findMedianSortedArrays(a, 0, b, 0));
    printf("%f\n",findMedianSortedArrays(a, 0, b, 4));
    printf("%f\n",findMedianSortedArrays(a, 3, b, 6));
    printf("%f\n",findMedianSortedArrays(a, 3, b, 0));
    int c[]= {1,3};
    int d[]= {2};
    printf("%f\n",findMedianSortedArrays(c, 2, d, 1));
}
