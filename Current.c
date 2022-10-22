#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#define max(a,b) (((a) > (b)) ? (a):(b))
#define min(a,b) (((a) < (b)) ? (a):(b))
#define TYPE_OF int

typedef int (*cmpf) (void*, void*);

typedef struct pairss {
	int key;
	char* value;
} pairs;

typedef struct Pairs {
	unsigned int key;
	TYPE_OF value;
} Pair;

typedef struct Nodes {

	Pair elem;
	struct Nodes* next;
	struct Nodes* prev;

} Node;

typedef struct  starts_ends {
	int start;
	int end;
}st;

typedef struct pars {
	int id;
	int points;
}par;

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

#define Vector_type int
typedef struct Vectors {

	size_t size;
	size_t capacity;
	Vector_type* data;

} Vector;

Vector* init_vector() {

	Vector* vector = malloc(sizeof(Vector));
	vector->capacity = 2;
	vector->size = 0;
	vector->data = malloc(vector->capacity*sizeof(Vector_type));

	return vector;
}

void vector_resize(Vector* self,size_t new_size) {
	self->data = realloc(self->data,new_size*sizeof(Vector_type));
	self->capacity = new_size;
	self->size = min(self->size, new_size);
}

void vector_append(Vector* self,Vector_type elem) {
	if (self->capacity == self->size) vector_resize(self, self->capacity << 1);
	self->data[self->size++] = elem;
}

Vector_type vector_pop(Vector* self) {
	if ((self->size << 2) + 1 <= self->capacity) vector_resize(self,(self->capacity>>1)+1);
	return self->data[--self->size];
}

void clear_vector(Vector* self){
	self->size = 0;
}

unsigned int hash(int x) {
	unsigned long long new = x;
	new *= 1000000007;
	new = new >> 30;
	return (unsigned int)new;
}

void* bin_search(void* elem, void* arr, size_t size_arr, size_t size_elem, cmpf comp) {
	size_t i = 0, j = size_arr - 1;
	size_t middle;
	void* answer=0;
	while (i <= j) {
		middle = (i + j) / 2;
		if (comp(elem, (char*)arr + middle * size_elem) < 0) {
			j = middle - 1;
		}
		else if (comp(elem, (char*)arr + middle * size_elem) > 0) {
			i = middle + 1;
		}
		else {
			answer =(char*)arr + middle * size_elem;
			break;
		}
		// чтобы получить индекс элемента (на который указывает результат функции)
		// можно пользоваться "формулой" (mid-arr)/size_elem 
		// для пользовательских типов данных достаточно mid-arr 
		//(в ином случае возвращается количество байт на промежутке mid-arr, 
		//из-за чего нужно разделить на тип)      (через char(...))
	}

	return comp(answer, elem) == 0 ? answer : NULL;
}

void* bin_search_up(void* elem, void* arr, size_t size_arr, size_t size_elem, cmpf comp) {
	size_t i = 0, j = size_arr - 1;
	size_t middle;
	void* answer = 0;
	while (i < j) {
		middle = (i + j) / 2;
		if (comp(elem, (char*)arr + middle * size_elem) >= 0) {
			i = middle+1;
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

void* bin_search_down(void* elem, void* arr, size_t size_arr, size_t size_elem, cmpf comp) {
	size_t i = 0, j = size_arr - 1;
	size_t middle;
	void* answer = 0;
	while (i < j) {
		middle = (i + j) / 2;
		if (comp(elem, (char*)arr + middle * size_elem) <= 0){
			j = middle;
		}
		else {
			i = middle + 1;
		}
	}
	
	answer = (char*)arr + i * size_elem;
	return comp(answer, elem) == 0 ? answer : NULL;
}

void* lower_bound(void* elem, void* arr, size_t size_arr, size_t size_elem, cmpf comp) {
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

void insertion_sort(int* arr, int num) {
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

void selection_sort(int* arr, int number) {

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

int UN_partition_po_pivu(void* arr, size_t size_arr, size_t size_elem, void* pivot, cmpf cmp) {
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

void UN_quick_sort(void* arr, size_t size_arr, size_t size_elem, cmpf cmp) {

	if (size_arr <= 1) {
		return;
	}
	void* pivot = malloc(size_elem);
	int ran = (int)rand() % size_arr;
	memcpy(pivot, (void*)((char*)arr + ran * size_elem), size_elem);
	int bound = UN_partition_po_pivu(arr, size_arr, size_elem, pivot, cmp);
	free(pivot);
	UN_quick_sort(arr, bound, size_elem, cmp);
	UN_quick_sort((void*)((char*)arr + bound * size_elem), size_arr - bound, size_elem, cmp);

	return;
}

int partition_po_pivu(int* arr, int len, int pivot) {

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

int partition_piva(int* arr, int left, int right) {
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

void quick_sort(int* arr, int len) {

	if (len <= 1) {
		return;
	}
	int ran = (int)rand() % len;
	int bound = partition_po_pivu(arr, len, arr[ran]);
	quick_sort(arr, bound);
	quick_sort(arr + bound, len - bound);

	return;
}

void buble_sort(int* arr, int arr_len) {

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
	return;
}

void merge(int* arr1, int* arr2, int len1, int len2, int* res) {

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

void merge_sort(int* arr, int len) {
	if (len <= 1) {
		return;
	}
	int* arr1 = arr;
	int* arr2 = len / 2 + arr;
	int n1 = len / 2;
	int n2 = len - n1;
	merge_sort(arr1, n1);
	merge_sort(arr2, n2);
	int* res = malloc(len * sizeof(int));
	merge(arr1, arr2, n1, n2, res);
	memmove(arr, res, len * sizeof(int));
	free(res);
}

void counting_sort(pairs* arr, int len, int range) {

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

int Find_K_Statistics(int* arr, int number, int point) {
	int left_arr = 0, right_arr = number - 1;
	while (1) {
		int mid = partition_piva(arr, left_arr, right_arr);
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

Pair init_Pair(unsigned int key, TYPE_OF value) {

	Pair elem;
	elem.key = key;
	elem.value = value;

	return elem;
}

Node* init_Node(Pair elem) {

	Node* new_node = malloc(sizeof(Node));
	new_node->elem = elem;
	new_node->next = new_node;
	new_node->prev = new_node;

	return new_node;
}

Node* create_head() {

	Node* new = malloc(1 * sizeof(Node));
	new->next = new;
	new->prev = new;

	return new;
}

void append_after(Pair new, Node* dot) {

	Node* new_dot = malloc(1 * sizeof(Node));
	new_dot->elem = new;
	new_dot->next = dot->next;
	dot->next->prev = new_dot;
	dot->next = new_dot;
	new_dot->prev = dot;

	return;
}

void append_before(Pair new, Node* dot) {

	Node* new_dot = malloc(1 * sizeof(Node));
	new_dot->elem = new;
	dot->prev->next = new_dot;
	new_dot->prev = dot->prev;
	dot->prev = new_dot;
	new_dot->next = dot;

	return;
}

Pair del_node(Node* new) {

	new->prev->next = new->next;
	new->next->prev = new->prev;
	Pair temp = new->elem;
	free(new);

	return temp;
}

//Hash table + tree
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
		append_after(pair, HT->arr[idex]);
	}
	else {
		HT->arr[idex] = create_head();
		append_after(pair, HT->arr[idex]);
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
				del_node(t);
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
				del_node(t);
			}
			del_node(HT->arr[i]);
		}
	}
	free(HT->arr);
	free(HT);
}

typedef struct NNodes {

	int key;
	void* value;
	struct NNodes* left;
	struct NNodes* right;

} NNode;

NNode* init_Node(int key, void* value) {

	NNode* Node = malloc(sizeof(NNode));
	Node->key = key;
	Node->value = value;
	Node->left = 0;
	Node->right = 0;

	return Node;
}

NNode* append_root(int key, void* value, NNode* root) {

	if (root == 0) {
		root = init_Node(key, value);
		return root;
	}

	if (key < root->key) {
		root->left = append_root(key, value, root->left);
	}

	else {
		root->right = append_root(key, value, root->right);
	}
	return root + 0;
}

NNode* find(NNode* root, int key) {

	if (root == 0) {
		return 0;
	}
	if (key == root->key) {
		return root;
	}
	NNode* N;
	if (key < root->key) {
		N = find(key, root->left);
	}
	else {
		N = find(key, root->right);
	}
	return N;

}

int count(NNode* root) {
	if (root == 0) return 0;
	return count(root->left) + 1 + count(root->right);
}

void Tree_to_Array(NNode* root, Pair* arr, int* i) {

	if (root == 0) return;

	Tree_to_Array(root->left, arr, i);

	arr[*i].key = root->key;
	arr[*i].value = root->value;
	*i = *i + 1;

	Tree_to_Array(root->right, arr, i);

	return;
}

Pair* ConvertationTA(NNode* root) {

	int i = 0;
	int size = count(root);
	Pair* arr = malloc(size * sizeof(Pair));

	Tree_to_Array(root, arr, &i);

	return arr;
}

*/

//Functions for tree
/*
void DeleteTree(NNode* root) {

	if (root == 0) return;

	DeleteTree(root->left);
	DeleteTree(root->right);

	free(root);

	return;

}

NNode* remove(NNode* root, int key) {

	if (root == 0) {
		return 0;
	}
	if (key == root->key) {
		return root;
	}
	NNode* N;
	if (key < root->key) {
		N = remove(root->left,key);
	}
	else {
		N = remove(root->right,key);
	}

	return N;
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

int compare_for_E(void* x, void* y) {
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

int compare_for_st(void* x, void* y) {
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

int compare_int(void* x, void* y) {

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

void solver_4(Node* stack,char* string) {
	int num,temp;
	operand op = is_operand(string);

	if (op == not_operand) {
		printf("%d\n", stack->prev->elem.value);
	}
	else if(op == plus) {
		scanf("%d", &num);
		temp = stack->prev->elem.value;
		num = max(num, temp);
		append_before(init_Pair(1, num), stack);
	}
	else if (op == minus) {
		del_node(stack->prev);
	}
}

void solver_3(Node* stack,char* string) {
	
	operand op = is_operand(string);

	if (op == not_operand) {
		append_before(init_Pair(1, atoi(string)), stack);
	}
	else {
		Pair element2 = del_node(stack->prev);
		Pair element1 = del_node(stack->prev);
		append_before(init_Pair(1, do_math(element1.value, element2.value, op)), stack);
	}
	return 0;
}

int main() {

	int number, elem;
	char operand;
	
	Vector* vec = init_vector();
	scanf("%d", &number);
	for (;;) {
		do {
			if (scanf("%c", &operand) < 1) return 0;
		} while (isspace(operand));
		if (operand == '+') {
			scanf("%d", &elem);
			vector_append(vec, elem);
		}
		if (operand == '-') {
			printf("%d\n", vector_pop(vec));
		}
	}

	return 0;
}
//Division of array
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
		int index = (int*) lower_bound(&temp, pref, number + 1, sizeof(int), compare_int) - pref;

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
	UN_quick_sort(arr1, number1, sizeof(int), compare_int);
	UN_quick_sort(arr2, number2, sizeof(int), compare_int);
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
	UN_quick_sort(arr1, number1, sizeof(int), compare_int);
	UN_quick_sort(arr2, number2, sizeof(int), compare_int);
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
# Линейные рекурентные соотношения(через калькулятор)
# f(n) = 2 * f(n - 1) + 2 - f(n - 2)
# f(n) = n * (c2 - 1 + n) + c1
# f(1) = c2 + c1 = A <=> c1 = A - c2
# f(n) = n ^ 2 + n * (c2 - 1) + A - c2

# ищем миниму на отрезке[1, number]
# 1 <= n <= number
# n = 1 / 2 - c2 / 2
#      |
# 1 - 2 * number <= c2 <= -1

# минимум этой функции(строчка выше) достгается при n = -(c2 - 1) / 2
# можно подставить и получить это минимальное значение
# однако n - целое и принадлежит от 1 до number, так что
# необходимо узнать значения около этой точки
# f(n) = c2 * (n - 1) + (n - 1) * n + A - фин.формула
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

	UN_quick_sort(arr, number, sizeof(st), compare_for_st);

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