/*************************************************************************
	> File Name: list.cpp
	> Brief: 
	> Author: Chen Kai(ischenkai@qq.com)
	> Home: http://www.chenkai.me
	> Created Time: 三  5/17 14:12:43 2017
 ************************************************************************/
#include<iostream>
using namespace std;
typedef struct Node Node;
struct Node
{
    int value;
    Node* next;
    Node(int item, Node* next):value(item),next(next){}
};

void printv(Node* item, void *arg)
{
    char* fmt = (char*)arg;
    printf(fmt, item->value);
}
void apply(Node* list, void(*fn)(Node*, void*), void *arg)
{
    for(;list != NULL; list = list->next)
    {
        (*fn)(list, arg);
    }
}

Node* reverse_list(Node* list)
{
    Node* n = new Node(0, NULL);
    Node* new_list = n;
    while(list)
    {
        Node* next = list->next;
        Node* new_next = new_list->next;
        new_list->next = list;
        list->next = new_next;
        list = next;
    }
    return n->next;
}
Node* merge_list(Node* list1, Node* list2)
{
    Node* n = new Node(0, NULL);
    Node* new_list = n;
    while(list1 && list2)
    {
        if(list1->value > list2->value)
        {
            new_list->next = list1;
            list1 = list1->next;
        }
        else
        {
            new_list->next = list2;
            list2 = list2->next;
        }
        new_list = new_list->next;
    }
    if(list1)
    {
        new_list->next = list1;
    }
    else if(list2)
    {
        new_list->next = list2;
    }
    return n->next;
}
int main()
{
    Node n1(2, NULL);
    Node n2(3, &n1);
    Node n3(7, &n2);
    Node n4(12, &n3);
    Node n5(23, &n4);
    Node n6(23, &n5);
    Node n7(199, &n6);
    Node* list = &n7;
    Node nn1(2, NULL);
    Node nn2(9, &nn1);
    Node nn3(17, &nn2);
    Node nn4(22, &nn3);
    Node nn5(33, &nn4);
    Node nn6(43, &nn5);
    Node nn7(52, &nn6);
    Node* list2 = &nn7;
    apply(list, printv, (void*)"%d->");
    printf("\n");
    apply(list2, printv, (void*)"%d->");
    printf("\n");
    Node* new_list = merge_list(list, list2);
    apply(new_list, printv, (void*)"%d->");
    printf("\n");
    Node* rlist = reverse_list(new_list);
    apply(rlist, printv, (void*)"%d->");
    printf("\n");
    return 0;
}


