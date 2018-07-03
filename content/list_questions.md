Title: 链表问题总结
Date: 2017-08-05 10:20
Category: 算法,数据结构
Tags: 链表,排序
Slug: linklist
Author: Chen Kai
Summary:  链表是最常用的一种数据结构，是一种线性表，数据在表里面并不是按线性的顺序存储，每个链表节点都有一个数据域，一个指针域，通过节点中的指针，来将所有的数据串接起来，由于不是顺序存储，所以链表的插入和删除效率高，为O(1)，访问特定节点的时间为O(n)；链表没有固定大小，可以灵活且充分的利用存储数据，并随时进行扩展和收缩；链表作为一种基础数据结构，在面试中几乎都会被考到。下面做了一些总结。

#### 导语
> 链表是最常用的一种数据结构，是一种线性表，数据在表里面并不是按线性的顺序存储，每个链表节点都有一个数据域，一个指针域，通过节点中的指针，来将所有的数据串接起来，由于不是顺序存储，所以链表的插入和删除效率高，为O(1)，访问特定节点的时间为O(n)；链表没有固定大小，可以灵活且充分的利用存储数据，并随时进行扩展和收缩；链表作为一种基础数据结构，在面试中几乎都会被考到。下面做了一些总结。

### 链表定义
```c
typedef struct Node Node;
struct Node
{
    int value;
    Node* next;
    Node(int item, Node* next=NULL):value(item),next(next){}
};
```

### 〇、链表创建
链表可以通过不停的在链表头或者尾插入节点来创建，当然也可以在任意位置插入。
```c
//在表头插入
Node* addFront(Node* list, Node* node)
{
    node->next = list;
    return node;
}

//在表尾插入
Node* addEnd(Node* list, Node* node)
{
    //找到表尾
    Node* p = list;
    if(list == NULL)
    {
        return node;
    }
    while(p->next != NULL)
    {
        p = p->next;
    }
    p->next = node;
    return list;
}
```
### 一、链表插入
在指定节点后插入节点
```c
void addAfterNode(Node* node, Node* new_node)
{
    Node *next = node->next;
    new_node->next = next;;
    node->next = new_node;
}

```
在指定节点前插入节点；在节点前插入节点会稍微麻烦一点，需要首先找到节点的前驱
```c
Node* addBeforeNode(Node* list, Node* node, Node* new_node)
{
    Node *pre = list;
    if(node == list)
    {
        return addFront(list, new_node);
    }
    else
    {
        while(pre->next != node)
        {
            pre = pre->next;
        }
        new_node->next = node;
        pre->next = new_node;
        return list;
    }
}
```
### 二、链表查找
```c
Node* findVal(Node* list, int val)
{
    while(list != NULL)
    {
        if(list->value != val)
        {
            list = list->next;
        }
        else
        {
            return list;
        }
    }
    return NULL;
}
```
### 三、链表删除
#### 1、删除链表中的指定节点
```c
Node* delNode(Node* list, Node* node)
{
    //首先，找到要删除节点的前驱，然后前驱指向后继，再删除节点
    //如果node 为首节点，没有前驱
    if(node* == list)
    {
        Node* new_head = list->next;
        delete node
        return new_head;
    }
    else
    {
        Node* p = list;
        while(p->next != node)
        {
            p = p->next;
        }
        p->next = node->next;
        delete node;
        return list;
    }
}
```
当节点不是尾节点的时候，可以通过节点数据替换，在常数时间内删除节点。
```c
Node* delNode(Node* list, Node* node)
{
    Node* next = node->next;
    node->data = next->data;
    node->next = next->next;
    delete next;
    return list;
}
```
#### 2、删除链表中的指定值的节点
删除指定值，可以将动作分解为两步,第一步：找到节点等于值得节点；第二步：删除节点
```c
Node* delVal(Node* list, int val)
{
    //find and delete
    while(list != NULL)
    {
        Node* dNode = findVal(list, val);
        if(dNode != NULL)
        {
            list = delNode(list, dNode);
        }
        else
        {
            break;
        }
    }
    return list;
}
```
### 四、链表逆转
链表逆转本质上，相当于不停地在链表头前插入新节点
```c
Node* reverseList(Node* list)
{
    Node* newList = NULL;
    Node* newHead = list;
    while(list != NULL)
    {
        Node* next = list->next;
        newHead = addFront(newList, list);
        list = next;
    }
    return newHead;
}
```
链表逆转还可以通过递归来解决
```c
Node* reverseList(Node* list)
{
    if(list !== NULL && list->next != NULL)
    {
        return list;
    }
    Node* newHead = reverseList(list->next);
    list->next->next = list;
    list->next = NULL;
    return newHead;
}
```

### 五、链表归并
链表归并，讲两条不相交的已排序链表合并为一条新链表，相当于从两个列表从选出一个节点，然后将节点插入在尾节点后
```c
Node* combineList(Node* list1, Node* list2)
{
    Node* dummyNode = new Node();
    Node* new_head = dummyNode;
    Node* new_tail = new_head;
    while(list1 && list2)
    {
        Node* selectNode = NULL;
        if(compareNode(list1, list2))//return list1->value >= list2->value ? true : false;
        {
            selectNode = list1;
            list1 = list1->next;
        }
        else
        {
            selectNode = list2;
            list2 = list2->next;
        }
        addAfterNode(new_tail, selectNode);
        new_tail = selectNode;
    }
    new_tail->next = list1 ? list1 : list2;
    new_head = new_head->next;
    delete dummyNode;
    return new_head;
}
```
### 六、找链表中点
链表中点可以通过块慢指针找到中点。块指针每次向前走两步，慢指针每次向前走一步，当块指针走到链表尾部，慢指针的位置为中点位置
```c
Node* findMidd(Node* list)
{
    Node* fast = list;
    Node* slow = list;
    while(fast && fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
```
### 七、找链表倒数第N个节点
可以先获得链表长度为len，则链表倒数第N个节点为顺数第 len-N 个节点。还可以通过类似于块慢指针的方法，块指针先向前走N步，则块慢节点的距离就为N，然后快慢节点一起递推，当快节点到达尾节点，则慢节点为倒数第N个节点。
```c
Node* findRN(Node* list, int n)
{
    Node* fast = list;
    Node* slow = list;
    //块节点先走N步
    for(int i = 0; i != N; ++i)
    {
        fast = fast->next;
    }
    while(fast->next)
    {
        fast = fast->next;
        slow = slow->next;
    }
    return slow();
}
```
### 八、判断链表是否存在环
可以通过块慢指针技术，来判断是否存在环；快节点步长设置为2，慢节点步长设置为1，如果存在环，当块慢节点都进入环结构中时，由于是环形，假设慢指针在快指针前面，距离差为N，那么经历N轮迭代，快指针终究会追上慢指针，类似于田径场上的套圈。如果不存在环，则块指针会率先到达尾节点。
```c
bool hasCircle(Node* list)
{
    Node* fast = list;
    Node* slow = list;
    while(fast && fast->next && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if(slow == fast)
        {
            return true;
        }
    }
    return false;
}
```
### 九、找到链表环的入口
如果链表存在环，那么一定是快指针先进入环线，然后慢指针进入环线，假设进入环线的点是C，此时快指针的点为K，那么经过K-C个循环，快慢指针将重合,重合的时候如下图

![circle](https://i.loli.net/2017/08/05/5985d54601bd2.png "带环链表图")

设 begin 到 connect 的距离为lenBC, connect 到 together 的距离为lenCT，环的长度为lenCircle，那么两个指针在together重合的时候，慢指针走了lenBC + lenCT 个距离，块指针走了lenBC + lenCT + n x lenCircle，又因为快指针走的路程为慢指针的两倍，所以lenBC + lenCT = n x lenCircle；那么如果此时由一个指针从指针头出发，另外一个指针由together点出发，以相同的步长，它们一定会在connect再次重合。
```c
Node* findCircle(Node* list)
{
    //第一步，两个节点走到重合点
    Node* fast = list;
    Node* slow = list;
    //while(fast && fast->next && fast->next)
    //已知包含环路
    while(true)
    {
        fast = fast->next->next;
        slow = slow->next;
        if(slow == fast)
        {
            break;
        }
    }
    slow = list;
    while(slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

```
### 十、判断两个链表是否相交
如果两个链表存在相同的节点，那么链表一定相交，从相交点往尾节点，都是两个链表的共同部分，所以最方便的是直接找两个链表的尾节点，如果尾节点是相同的，那么两个链表一定相交。
```c
bool linkCross(Node* list1, Node* list2)
{
    Node* tail1 = findTail(Node* list1);
    Node* tail2 = findTail(Node* list2);
    return tail1 == tail2;
}
```

### 十一、找到两个链表的交点
如果两个链表相交，那么两个链表将组成一个Y形，将Y形的底的next指向任何一个枝链表的头，那么将转换为找链表环入口的问题。
