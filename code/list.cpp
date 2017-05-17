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
int main()
{
    Node n1(2, NULL);
    Node n2(9, &n1);
    Node n3(7, &n2);
    Node n4(22, &n3);
    Node n5(3, &n4);
    Node n6(23, &n5);
    Node n7(12, &n6);
    Node* list = &n7;
    apply(list, printv, (void*)"%d->");
    sort(list);
    apply(list, printv, (void*)"%d->");
    return 0;
}


