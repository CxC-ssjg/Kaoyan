#include <stdio.h>
#include <stdlib.h>

// 定义链表
typedef struct _LinkList {
    int data;
    struct _LinkList* next;
}LNode, *LinkList;


// 初始化一个链表
LinkList Init() {
    LinkList head = (LNode *)malloc(sizeof(LNode));
    head->next = NULL;
    return head;
}


// 采用头插法
void HeadInsert(LinkList L, int data) {
    LNode* p = (LNode *)malloc(sizeof(LNode));
    p->data = data;
    p->next = L->next;
    L->next = p;
}


// 链表反转
void reverse(LinkList L) {
    LNode *cur = L->next, *pre = NULL;
    if (L->next == NULL || L->next->next == NULL) {
        return;
    }

    LNode* p = L->next->next;
    L->next = NULL;

    while (p != NULL) {
        cur->next = pre;
        pre = cur;
        cur = p;
        p = p->next;
    }
    cur->next = pre;
    L->next = cur;
}


// 用链表存储数据
void OrganizeLinkList(LinkList L, int data) {
    while (data != 0) {
        int num = data % 10;
        HeadInsert(L, num);
        data = data / 10;
    }
}


// 实现两数相加
LinkList AddNums(LinkList L1, LinkList L2) {
    LinkList L = Init();
    reverse(L1);
    reverse(L2);
    LNode *p = L1->next, *q = L2->next;
    int flag = 0;
    while (p && q) {
        int num = 0;
        if (flag == 1) {
            num++;
        }
        
        if (num + p->data + q->data >= 10) {
            flag = 1;
        } else {
            flag = 0;
        }

        num += p->data + q->data;
        num = num % 10;

        HeadInsert(L, num);

        p = p->next;
        q = q->next;
    }
    
    if (p) {
        while (p) {
            int num = 0;
            if (flag == 1) {
                num++;
            }

            if (num + p->data >= 10) {
                flag = 1;
            } else {
                flag = 0;
            }

            num += p->data;
            num %= 10;
            HeadInsert(L, num);
            p = p->next;
        }
    } else if (q) {
        while (q) {
            int num = 0;
            if (flag == 1) {
                num++;
            }

            if (num + q->data >= 10) {
                flag = 1;
            } else {
                flag = 0;
            }

            num += q->data;
            num %= 10;
            HeadInsert(L, num);
            q = q->next;
        }
    }

    return L;
}


void Print(LinkList L) {
    LNode* p = L->next;
    while (p) {
        printf("%d\t", p->data);
        p = p->next;
    }
}

int Cal(LinkList L) {
    LNode* p = L->next;
    int num = 0;

    while (p) {
        num = num * 10 + p->data;
        p = p->next;
    }

    return num;
}


int main() {
    LinkList L1 = Init();
    LinkList L2 = Init();
    OrganizeLinkList(L1, 12345678);
    OrganizeLinkList(L2, 1);
    LinkList L = AddNums(L1, L2);
    Print(L);
    printf("\n%d\n", Cal(L));
    return 0;
}
