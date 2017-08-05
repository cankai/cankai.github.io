/*************************************************************************
	> File Name: odd_even_linked_list.cpp
	> Brief: 
	> Author: Chen Kai(http://www.chenkai.me)
	> Mail: ischenkai@qq.com
	> Created Time: 一  6/ 5 21:00:56 2017
 ************************************************************************/
#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        //先分割List 为一个odd，一个even
        //再合并
        ListNode* odd = new ListNode(0);
        ListNode* odd_tail = odd;
        ListNode* even = new ListNode(0);
        ListNode* even_tail = even;
        while(head)
        {
            //even
            if(head->val%2 == 0)
            {
                even_tail->next = head;
                even_tail = head;
            }
            else//odd
            {
                odd_tail->next = head;
                odd_tail = head;
            }
            head = head->next;
        }
        odd_tail->next = even->next;
        ListNode* rt = odd->next;
        delete odd;
        delete even; return rt; }
};
