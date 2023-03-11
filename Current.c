

/**
Het is goed dat je bent gekomen!


           Hello!


This is my main file with main part of 
things I've already writen for this moment.

Here you can find such #data structures# as:
1) Queue
2) Stack
3) Linked List (cyclic doubly linked)
4) Vector (dinamic array)
5) Priority Queue
6) Heap (Binary)
7) Hash Table (in process)
8) Tree

Such #algorithms# as:
1) Swaps
2) Sorts
3) Searching algorithms (Binary Search and K-Statistics) 



In the end of this file there are some
solved problems, which I decided to save
just for myself.


Use!
*/




#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <Windows.h>

#define max(a,b) (((a) > (b)) ? (a):(b))
#define min(a,b) (((a) < (b)) ? (a):(b))
#define BufSize 50

typedef int (*cmpf) (void*, void*);




//Some rubish
//
typedef struct pairss {
	
	int key;
	char* value;

} pairs;
typedef struct starts_ends {

	int start;
	int end;

}st;
typedef struct pars {

	int id;
	int points;

}par;
//



// Swaps
//
void swap(int* a, int* b) {

	int temp = *a;
	*a = *b;
	*b = temp;

}

void UnSwap(void* a, void* b,size_t size_elem) {

	void* temp=(void*)malloc(sizeof(size_elem));
	memcpy(temp, a, size_elem);
	memcpy(a, b, size_elem);
	memcpy(b, temp, size_elem);
	free(temp);

}
//



// Vector (dinamic array)
//

//Vector on defines
#define CONCAT2X(a, b) a##_##b
#define CONCAT2(a, b) CONCAT2X(a, b)
#define NAME(name) CONCAT2(vector, name)
#define createVectorType(VECTOR_TYPE) \
typedef struct NAME{ \
VECTOR_TYPE *arr; size_t size; size_t cap; \
} NAME; \
void CONCAT2(NAME, init(NAME* vec)) { \
vec->cap = 1; \
vec->arr = calloc(vec->cap, sizeof(VECTOR_TYPE)); \
vec->size = 0; \
} \
int CONCAT2(NAME, push(NAME* vec, VECTOR_TYPE value)) { \
if (vec->cap == vec->size) { \
if (vec->cap == 0) { \
CONCAT2(NAME, init(vec)); \
} \
vec->cap *= 2; \
vec->arr = realloc(vec->arr, vec->size * sizeof(VECTOR_TYPE)); \
} \
vec->arr[vec->size++] = value; \
return vec->size - 1; \
}
//


#define VectorType int

typedef struct Vectors {
	
	size_t size;
	size_t capacity;
	VectorType* data;

} Vector;

Vector* VectorInit() {
	
	Vector* vector = malloc(sizeof(Vector));
	vector->capacity = 2;
	vector->size = 0;
	vector->data = malloc(vector->capacity*sizeof(VectorType));

	return vector;
}

void VectorResize(Vector* self,size_t new_size) {

	self->data = realloc(self->data,new_size*sizeof(VectorType));
	self->capacity = new_size;
	self->size = min(self->size, new_size);

}

void VectorAdd(Vector* self,VectorType elem) {

	if (self->capacity == self->size) VectorResize(self, self->capacity << 1);
	self->data[self->size++] = elem;

}

VectorType VectorPop(Vector* self) {

	if ((self->size << 2) + 1 <= self->capacity) VectorResize(self,(self->capacity>>1)+1);

	return self->data[--self->size];
}

void VectorClear(Vector* self){

	self->size = 0;

}

void VectorFree(Vector* self) {

	free(self->data);
	free(self);

}
//



// Linked List
//
#define ListValueType int

typedef struct ListPairs {

	unsigned int key;
	ListValueType value;

} ListPair;

typedef struct Nodes {

	ListPair elem;
	struct Nodes* next;
	struct Nodes* prev;

} Node;

ListPair PairInit(unsigned int key, ListValueType value) {

	ListPair elem;
	elem.key = key;
	elem.value = value;

	return elem;
}

Node* NodeInit(ListPair elem) {

	Node* new_node = malloc(sizeof(Node));
	new_node->elem = elem;
	new_node->next = new_node;
	new_node->prev = new_node;

	return new_node;
}

Node* NodeHeadCreate() {

	Node* new = malloc(1 * sizeof(Node));
	new->next = new;
	new->prev = new;

	return new;
}

void NodeAddAfter(ListPair new, Node* dot) {

	Node* new_dot = malloc(1 * sizeof(Node));
	new_dot->elem = new;
	new_dot->next = dot->next;
	dot->next->prev = new_dot;
	dot->next = new_dot;
	new_dot->prev = dot;

}

void NodeAddBefore(ListPair new, Node* dot) {

	Node* new_dot = malloc(1 * sizeof(Node));
	new_dot->elem = new;
	dot->prev->next = new_dot;
	new_dot->prev = dot->prev;
	dot->prev = new_dot;
	new_dot->next = dot;

}

ListPair NodePop(Node* new) {

	new->prev->next = new->next;
	new->next->prev = new->prev;
	ListPair temp = new->elem;
	free(new);

	return temp;
}
//



// Binary_Heap
//
typedef struct Heaps {

	Vector* vector;
	cmpf comp;

}Heap;

typedef struct HeapPairs {

	int value;
	size_t heapIndex;

}HeapPair;

Heap* HeapInit(cmpf comp) {

	Heap* new_heap = malloc(sizeof(Heap));
	new_heap->comp = comp;
	new_heap->vector = VectorInit();

	return new_heap;
}

void HeapSiftUp(Heap* self, int index) {

	int parent_index = (int)((index - 1) / 2);
	while (index > 0) {

		if (self->comp(&self->vector->data[index],
			&self->vector->data[parent_index]) < 0) {
			UnSwap(&self->vector->data[index],
				&self->vector->data[parent_index],
				sizeof(VectorType));
			index = parent_index;
			parent_index = (int)((parent_index - 1) / 2);
		}
		else break;
	}

}

void HeapSiftDown(Heap* self, int index) {

	int child_index = index * 2 + 1;
	while (self->vector->size > child_index) {

		if (self->vector->size > child_index + 1) {
			if (self->comp(&self->vector->data[index * 2 + 1],
				&self->vector->data[index * 2 + 2]) > 0) child_index++;
		}

		if (self->comp(&self->vector->data[index],
			&self->vector->data[child_index]) > 0) {
			UnSwap(&self->vector->data[index],
				&self->vector->data[child_index],
				sizeof(VectorType));
			index = child_index;
			child_index = index * 2 + 1;
		}
		else break;
	}

}

void HeapAdd(Heap* self, VectorType elem) {

	VectorAdd(self->vector, elem);
	HeapSiftUp(self, self->vector->size - 1);

}

VectorType HeapExtractMin(Heap* self) {

	if (self->vector->size == 0) return NULL;
	UnSwap(&self->vector->data[0], &self->vector->data[self->vector->size - 1], sizeof(VectorType));
	VectorType temp = VectorPop(self->vector);
	HeapSiftDown(self, 0);

	return temp;
}

void HeapBuild(Heap* self) {

	for (int i = self->vector->size / 2; i >= 0; i++) {
		HeapSiftDown(self, i);
	}

}

void HeapMerge(Heap* dist, Heap* sourse) {

	for (int i = 0; i < sourse->vector->size; i++) {
		HeapAdd(dist, sourse->vector->data[i]);
	}
	HeapBuild(dist);
	free(sourse);

}

void FreeHeap(Heap* self) {

	VectorFree(self->vector);
	free(self);

}

void HeapSwap(HeapPair** a, HeapPair** b) {

	ListPair* temp1 = *a;
	*a = *b;
	*b = temp1;

	int temp2 = (*a)->heapIndex;
	(*a)->heapIndex = (*b)->heapIndex;
	(*b)->heapIndex = temp2;

}
//



//Hash table
//
#define HashTableNodeType char*

typedef struct HashPairs {

	HashTableNodeType value;
	int key;

}HashPair;

typedef struct HashTableNodes {

	HashPair elem;
	struct HashTableNodes* next;
	struct HashTableNodes* prev;

}HashTableNode;

typedef struct HashTables {

	int size;
	HashTableNode** arr;

}HashTable;

unsigned int hash(int x) {

	unsigned long long new = x;
	new *= 1000000007;
	new = new >> 20;   //might be 30

	return (unsigned int)new;
}

HashTable* HashTableInit(int size) {

	HashTable* self = malloc(sizeof(HashTable));
	self->size = size;
	self->arr = calloc(size, sizeof(HashTableNode*));
	
	return self;
}

void append_pair(HashTable* HT, HashPair pair) {

	unsigned int num = hash(pair.key);
	unsigned int idex = num % HT->size;

	if (HT->arr[idex] != 0) {
		for (Node* temp = HT->arr[idex]->next; temp != HT->arr[idex]; temp = temp->next) {
			if (pair.key == temp->elem.key) {
				temp->elem.key = pair.key;
				return;
			}
		}
		//NodeAddAfter(pair, HT->arr[idex]);
	}
	else {
		HT->arr[idex] = NodeHeadCreate();
		//NodeAddAfter(pair, HT->arr[idex]);
	}

	return;
}
/*
typedef struct Pairs {
	int key;
	char* value;
} Pair;

typedef struct Nodes {
	Pair elem;
	struct Nodes* next;
	struct Nodes* prev;
} Node;

typedef struct hash_tabels {
	int size;
	Node** arr;
}hash_table;

hash_table* init_HT(int size) {

	hash_table* HT = malloc(sizeof(hash_table));
	HT->size = size;
	HT->arr = calloc(size, sizeof(Node*));

	return HT;
}

void append_pair(hash_table* HT, Pair pair) {

	unsigned int num = hash(pair.key);
	unsigned int idex = num % HT->size;

	if (HT->arr[idex] != 0) {
		for (Node* temp = HT->arr[idex]->next; temp != HT->arr[idex]; temp = temp->next) {
			if (pair.key == temp->elem.key) {
				temp->elem.key = pair.key;
				return;
			}
		}
		NodeAddAfter(pair, HT->arr[idex]);
	}
	else {
		HT->arr[idex] = NodeHeadCreate();
		NodeAddAfter(pair, HT->arr[idex]);
	}

	return;
}

char** get_value(hash_table* HT, int key) {

	unsigned int new = hash(key);
	unsigned int index = new % HT->size;

	Node* temp = HT->arr[index];
	if (temp != 0) {
		for (Node* t = HT->arr[index]->next; t != HT->arr[index]; t = t->next) {
			if (key == t->elem.key) {
				return &t->elem.value;
			}
		}
	}

	return NULL;
}

char contains_key(hash_table* HT, int key) {

	unsigned int new = hash(key);
	unsigned int index = new % HT->size;

	Node* temp = HT->arr[index];
	if (temp != 0) {
		for (Node* t = HT->arr[index]->next; t != HT->arr[index]; t = t->next) {
			if (key == t->elem.key) {
				return 1;
			}
		}
	}

	return 0;
}

void del_elem(int key, hash_table* HT) {

	unsigned int new = hash(key);
	unsigned int index = new % HT->size;

	Node* temp = HT->arr[index];
	if (temp != 0) {
		for (Node* t = HT->arr[index]->next; t != HT->arr[index]; t = t->next) {
			if (key == t->elem.key) {
				NodePop(t);
				return;
			}
		}
	}

	return;
}

void del_HT(hash_table* HT) {
	for (int i = 0; i < HT->size; i++) {
		if (HT->arr[i] != 0) {
			for (Node* t = HT->arr[i]->next; t != HT->arr[i]; t = HT->arr[i]->next) {
				NodePop(t);
			}
			NodePop(HT->arr[i]);
		}
	}
	free(HT->arr);
	free(HT);
}



*/
//



// Tree
//
#define TreeValueType int

typedef struct TreeNodes{

	int key;
	TreeValueType value;
	struct TreeNodes* left;
	struct TreeNodes* right;
	int hight;
	
}TreeNode;

typedef struct _Trees {

	TreeNode* root;

}Tree;

int getHight(TreeNode* self) {

	if (self == NULL) return -1;

	return self->hight;
}

void updateBalance(TreeNode* self) {

	if (self == NULL) return;
	self->hight = 1 + max(getHight(self->left), getHight(self->right));

}

TreeNode* smallLeftRotate(TreeNode* root) {

	TreeNode* temp = root->right;
	root->right = temp->left;
	temp->left = root;

	updateBalance(root);
	updateBalance(temp);

	return temp;
}

TreeNode* smallRightRotate(TreeNode* root) {

	TreeNode* temp = root->left;
	root->left = temp->right;
	temp->right = root;

	updateBalance(root);
	updateBalance(temp);

	return temp;
}

TreeNode* bigLeftRotate(TreeNode* root) {

	root->right = smallRightRotate(root->right);
	return smallLeftRotate(root);

}

TreeNode* bigRightRotate(TreeNode* root) {

	root->left = smallLeftRotate(root->left);
	return smallRightRotate(root);

}

TreeNode* balanceTree(TreeNode* root) {

	TreeNode* temp = root;

	if (root->hight == 0) return root;

	int rightHight, leftHight, balance;
	rightHight = getHight(root->right);
	leftHight = getHight(root->left);
	balance = rightHight - leftHight;

	if (balance == 2) { // right under-tree is heavier

		if (rightHight - getHight(root->right->right) == 1) { // right-right under-tree is heaviev
			
			temp = smallLeftRotate(root);

		}
		else {

			temp = bigLeftRotate(root);

		}

	}
	if (balance == -2) { 

		if (leftHight - getHight(root->left->left) == 1) { // left-left under-tree is heavier

			temp = smallRightRotate(root);

		}
		else {

			temp = bigRightRotate(root);

		}

	}

	return temp;
}

Tree* TreeInit() {

	Tree* self = malloc(sizeof(Tree));
	self->root = 0;

	return self;
}

TreeNode* TreeNodeInit(int key, TreeValueType value) {

	TreeNode* TNode = malloc(sizeof(TreeNode));
	TNode->hight = 0;
	TNode->value = value;
	TNode->key = key;
	TNode->left = NULL;
	TNode->right = NULL;

	return TNode;
}

TreeNode* _TreeAddNode(TreeNode* root,TreeValueType value, int key) {

	if (root == 0) {
		TreeNode* NewNode = TreeNodeInit(key, value);
		//updateBalance(NewNode);
		return NewNode;
	}
	if (key < root->key) {
		root->left = _TreeAddNode(root->left,value,key);
	}
	if (key > root->key) {
		root->right = _TreeAddNode(root->right,value,key);
	}
	updateBalance(root);
	root = balanceTree(root);

	return root;
}

void TreeAdd(Tree* self, TreeValueType value, int key) {

	self->root = _TreeAddNode(self->root, value, key);

}

TreeNode* TreeFindNode(TreeNode* root,int key) {

	if (root == NULL) return 0;
	if (key == root->key) return root;
	TreeNode* found;

	if (key < root->key) found = TreeFindNode(root->left, key);
	else found = TreeFindNode(root->right, key);

	return found;
}

TreeNode* _TreeNodeRemove(TreeNode* root,int key) {

	if (root == 0) return 0;

	if (root->key == key) {

		TreeNode* temp = root;

		if (root->left == NULL && root->right == NULL) {
			free(root);
			temp = 0;
		}
		else if (root->right == NULL) {
			temp = root->left;
			free(root);
			
		}
		else if (root->left == NULL) {
			temp = root->right;
			free(root);
			
		}
		else {

			TreeNode* end = root->left;
			while (end->right != NULL) {
				end = end->right;
			}

			TreeValueType val = temp->value;
			int k = temp->key;
			temp->value = end->value;
			temp->key = end->key;
			end->key = k;
			end->value = val;

			root->left = _TreeNodeRemove(root->left, key);
			
		}
		updateBalance(temp);
		
		return temp;

	}

	if (key < root->key) {
		root->left = _TreeNodeRemove(root->left,key);
	}
	if (key > root->key) {
		root->right = _TreeNodeRemove(root->right, key);
	}
	updateBalance(root);
	root = balanceTree(root);

	return root;
}

void TreeNodeRemove(Tree* self,int key) {

	self->root = _TreeNodeRemove(self->root, key);

}

int TreeCount(TreeNode *self) {

	if (self == NULL) return 0;

	return TreeCount(self->left) + TreeCount(self->right) + 1;
}

TreeNode* TreeGetNext(Tree* self,int key) {

	TreeNode* cur = self->root;
	TreeNode* reminder = NULL;

	while (cur != NULL) {
		if (cur->key > key) {
			reminder = cur;
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}

	return reminder;
}

TreeNode* TreeGetPrev(Tree* self, int key) {

	TreeNode* cur = self->root;
	TreeNode* reminder = NULL;

	while (cur != NULL) {
		if (cur->key >= key) {
			cur = cur->left;
		}
		else {
			reminder = cur;
			cur = cur->right;
		}
	}

	return reminder;
}

typedef struct TreeArrayPairs {

	TreeValueType value;
	int key;

}TreeArrayPair;

void _TreeConvToArray(TreeNode* root, TreeArrayPair* arr, int* i) {

	if (root == 0) return;

	_TreeConvToArray(root->left, arr, i);

	arr[*i].key = root->key;
	arr[*i].value = root->value;
	(* i)++;

	_TreeConvToArray(root->right, arr, i);

}

TreeArrayPair* TreeToArray(Tree* self) {

	int i = 0;
	int size = TreeCount(self);
	TreeArrayPair* arr = malloc(size * sizeof(TreeArrayPair));
	_TreeConvToArray(self->root, arr, &i);

	return arr;
}

void _TreePostTraverasl(TreeNode* root, TreeArrayPair* arr, int* i) {

	if (root == 0) return;

	_TreePostTraverasl(root->left, arr, i);
	_TreePostTraverasl(root->right, arr, i);
	arr[*i].key = root->key;
	arr[*i].value = root->value;
	(*i)++;
}

TreeArrayPair* TreePostTraveraslToArray(Tree* self) {

	int i = 0;
	int size = TreeCount(self->root);
	TreeArrayPair* arr = malloc(size * sizeof(TreeArrayPair));
	_TreePostTraverasl(self->root, arr, &i);

	return arr;
}

void TreeDelete(TreeNode* self) {

	if (self == NULL) return;

	TreeDelete(self->left);
	TreeDelete(self->right);
	free(self);

}
//

// Segment tree
//
#define segmentTreeValue int

typedef struct SegTreeNodes {

	segmentTreeValue value;

}SegTreeNode;

SegTreeNode* SegTreeInit(int number) {
	
	SegTreeNode* temp = calloc(4*number,sizeof(SegTreeNode));

	return temp;
}

void _configTree(SegTreeNode* tree, int* array,int number,int leftBoard, int rightBoard) {

	if (leftBoard == rightBoard) {

		tree[number].value = array[leftBoard];

	}
	else {

		int middle = (leftBoard + rightBoard) / 2;
		_configTree(tree, array, number * 2, leftBoard, middle);
		_configTree(tree, array, number * 2+1, middle+1, rightBoard);
		tree[number].value = tree[number * 2].value + tree[number * 2 + 1].value;

	}
}

void buildSegTree(SegTreeNode* tree, int* array,int number) {

	_configTree(tree,array, 1, 0, number - 1);

}

int _SegTreeGetSum(SegTreeNode* tree, int value, int curLeft, int curRight, int lf, int rt) {

	if (lf <= curLeft && rt >= curRight) return tree[value].value;

	if (curRight < lf || curLeft > rt) return 0;

	int middle = (curLeft + curRight) / 2;
	return _SegTreeGetSum(tree, value * 2, curLeft, middle, lf,rt) 
		+ _SegTreeGetSum(tree, value * 2 + 1, middle+1, curRight, lf, rt);
}

int SegTreeGetSum(SegTreeNode* tree,int number, int lf, int rt) {

	return _SegTreeGetSum(tree, 1, 0, number - 1, lf, rt);

}

void _SegTreeUpdate(SegTreeNode* tree,int* arr, int oldind, int lf, int rt, int index, segmentTreeValue updateValue) {

	/*if (lf == rt) tree[value].value = updateValue;
	else {
		int middle = (lf + rt) / 2;
		if (index <= middle) _SegTreeUpdate(tree, value * 2, lf, middle, 
			index, updateValue);
		else _SegTreeUpdate(tree, value * 2, middle + 1, rt, index, updateValue);

		tree[value].value = tree[value * 2].value + tree[value * 2 + 1].value;
	}*/

	if (index <= lf && rt <= index) {
		arr[index] = updateValue;
		tree[oldind].value = updateValue;
		return;
	}
	if (rt < index || index < lf) return;

	int middle = (rt + lf);
	middle /= 2;
	_SegTreeUpdate(tree,arr, oldind *2,lf,middle,index,updateValue);
	_SegTreeUpdate(tree,arr, oldind *2+1,middle+1,rt,index,updateValue);
	tree[oldind].value = tree[oldind * 2].value + tree[oldind * 2 + 1].value;
}

void SegTreeUpdate(SegTreeNode* tree,int* arr,int number, int index, segmentTreeValue updateValue) {

	_SegTreeUpdate(tree,arr,1,0,number-1,index,updateValue);

}

//


// Searching algorythms
//
void* BinSearch(void* elem, void* arr, size_t size_arr, size_t size_elem, cmpf comp) {

	size_t i = 0, j = size_arr - 1;
	size_t middle;
	void* answer = 0;
	while (i <= j) {
		middle = (i + j) / 2;
		if (comp(elem, (char*)arr + middle * size_elem) < 0) {
			j = middle - 1;
		}
		else if (comp(elem, (char*)arr + middle * size_elem) > 0) {
			i = middle + 1;
		}
		else {
			answer = (char*)arr + middle * size_elem;
			break;
		}
		// To get the index of the element (pointed to by the result of the function),
		// you can use the "formula" (mid-arr)/size_elem.
		// For custom data types is enough mid-arr,
		// (otherwise, the number of bytes in the interval is returned mid-arr, 
		// because of what you need to divide by type)      (by char(...))
	}

	return comp(answer, elem) == 0 ? answer : NULL;
}

void* BinSearchUp(void* elem, void* arr, size_t size_arr, size_t size_elem, cmpf comp) {

	size_t i = 0, j = size_arr - 1;
	size_t middle;
	void* answer = 0;
	while (i < j) {
		middle = (i + j) / 2;
		if (comp(elem, (char*)arr + middle * size_elem) >= 0) {
			i = middle + 1;
		}
		else {
			j = middle;
		}

	}
	if (comp((char*)arr + (i - 1) * size_elem, (char*)arr + i * size_elem) < 0) {
		i -= 1;
	}
	if (i < 0) return NULL;
	answer = (char*)arr + i * size_elem;

	return comp(answer, elem) == 0 ? answer : NULL;
}

void* BinSearchDown(void* elem, void* arr, size_t size_arr, size_t size_elem, cmpf comp) {

	size_t i = 0, j = size_arr - 1;
	size_t middle;
	void* answer = 0;
	while (i < j) {
		middle = (i + j) / 2;
		if (comp(elem, (char*)arr + middle * size_elem) <= 0) {
			j = middle;
		}
		else {
			i = middle + 1;
		}
	}
	
	answer = (char*)arr + i * size_elem;

	return comp(answer, elem) == 0 ? answer : NULL;
}

void* LowerBound(void* elem, void* arr, size_t size_arr, size_t size_elem, cmpf comp) {

	size_t i = 0, j = size_arr - 1;
	size_t middle;
	void* answer = 0;
	while (i < j) {
		middle = (i + j) / 2;
		if (comp(elem, (char*)arr + middle * size_elem) <= 0) {
			j = middle;
		}
		else {
			i = middle + 1;
		}
	}
	answer = (char*)arr + i * size_elem;

	return answer;
}

int Partition(int* arr, int left, int right) {

	int pivo = arr[(left + right) / 2];
	int i = left, j = right;
	while (i <= j) {
		while (arr[i] < pivo) i++;
		while (arr[j] > pivo) j--;
		if (i >= j) {
			break;
		}
		swap(&arr[i++], &arr[j--]);
	}

	return j;
}

int KStatistics(int* arr, int number, int point) {

	int left_arr = 0, right_arr = number - 1;
	while (1) {
		int mid = Partition(arr, left_arr, right_arr);
		if (left_arr == right_arr) {
			return arr[mid];
		}
		else if (point <= mid) {
			right_arr = mid;
		}
		else {
			left_arr = mid + 1;
		}
	}

}
//



// Sorts
//
void InsertionSort(int* arr, int num) {

	int temp;
	for (int i = 1; i < num; i++) {
		temp = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > temp) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}

}

void CelectionSort(int* arr, int number) {

	for (int i = 0; i < number - 1; i++) {
		int lowest = i;
		for (int j = i + 1; j < number; j++) {
			if (arr[j] < arr[lowest]) {
				lowest = j;
			}
		}
		swap(&arr[i], &arr[lowest]);

	}

}

int UnPartition(void* arr, size_t size_arr, size_t size_elem, void* pivot, cmpf cmp) {

	int current;
	int i = 0;
	int j = size_arr - 1;
	void* new_arr = malloc(size_arr * size_elem);
	char coin = 0;
	for (int k = 0; k < size_arr; k++) {
		current = cmp((char*)arr + k * size_elem, pivot);
		if (current == 1) {
			memcpy((void*)((char*)new_arr + j * size_elem), (void*)((char*)arr + k * size_elem), size_elem);
			j--;
		}
		else if (current == -1) {
			memcpy((void*)((char*)new_arr + i * size_elem), (void*)((char*)arr + k * size_elem), size_elem);
			i++;
		}
		else {
			if (coin) {
				memcpy((void*)((char*)new_arr + i * size_elem), (void*)((char*)arr + k * size_elem), size_elem);
				i++;
				coin = 0;
			}
			else {
				memcpy((void*)((char*)new_arr + j * size_elem), (void*)((char*)arr + k * size_elem), size_elem);
				j--;
				coin = 1;
			}
		}

	}
	memmove(arr, new_arr, size_arr * size_elem);
	free(new_arr);

	return j + 1;
}

void UnQuickSort(void* arr, size_t size_arr, size_t size_elem, cmpf cmp) {

	if (size_arr <= 1) {
		return;
	}
	void* pivot = malloc(size_elem);
	int ran = (int)rand() % size_arr;
	memcpy(pivot, (void*)((char*)arr + ran * size_elem), size_elem);
	int bound = UnPartition(arr, size_arr, size_elem, pivot, cmp);
	free(pivot);
	UnQuickSort(arr, bound, size_elem, cmp);
	UnQuickSort((void*)((char*)arr + bound * size_elem), size_arr - bound, size_elem, cmp);

}

int CustomPartition(int* arr, int len, int pivot) {

	int i = 0;
	int j = len - 1;
	int* new_arr = malloc(len * sizeof(int));
	char coin = 0;
	for (int k = 0; k < len; k++) {

		if (arr[k] > pivot) {
			new_arr[j] = arr[k];
			j--;
		}
		else if (arr[k] < pivot) {
			new_arr[i] = arr[k];
			i++;
		}
		else {
			if (coin) {
				new_arr[i] = arr[k];
				i++;
				coin = 0;
			}
			else {
				new_arr[j] = arr[k];
				j--;
				coin = 1;
			}
		}

	}
	for (int i = 0; i < len; i++) {
		arr[i] = new_arr[i];
	}
	free(new_arr);

	return j + 1;
}

void QuickSort(int* arr, int len) {

	if (len <= 1) {
		return;
	}
	int ran = (int)rand() % len;
	int bound = CustomPartition(arr, len, arr[ran]);
	QuickSort(arr, bound);
	QuickSort(arr + bound, len - bound);

	return;
}

void BubbleSort(int* arr, int arr_len) {

	for (int i = 1; i < arr_len; i++) {
		for (int j = 0; j < arr_len - i; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp;
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}

	}

}

void ArrayMerge(int* arr1, int* arr2, int len1, int len2, int* res) {

	int i = 0, j = 0;
	while (i < len1 && j < len2) {

		if (arr1[i] <= arr2[j]) {
			res[i + j] = arr1[i];
			i++;
		}
		else {
			res[j + i] = arr2[j];
			j++;
		}
	}
	if (j == len2) {
		memmove(res + j + i, arr1 + i, (len1 - i) * sizeof(int));
	}
	else {
		memmove(res + j + i, arr2 + j, (len2 - j) * sizeof(int));
	}

	return;
}

void MergeSort(int* arr, int len) {

	if (len <= 1) {
		return;
	}
	int* arr1 = arr;
	int* arr2 = len / 2 + arr;
	int n1 = len / 2;
	int n2 = len - n1;
	MergeSort(arr1, n1);
	MergeSort(arr2, n2);
	int* res = malloc(len * sizeof(int));
	ArrayMerge(arr1, arr2, n1, n2, res);
	memmove(arr, res, len * sizeof(int));
	free(res);

}

void RadixSort(char** arr, size_t arr_size, size_t length) {

	int start = 'a';
	int end = 'z';

	char** res = malloc(arr_size * sizeof(char*));
	int* count = calloc((end - start + 1), sizeof(int));

	for (int j = length - 1; j >= 0; j--) {
		memset(count, 0, (end - start + 1) * sizeof(int));
		for (size_t i = 0; i < arr_size; i++) {
			count[arr[i][j] - start]++;
		}

		for (size_t i = 1; i < end - start + 1; i++) {
			count[i] += count[i - 1];
		}

		for (int i = arr_size - 1; i >= 0; i--) {
			res[--count[arr[i][j] - start]] = arr[i];
		}

		for (size_t i = 0; i < arr_size; i++) {
			arr[i] = res[i];
		}

	}
	free(res);
	free(count);

}

void FlipFlopRadixSort(char** arr, size_t arr_size, size_t length) {

	int start = 'a';
	int end = 'z';

	char** res = malloc(arr_size * sizeof(char*));
	int* count = calloc((end - start + 1), sizeof(int));

	int coin = 0;

	char** flipflop[2] = { arr,res };
	char** from;
	char** to;
	for (int j = length - 1; j >= 0; j--) {
		from = flipflop[coin];
		to = flipflop[coin ^ 1];
		memset(count, 0, (end - start + 1) * sizeof(int));
		for (size_t i = 0; i < arr_size; i++) {
			count[from[i][j] - start]++;
		}

		for (size_t i = 1; i < end - start + 1; i++) {
			count[i] += count[i - 1];
		}

		for (int i = arr_size - 1; i >= 0; i--) {
			to[--count[from[i][j] - start]] = from[i];
		}
		coin ^= 1;
	}
	if (coin) memmove(arr, res, arr_size * sizeof(char*));
	free(res);
	free(count);

}

void Heap_Sort(Heap* self, int* res_arr) {

	int size = self->vector->size;
	for (size_t i = 0; i < size; i++) res_arr[i] = HeapExtractMin(self);

}
//



// Comparators
//
int comparePair(ListPair** x, ListPair** y) {

	if ((*x)->value < (*y)->value) {
		return -1;
	}
	else if ((*x)->value > (*y)->value) {
		return 1;
	}
	else {
		return 0;
	}

}

int comparePar(void* x, void* y) {

	if ((((par*)x)->points) < (((par*)y)->points)) {
		return 1;
	}
	if ((((par*)x)->points) > (((par*)y)->points)) {
		return -1;
	}
	else {
		if ((((par*)x)->id) < (((par*)y)->id)) {
			return -1;
		}
		if ((((par*)x)->id) > (((par*)y)->id)) {
			return 1;
		}
		return 0;
	}

}

int compareSt(void* x, void* y) {

	if ((((st*)x)->start) < (((st*)y)->start)) {
		return -1;
	}
	if ((((st*)x)->start) > (((st*)y)->start)) {
		return 1;
	}
	else {
		if ((((st*)x)->end) < (((st*)y)->end)) {
			return -1;
		}
		if ((((st*)x)->end) > (((st*)y)->end)) {
			return 1;
		}
		return 0;
	}

}

int compareInt(void* x, void* y) {

	if (*((int*)x) < (*(int*)y)) {
		return -1;
	}
	else if (*((int*)x) > (*(int*)y)) {
		return 1;
	}
	else {
		return 0;
	}

}

int compareChr(size_t* context,char** x,char** y) {

	if ((* x)[*context] < ((*y)[*context])) {
		return -1;
	}
	else if ((*x)[*context] > ((*y)[*context])) {
		return 1;
	}
	else {
		return 0;
	}

}
//



// Practical
//
void PairsCountingSort(pairs* arr, int len, int range) {

	int* new_len = calloc(range + 2, sizeof(int));
	for (int i = 0; i < len; i++) {
		new_len[arr[i].key + 1]++;
	}
	for (int i = 1; i <= range; i++) {
		new_len[i] += new_len[i - 1];
	}
	pairs* new_arr = malloc(len * sizeof(pairs));
	for (int i = 0; i < len; i++) {
		new_arr[new_len[arr[i].key]] = arr[i];
		new_len[arr[i].key]++;
	}

	memmove(arr, new_arr, len * sizeof(pairs));
	free(new_arr);
	free(new_len);

}



int check_for_avaliable(int* arr,int arr_size, long long pivot,int count_jord) {

	long long summary = 0;
	int sount = 0;
	
	for (size_t i = 0; i < arr_size; i++){
		if (sount >= count_jord) return 0;
		if (arr[i] > pivot) return 0;
		summary += arr[i];
		if (summary > pivot) {
			summary = arr[i];
			sount++;
		}
	}
	sount++;
	
	if (sount <= count_jord) {
		return 1;
	}

	return 0;
}

long long maximal_among_minimal(int* arr,int arr_size,int count_jord) {

	long long start = INT_MIN;
	long long end = 0;
	long long answer;
	for (size_t i = 0; i < arr_size; i++) {
		if (arr[i] > start) start = arr[i];
		end += arr[i];
	}
	while (start <= end) {
		long long pivot = (start + end) / 2;

		if (check_for_avaliable(arr, arr_size, pivot, count_jord)) {
			answer = pivot;
			end = pivot - 1;
		}
		else start = pivot + 1;
	}

	return answer;
}

void Eratosphen(int pivot, Node* Ans) {

	int* arr = malloc(pivot * sizeof(int));
	for (size_t i = 0; i < pivot; i++) {
		arr[i] = i;
	}
	arr[1] = 0;
	for (size_t i = 2; i < pivot; i++) {
		if (arr[i] != 0) {
			for (size_t j = i * 2; j < pivot; j += i) arr[j] = 0;
		}
	}
	for (size_t i = 0; i < pivot; i++) if (arr[i] != 0) NodeAddAfter(PairInit(1, arr[i]), Ans);

}

int getSummOfDigits(int number) {
	if (!number) return 0;

	return getSummOfDigits(number/10)+number%10;
}

void _extraSpace(char* source, char* dest, char* dotPlace, int condition) {
	
	if (*source == 0) {
		if (dotPlace != 0) {
			*(dotPlace + 1) = 0;
		}
		return;
	}
	
	if (*source != ' ' || condition != 1) {
		condition = 0;
		if (*source == '(' || *source == ' ') condition = 1;
		if (*source == '.') dotPlace = dest;

		*dest = *source;
		dest++;
		
	}
	
	_extraSpace(source+1, dest,dotPlace,condition);
}

void removeExtraSpace(char* source, char* dest) {
	_extraSpace(source,dest,0,1);
}
//

typedef struct treePairs {
	int key;
	int left;
	int right;
}treePair;

int findHight(treePair* arr,int index) {
	
	if (index == 0) return 0;

	return 1+max(findHight(arr,arr[index].left), findHight(arr,arr[index].right));
}

int checker(treePair* arr,int index,int minim,int maxim) {
	if (index == 0) return 1;
	if (arr[index].key <= minim || arr[index].key >= maxim) return 0;
	
	return checker(arr, arr[index].left, minim, arr[index].key) && checker(arr, arr[index].right, arr[index].key, maxim);
}

void fillip(treePair* arr,int index,int* res, int* i) {

	if (index == 0) return;

	fillip(arr,arr[index].left, res, i);

	//res[*i] = arr[index].key;
	res[arr[index].key] = ++(* i);

	fillip(arr, arr[index].right, res, i);

}

int main() {
	
	freopen("input.txt", "r", stdin);	
/*
	int number,val;
	scanf("%d", &number);

	TreeNode* vertices = calloc(number + 1, sizeof(TreeNode));

	int* stack = calloc(number + 1, sizeof(int));
	stack[0] = 0;
	vertices[stack[stack[stack[stack[stack[stack[0]]]]]]].key = 3E6;
	int pointer=0;

	for (size_t i = 1; i <= number; i++){
			
		scanf("%d", &val);

		vertices[val].key = val;

		if (val < vertices[stack[pointer]].key) {

			vertices[stack[pointer]].left = vertices + val;
		}
		else {
			int popedIndexOfNode;
			for (1+4; val > vertices[stack[pointer]].key; popedIndexOfNode = stack[pointer--]);
			
			vertices[popedIndexOfNode].right = vertices + val;
		}
		stack[++pointer] = val;
	}
	
	int i = 0;
	int size = TreeCount(vertices[0].left)+1;
	TreeArrayPair* arr = malloc(size * sizeof(TreeArrayPair));
	_TreePostTraverasl(vertices[0].left, arr, &i);

	for (size_t i = 0; i < number; i++){
		printf("%d ", arr[i].key);
	}*/
	double summ = 0;
	double num = 1;
	for (int i = 1; i < 100; i++){
		summ += (double)(1 / num);
		num *= (i + 1);
	}

	printf("%.15lf", summ);
	return 0;
}



// SOME SOLVED PROBLEMS

//CustomedRadixSort (sorts only %phaze times)
/*
void CustomedFlipFlopRadixSort(char** arr, size_t arr_size, int length,int phaze) {

	int start = 'a';
	int end = 'z';

	char** res = malloc(arr_size * sizeof(char*));
	int* count = calloc((end - start + 1), sizeof(int));

	int coin = 0;

	char** flipflop[2] = { arr,res };
	char** from;
	char** to;
	for (int j = length - 1; j >= length-phaze; j--) {
		from = flipflop[coin];
		to = flipflop[coin ^ 1];
		memset(count, 0, (end - start + 1) * sizeof(int));
		for (size_t i = 0; i < arr_size; i++) {
			count[from[i][j] - start]++;
		}

		for (size_t i = 1; i < end - start + 1; i++) {
			count[i] += count[i - 1];
		}

		for (int i = arr_size - 1; i >= 0; i--) {
			to[--count[from[i][j] - start]] = from[i];
		}
		coin ^= 1;
	}
	if (coin) memmove(arr, res, arr_size * sizeof(char*));
	free(res);
	free(count);
}
*/

//Array Division (100/100)
/*
int number, walls;

	scanf("%d %d", &number, &walls);
	int* arr = malloc(sizeof(int) * number);
	for (int i = 0; i < number; i++) scanf("%d", arr + i);

	int* jords = malloc(walls * sizeof(int));
	long long pivo = maximal_among_minimal(arr, number, walls);
	long long summary = 0;
	int count = 0;

	for (size_t i = 0; i < number; i++) {
		if (count >= walls) return 0;
		if (arr[i] > pivo) return 0;
		summary += arr[i];
		if (summary > pivo) {
			summary = arr[i];
			jords[count] = i;
			count++;
		}
	}


	for (size_t i = count; i < walls; i++){
		jords[i] = number;
	}
	for (int i = walls-2; i >= 0; i--){
		if (jords[i] >= jords[i + 1]) {
			jords[i]=jords[i+1]-1;
		}
	}

	for (size_t i = 0; i < walls-1; i++){
		printf("%d ", jords[i]);
	}

*/
//Array Division (80/100)
/*
	//freopen("input.txt", "r", stdin);
	int number,temp,walls;
	scanf("%d %d",&number,&walls);
	int* arr = malloc(sizeof(int) * number);
	for (int i = 0; i < number; i++) {
		scanf("%d",arr + i);
	}
	int* pref = malloc(sizeof(int) * (number+1));
	pref[0] = 0;
	for (int i = 0; i < number; i++) {
		pref[i+1] = pref[i] + arr[i];
	}
	int* jorno = malloc((walls+1) * sizeof(int));
	jorno[0] = 0;
	int summary = pref[number];
	for (int j = 1; j <= walls; j++) {
		double hu = (double)j * summary / walls;
		int temp = ceil(hu);
		int index = (int*) LowerBound(&temp, pref, number + 1, sizeof(int), compareInt) - pref;

		if (index>1 && abs(hu - pref[index - 1]) <= abs(pref[index] - hu)) {
			index -= 1;
		}

		jorno[j] = index;
		if (jorno[j] <= jorno[j - 1]) {
			jorno[j] = jorno[j-1]+1;
		}
	}
	
	int error = jorno[walls] > number ? jorno[walls] - number : 0;

	for (int i = 1; i < walls; i++) {
		jorno[i] = max(jorno[i - 1] + 1, jorno[i] - error);
		printf("%d ", jorno[i]);
	}
	*/

//Nested arrays v1
/*int main() {

	int number1, number2, elem;
	scanf("%d", &number1);
	int* arr1 = malloc(number1 * sizeof(int));
	for (int i = 0; i < number1; i++) {
		scanf("%d", &elem);
		arr1[i] = elem;
	}	
	scanf("%d", &number2);
	int* arr2 = malloc(number2 * sizeof(int));

	for (int i = 0; i < number2; i++) {
		scanf("%d", &elem);
		arr2[i] = elem;
	}
	UnQuickSort(arr1, number1, sizeof(int), compareInt);
	UnQuickSort(arr2, number2, sizeof(int), compareInt);
	int i = 0, j = 0;
	int rem;
	while (i < number1 && j < number2) {
		int rem = arr1[i];
		while (i < number1 && arr1[i] == rem) i++;
		if (arr2[j] == rem) { 
			while (j < number2 && arr2[j] == rem) j++; 
		}
		else { printf("NO"); return 0; }
	}
	if (j != number2) {
		printf("NO");
		return 0;
	}
	if (i != number1) {
		printf("NO");
		return 0;
	}
	printf("YES");

}*/

//Nested arrays v2
/*int main() {

	int number1, number2, elem;
	scanf("%d", &number1);
	int* arr1 = malloc(number1 * sizeof(int));
	for (int i = 0; i < number1; i++) {
		scanf("%d", &elem);
		arr1[i] = elem;
	}	
	scanf("%d", &number2);
	int* arr2 = malloc(number2 * sizeof(int));

	for (int i = 0; i < number2; i++) {
		scanf("%d", &elem);
		arr2[i] = elem;
	}
	UnQuickSort(arr1, number1, sizeof(int), compareInt);
	UnQuickSort(arr2, number2, sizeof(int), compareInt);
	int i1 = 0, j1 = 0, counter1 = 0;
	int i2 = 0, j2 = 0, counter2 = 0;
	int log1 = 0, log2 = 0,log3;
	while (i1 < number1 && j1 < number2) {
		if (arr1[i1] == arr2[j1]) {
			counter1++;
			i1++;
		}
		else {
			j1++;
		}
		
	}
	while (i2 < number1 && j2 < number2) {
		if (arr2[j2] == arr1[i2]) {
			counter2++;
			j2++;
		}
		else {
			i2++;
		}

	}
	if (counter1 == number1) {
		log1 = 1;
	}
	if (counter2 == number2) {
		log2 = 1;
	}
	log3 = log1 && log2;
	if (log3) {
		printf("YES");
	}
	else {
		printf("NO");
	}
}*/

//Garland
/*
# Linear recurrences (via calculator):
# f(n) = 2 * f(n - 1) + 2 - f(n - 2)
# f(n) = n * (c2 - 1 + n) + c1
# f(1) = c2 + c1 = A <=> c1 = A - c2
# f(n) = n ^ 2 + n * (c2 - 1) + A - c2

# Looking for a minimum on the segment [1, number]:
# 1 <= n <= number
# n = 1 / 2 - c2 / 2
#      |
# 1 - 2 * number <= c2 <= -1

# The minimum of this function (the line above) is reached at n = -(c2 - 1) / 2.
# You can substitute and get this minimum value.
# However n - integer and belongs from 1 to number, so
# you need to know the values ​​around this point:
# f(n) = c2 * (n - 1) + (n - 1) * n + A - final formula
N = list(map(float, input().split()))
number = N[0]
A = N[1]
c2 = -1 - 2 * ((A) * *(0.5))
if (c2 > -1) :
	c2 = -1
if (c2 < 1 - 2 * number) :
	c2 = 1 - 2 * number
b = round(1 / 2 - c2 / 2)
c2 = -A / (b - 1) - b
ans = c2 * (number - 1) + (number - 1) * number + A
print(f"{ans:.2f}")
*/

//Fences
/*
int main() {

	int number, start, end;
	scanf("%d", &number);
	st* arr = malloc(number * sizeof(st));
	for (int i = 0; i < number; i++) {
		scanf("%d %d", &start, &end);
		arr[i].start = start;
		arr[i].end = end + 1;
	}

	UnQuickSort(arr, number, sizeof(st), compare_for_st);

	int summary = arr[0].end - arr[0].start;
	int i = 1;
	int max_end = arr[0].end;
	while (i < number) {
		if (max_end > arr[i].start) {

			if (max_end < arr[i].end) {
				summary += arr[i].end - max_end;
			}
		}
		else {
			summary += arr[i].end - arr[i].start;
		}
		max_end = max(max_end, arr[i].end);
		i++;
	}
	printf(" %d ", summary);
}
*/

//Polish notation and MaxStack
/*
typedef enum operands {

	not_operand, plus, minus, mult

}operand;

int do_math(int num1,int num2,operand oper) {

	switch (oper)
	{
	case plus:
		return num1 + num2;
	case minus:
		return num1 - num2;
	case mult:
		return num1 * num2;
	default:
		assert(1);
	}

}

operand is_operand(char* string) {

	switch (string[0])
	{
	case '-':
		return minus;
	case '+':
		return plus;
	case '*':
		return mult;
	default:
		return not_operand;
	}

}

void MaxStack(Node* stack,char* string) {

	int num,temp;
	operand op = is_operand(string);

	if (op == not_operand) {
		printf("%d\n", stack->prev->elem.value);
	}
	else if(op == plus) {
		scanf("%d", &num);
		temp = stack->prev->elem.value;
		num = max(num, temp);
		NodeAddBefore(PairInit(1, num), stack);
	}
	else if (op == minus) {
		NodePop(stack->prev);
	}

}

void PolishNotation(Node* stack,char* string) {

	operand op = is_operand(string);

	if (op == not_operand) {
		NodeAddBefore(PairInit(1, atoi(string)), stack);
	}
	else {
		ListPair element2 = NodePop(stack->prev);
		ListPair element1 = NodePop(stack->prev);
		NodeAddBefore(PairInit(1, do_math(element1.value, element2.value, op)), stack);
	}

}
*/

//Test
/*
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int x;
	scanf("%d", &x);
	Pair* arr = malloc(x * sizeof(Pair));
	for (int i = 0; i < x; i++) {
		int y;
		char* z = malloc(4*sizeof(char));
		z[3] = 0;
		scanf("%d %s", &y, z);
		arr[i].key = y;
		arr[i].value = z;
	}
	NNode* root = 0;
	for (int i = 0; i < x; i++) {
		root = append_root(arr[i].key, arr[i].value, root);
	}

	Pair* new_arr = ConvertationTA(root);
	for (int i = 0; i < x; i++) {
		printf("%d %s\n", new_arr[i].key, new_arr[i].value);

	}
*/

//main
/*
#define FST 1

#if FST!=1
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n;
	int range;
	scanf("%d", &n);
	scanf("%d", &range);
	pair* arr = malloc(n * sizeof(pair));
	for (int i = 0; i < n; i++) {
		int num;
		arr[i].value =malloc(4*sizeof(char));
		scanf("%d ", &num);
		for (int j = 0; j < 3; j++) {
			scanf("%c", &arr[i].value[j]);
			}
		arr[i].value[3] = 0;

		arr[i].key = num;
	}



	//for (size_t i = 0; i < n; i++)
	//{
	//	free(arr[i].value);
	//}
	//free(arr);



	return 0;
}
#else
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int num;
	scanf("%d", &num);

	hash_table* HT = init_HT(num*10);


	int* arr = malloc(num * sizeof(int));
	int size = 0;
	for (int i = 0; i < num; i++) {
		int x;
		scanf("%d", &x);
		if (contains_key(HT, x)==0) {
			append_pair(HT, (Pair) { x, 322 });
			arr[size] = x;
			size++;
		}

	}
	printf("%d %d\n ", size,num);
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}



	return 0;
}
#endif

*/


