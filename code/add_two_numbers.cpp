/*************************************************************************
	> File Name: add_two_numbers.cpp
	> Brief: 
	> Author: Chen Kai(http://www.chenkai.me)
	> Mail: ischenkai@qq.com
	> Created Time: 一  6/ 5 20:20:20 2017
    > Ended Time: 20:44
 ************************************************************************/
#include<iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* reverse_list(ListNode* list)
{
    ListNode* n = new ListNode(0);
    ListNode* new_list = n;
    while(list)
    {
        ListNode* next = list->next;
        ListNode* new_next = new_list->next;
        new_list->next = list;
        list->next = new_next;
        list = next;
    }
    ListNode* rt = n->next;
    delete n;
    return rt;
}

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        //first revere the two list
        ListNode* nl1 = reverse_list(l1);
        ListNode* nl2 = reverse_list(l2);
        ListNode* rt = new ListNode(0);
        ListNode* tail = rt;
        //then add it;
        int flag = 0;
        while(nl1 && nl2)
        {
            int val = (flag + nl1->val + nl2->val)%10;
            flag = (flag + nl1->val + nl2->val)/10;
            ListNode* n = new ListNode(val);
            tail->next = n;
            tail = n;
            nl1 = nl1->next;
            nl2 = nl2->next;
        }
        while(nl1)
        {
            int val = (flag + nl1->val)%10;
            flag = (flag + nl1->val)/10;
            ListNode* n = new ListNode(val);
            tail->next = n;
            tail = n;
            nl1 = nl1->next;
        }
        while(nl2)
        {
            int val = (flag + nl2->val)%10;
            flag = (flag + nl2->val)/10;
            ListNode* n = new ListNode(val);
            tail->next = n;
            tail = n;
            nl2 = nl2->next;
        }
        if(flag == 1)
        {
            ListNode* n = new ListNode(1);
            tail->next = n;
        }
        ListNode* rt2 = reverse_list(rt->next);
        delete rt;
        return rt2;
    }
};

int main()
{
    return 0;
}

