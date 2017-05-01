/*************************************************************************
	> File Name: contains_duplicate.c
	> Brief: 
	> Author: Chen Kai(ischenkai@qq.com)
	> Home: http://www.chenkai.me
	> Created Time: 2017年05月01日 星期一 15时37分53秒
 ************************************************************************/
/*************************************************************************
Given an array of integers, find if the array contains any duplicates. Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.

Subscribe to see which companies asked this question.
 ************************************************************************/
#include<stdio.h>

/*
 * Brief:
 * Params:
 * Return:
 * Author: Chen Kai(ischenkai.com)
 * Created Time:  2017年05月01日 星期一 15时38分39秒
 */
bool containsDuplicate(int* nums, int numsSize)
{
    for(int i = 0; i < numsSize; ++i)
    {
        for(int j = i + 1; j < numsSize; ++j)
        {
            if(nums[i] == nums[j]) return true;
        }
    }
    return false;
}

int main()
{
    return 0;
}
