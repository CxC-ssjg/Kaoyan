#include <stdio.h>
#include <stdlib.h>
#define MAX_TREE_NODES (1 << 8)  // “<<”是位运算符, 位运算都是按二进制来计算的, 这里是1左移8位换算成十进制就是2的8次方

// 注意这里实现的是满二叉树, 如果实现二叉树尽量用链表实现, 数组会很浪费空间

typedef int ElemType;

typedef struct _Node {
	ElemType data;
}Node;

typedef struct _BinaryTree {
	int num;
	Node* n[MAX_TREE_NODES];
}BinaryTree;

void InitBinaryTree(BinaryTree *tree) {
	for (int i = 0; i < MAX_TREE_NODES; i++) {
		tree->n[i] = NULL;
	}
}

Node* CreateNode(ElemType data) {
	Node* n;
	n = malloc(sizeof(Node));

	// 如果内存申请成功
	if (n) {
		n->data = data;
	}

	return n;
}

void OrganizeATree(BinaryTree* tree) {
	int data[10] = {5, 8, 2, 9, 10, 1, 6, 3, 4, 7};

	InitBinaryTree(tree);

	// 从下标1开始存储, 为什么从1, 树上说的很清楚了, 为了更好地得出二叉树结点之间的关系, 这样可以根据索引值来计算该结点的双亲结点或者子结点的索引值
	for (int i = 1; i <= 10; i++) {
		tree->n[i] = CreateNode(data[i - 1]);
	}

	tree->num = 10;
}

// 中序遍历
void _InOrder(BinaryTree* tree, int index) {
	if (!tree->n[index]) {
		return;
	}

	// 该结点的左子树结点对应下标是index * 2, 右子树下标是index * 2 + 1
	_InOrder(tree, index * 2);

	printf("[%2d]: %4d\n", index, tree->n[index]->data);

	_InOrder(tree, index * 2 + 1);
}

void InOrder(BinaryTree *tree) {
	_InOrder(tree, 1);
}

int main() {
	BinaryTree tree;

	OrganizeATree(&tree);
	InOrder(&tree);

	return 0;
}	
