/*************************************************************************
	> File Name: my_list.c
	> Brief: 
	> Author: Chen Kai(http://www.chenkai.me)
	> Mail: ischenkai@qq.com
	> Created Time: 日  5/ 7 20:52:23 2017
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Nameval Nameval;

struct Nameval {
    char* name;
    int value;
    Nameval *next;
};

Nameval *newitem(char *name, int value)
{
    Nameval *newp;
    newp = (Nameval*)malloc(sizeof(Nameval));
    newp->name = name;
    newp->value = value;
    newp->next = NULL;
    return newp;
}
Nameval* addfront(Nameval* listp, Nameval* newp)
{
    newp->next = listp;
    return newp;
}
Nameval* addend(Nameval* listp, Nameval* newp)
{
    if(listp == NULL)
    {
        return newp;
    }
    Nameval* p;
    for(p = listp; p->next != NULL; p = p->next){}
    return listp;
}
Nameval* lookup(Nameval* listp, char* name)
{
    for(; listp != NULL; listp = listp->next)
    {
        if(strcmp(name, listp->name) == 0)
        {
            return listp;
        }
    }
    return NULL;
}

void apply(Nameval* listp, void(*fn)(Nameval*,void*), void* arg)
{
    for(; listp != NULL; listp = listp->next)
    {
        (*fn)(listp, arg);
    }
}

int itemcmp(void* item1, void* item2)
{
    Nameval* i1 = item1;
    Nameval* i2 = item2;
    if(i1->value == i2->value)
        return 0;
    else if(i1->value > i2->value)
        return 1;
    else
        return -1;
}

void printv(Nameval* p, void* arg)
{
    char* fmt;
    fmt = (char*)arg;
    printf(fmt, p->name, p->value);
}

void inccounter(Nameval* p, void* arg)
{
    int* ip;
    ip = (int*)arg;
    (*ip)++;
}

void freeall(Nameval* listp)
{
    Nameval* next;
    for(; listp != NULL; listp = next)
    {
        next = listp->next;
        free(listp);
    }
}

Nameval* delitem(Nameval* listp, char* name)
{
    //lookup 
    Nameval *pre;
    Nameval *p;
    for(p = listp; p != NULL; p = listp->next)
    {
        if(strcmp(name, p->name) == 0)
        {
            if(pre == NULL)
                listp = p->next;
            else
                pre->next = p->next;
            free(p);
            return listp;
        }
        pre = p;
    }
    return NULL;
}

Nameval* copy(Nameval* lists, Nameval* listd)
{
    for(; lists != NULL; lists = lists->next)
    {
    }
}

Nameval* merge(Nameval* listp1, Nameval* listp2)
{
    if(listp1 == NULL)
    {
        return listp2;
    }
    if(listp2 == NULL)
    {
        return listp1;
    }
    Nameval * listp;
    int listcmpr = itemcmp(listp1, listp2);
    if(listcmpr > 0)
    {
        listp = listp2;
        listp->next = merge(listp1, listp2->next);
    }
    else
    {
        listp = listp1;
        listp->next = merge(listp1->next, listp2);
    }
    return listp;
}
Nameval* merge2(Nameval* listp1, Nameval* listp2)
{
    if(listp1 == NULL)
    {
        return listp2;
    }
    if(listp2 == NULL)
    {
        return listp1;
    }
    Nameval * listp;
    Nameval* p1 = listp1;
    Nameval* p2 = listp2;
    int listcmpr = itemcmp(listp1, listp2);
    if(listcmpr > 0)
    {
        listp = listp2;
    }
    else
    {
        listp = listp1;
    }
    Nameval* listpe = listp;
    while(p1 && p2)
    {
        if(p1->value < p2->value)
        {
            listpe->next = p1;
            listpe = p1;
            p1 = p1->next;
        }
        else
        {
            listpe->next = p2;
            listpe = p2;
            p2 = p2->next;
        }
    }
    while(p1)
    {
        listpe->next = p1;
        listpe = p1;
        p1 = p1->next;
    }
    while(p2)
    {
        listpe->next = p2;
        listpe = p2;
        p2 = p2->next;
    }
    return listp;
}

Nameval* revers(Nameval* listp)
{
    if(!listp || !listp->next)
        return listp;
    Nameval* listp1 = listp;
    Nameval* listp2 = listp->next;
    listp1->next = NULL;
    while(listp2)
    {
        Nameval* next = listp2->next;
        listp2->next = listp1;
        listp1 = listp2;
        listp2 = next;
    }
    return listp1;;
}
