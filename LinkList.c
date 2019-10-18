#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;


// 定义结点结构体, 并为这个结构体起了LinkNode别名, 和这个结构体指针类型的别名
typedef struct _Node {
	ElemType data;
	struct _Node *next;
}LinkNode, *LinkList;


// 创建一个带有头结点的单链表
LinkList InitLinkList() {
	LinkNode *head;
	head = (LinkNode *)malloc(sizeof(LinkNode));  // 为头结点申请内存空间
	head->next = NULL;
	return head;
}


// 判断链表是否为空
bool isEmpty(LinkList L) {
	if (L->next == NULL) {
		return true;
	}
	return false;
}


// 头插法
void HeadInsert(LinkList L, ElemType x) {
	LinkNode *p;
	p = (LinkNode *)malloc(sizeof(LinkNode));
	p->data = x;
	p->next = L->next;
	L->next = p;
}


// 尾插法
void TailInsert(LinkList L, ElemType x) {
	LinkNode *p, *q = L->next;
	p = (LinkNode *)malloc(sizeof(LinkNode));
	p->data = x;
	
	// 如果该链表为空则直接将这个结点插到头结点后即可
	if (isEmpty(L)) {
		L->next = p;
		p->next = NULL;
		return;
	}
	
	while (q->next != NULL) {
		q = q->next;
	}

	q->next = p;
	p->next = NULL;
}

// 打印链表
void Print(LinkList L) {
	LinkNode *p = L->next;
	if (p == NULL) {
		printf("The LinList doesn't have data!\n");
	}

	printf("LinkList: %d", p->data);
	p = p->next;

	while (p) {
		printf(" -> %d", p->data);
		p = p->next;
	}
	printf("\n");
}

// 链表的反转
void reverse(LinkList L) {
	if (L->next == NULL) {
		printf("LinkList is NULL");
	}
	if (L->next->next == NULL) {
		return;
	}

	LinkNode *cur = L->next, *pre = NULL, *n = L->next->next;
	L->next = NULL; // 首先将头结点与链表分离
	while (n != NULL) {
		cur->next = pre;
		pre = cur;
		cur = n;
		n = n->next;
	}
	cur->next = pre;
	L->next = cur;
}

int main() {
	LinkList L1, L2;
	L1 = InitLinkList();
	L2 = InitLinkList();

	for (int i = 0; i < 10; i++) {
		TailInsert(L1, i);
		HeadInsert(L2, i);
	}
	
	printf("TailInsert:\n");
	Print(L1);
	printf("HeadInsert:\n");
	Print(L2);

	reverse(L1);
	printf("reverse linklist L1:\n");
	Print(L1);
	return 0;
}
