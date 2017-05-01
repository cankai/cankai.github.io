/*************************************************************************
	> File Name: two_sum.c
	> Brief: 
	> Author: Chen Kai(ischenkai@qq.com)
	> Home: http://www.chenkai.me
	> Created Time: 2017年05月01日 星期一 15时19分28秒
 ************************************************************************/
/*************************************************************************
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
 ************************************************************************/
#include<stdio.h>


/*
 * Brief: find the 
 * Params:
 * Return:
 * Author: Chen Kai(ischenkai.com)
 * Created Time:  2017年05月01日 星期一 15时20分29秒
 */
int* twoSum(int* nums, int numsSize, int target) 
{
    int *num_index = (int*)malloc(sizeof(int) * 2);
    for(int i = 0; i < numsSize; ++i)
    {
        for(int j = i + 1; j < numsSize; ++j)
        {
            int sum = nums[i] + nums[j];
            if(sum == target)
            {
                num_index[0] = i;
                num_index[1] = j;
                return num_index;
            }
        }
    }
    return (int*)NULL;
}

int main()
{
    return 0;
}
//done it in 9 minutes
