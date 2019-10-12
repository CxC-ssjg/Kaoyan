#include <stdio.h>
#include <stdbool.h>
#define MAXSIZE 100  // 宏定义， 把MAXSIZE看成一个值为100的常数	


typedef int ElemType;  // 给int一个别名，为什么要给int起别名呢? 想一想如果有一天我们写的这个代码保存的不是int类型的数据了，我想保存char类型的数据，是不是要把数据全部重新定义为char类型，如果我们在这给这个数据类型起了别名，我们需要改数据类型的时候我们只需要把这里的int改成你想要的数据类型，是不是很方便呢


// 定义结构体
typedef struct _SqList {
	ElemType data[MAXSIZE];  // 顺序存储其实就是定义一个数据，在结构体初始化时，gcc会自动为它分配内存空间, 只要跟我们要保存的数据有关的我们都用ElemType来定义
	int length;
}SqList;


// 初始化顺序表, 无返回数据, 关于函数需要传入的参数， 当我们要对传进的参数做改变的话，我们需要传入一个指针类型，才修改参数的值
void InitSqList(SqList *L) {
	L->length = 0;	
}


// 按给定索引查找值, 注意当我们需要返回一个bool类型的值时，需要引入stdbool.h这个头文件, 用result来保存查找的结果，注意为什么要传入result的指针，上面我说过了，如果要修改参数的值，必须传入指针
bool SearchByIndex(SqList L, int index, ElemType *result) {
	if (index < 0 || index >= L.length) {
		return false;  // 如果索引值不在顺序表中数组的下标范围内，那么我们查找失败
	}

	// 因为传入的是指针，(*result)代表取出这个指针指向的内存块中的值
	(*result) = L.data[index];
	return true;
}


// 通过值查找顺序表中其在顺序表中的索引值
bool SearchByValue(SqList L, ElemType value, int *index) {
	for (int i = 0; i < L.length; i++) {
		if (value == L.data[i]) {
			(*index) = i; // 切记，我们得到的是索引值，如果要得到该值在数组的第几个位置，那么我们需要对index + 1
			return true;  // 查找成功, 函数结束执行
		}
	}

	return false;  // 没有查到该值，因为for循环已经结束了但却没有return，说明这个值不在顺序表中
}


// 在第i个位置插入一个数据, 注意这里是第几个位置，不是索引值
void InsertByIndex(SqList *L, int index, ElemType value) {
	// 首先我们画个草图，如果我们要在索引值为i的位置上插入一个数据，那么原本在i上面的数据以及它后面的数据需要往后移动一个位置，这样才能空出索引i位置的空间，然后进行插入操作。也就是说我们分两个步骤，第一移动原始索引为i以及它后面的数据，第二步把我们想插入的数据插入到空出的位置里
	
	// 1.空出位置, 为什么从后面开始遍历，你画个草图就可以发现了，画图这个方法非常的重要！！！非常重要！！！记住！！！
	for (int i = L->length - 1; i >= index; i--) {
		L->data[i + 1] = L->data[i];
	}

	// 2.插入数值
	L->data[index] = value;

	// 最后别忘了插入了一个数值顺序表长度加1
	L->length++;
}


// 删除索引为i的数据
void DeleteByIndex(SqList *L, int index, ElemType *value) {
	(*value) = L->data[index]; // 通过这个函数将索引值为i的得到value的值
	
	for (int i = index; i < L->length - 1; i++) {
		L->data[i] = L->data[i + 1];
	}

	L->length--;
}


// 删除值为value的数据
bool DeleteByValue(SqList *L, ElemType value) {
	int index;
	bool flag = SearchByValue(*L, value, &index);  // 通过值找到对应索引值
	if (flag == false) {
		return false;
	}

	// 删除操作
	for (int i = index; i < L->length - 1; i++) {
		L->data[i] = L->data[i + 1];
	}
	
	L->length--;
	return true;
}


// 输出顺序表
void PrintSqList(SqList L) {
	printf("********SqList***********\n");
	for (int i = 0; i < L.length; i++) {
		printf("**data[%d] = %d\n", i, L.data[i]);
	}
}


int main() {
	// 测试
	SqList L;
	InitSqList(&L);
	for (int i = 0; i < 10; i++) {
		InsertByIndex(&L, i, i);
	}
	PrintSqList(L);

	printf("\r\r\n在索引为5的位置插入一个数据\n");
	InsertByIndex(&L, 5, 9999);
	PrintSqList(L);

	printf("\r\r\n删除索引值为5的数据\n");
	ElemType x;
	DeleteByIndex(&L, 5, &x);
	printf("您删除了data[5] = %d\n", x);
	PrintSqList(L);

	printf("\r\r\n删除值为5的数据\n");
	bool _ = DeleteByValue(&L, 5);
	PrintSqList(L);
	return 0;
}
