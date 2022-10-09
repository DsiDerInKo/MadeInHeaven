#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a,b) (((a) > (b)) ? (a):(b))
#define Pi 3.14

typedef int (*cmpf) (void*, void*);

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void* bin_search(void* elem, void* arr, size_t size_arr, size_t size_elem, cmpf comp) {
	size_t i = 0, j = size_arr - 1;
	size_t middle;
	while (i <= j) {
		middle = (i + j) / 2;
		if (comp(elem, (char*)arr + middle * size_elem) < 0) {
			j = middle - 1;
		}
		else if (comp(elem, (char*)arr + middle * size_elem) > 0) {
			i = middle + 1;
		}
		else {
			return (char*)arr + middle * size_elem;
		}
		// чтобы получить индекс элемента (на который указывает результат функции)
		// можно пользоваться "формулой" (mid-arr)/size_elem 
		// для пользовательских типов данных достаточно mid-arr 
		//(в ином случае возвращается количество байт на промежутке mid-arr, 
		//из-за чего нужно разделить на тип)      (через char(...))
	}
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

typedef struct pairs {
	int key;
	char* value;
} pair;

void counting_sort(pair* arr, int len, int range) {

	int* new_len = calloc(range + 2, sizeof(int));
	for (int i = 0; i < len; i++) {
		new_len[arr[i].key + 1]++;
	}
	for (int i = 1; i <= range; i++) {
		new_len[i] += new_len[i - 1];
	}
	pair* new_arr = malloc(len * sizeof(pair));
	for (int i = 0; i < len; i++) {
		new_arr[new_len[arr[i].key]] = arr[i];
		new_len[arr[i].key]++;
	}

	memmove(arr, new_arr, len * sizeof(pair));
	free(new_arr);
	free(new_len);
}

unsigned int hash(int x) {
	unsigned long long new = x;
	new *= 1000000007;
	new = new >> 30;
	return (unsigned int)new;
}

typedef struct Pairs {
	int key;
	char* value;
} Pair;

typedef struct Nodes {
	Pair elem;
	struct Nodes* next;
	struct Nodes* prev;
} Node;

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

void del_node(Node* new) {

	new->prev->next = new->next;
	new->next->prev = new->prev;
	free(new);

	return;
}

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

//int main() {
//	freopen("input.txt", "r", stdin);
//	FILE* fout = fopen("output.txt", "w");
//	int n;
//	scanf("%d", &n);
//	srand(time(NULL));
//
//	int* arr;
//	
//	arr = malloc(n * sizeof(int));
//	for (int i = 0; i < n; i++) {
//		scanf("%d", &arr[i]);
//	}
//	
//	//Quick_sort(arr, n);
//	merge_sort(arr, n);
//	printf("%lld", c);
//
//	return 0;
//
//	// die alles Gute, Arigato за птсы 
//}


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
/*
void DeleteTree(NNode* root) {

	if (root == 0) return;

	DeleteTree(root->left);
	DeleteTree(root->right);

	free(root);

	return;

}
*/


/*
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


typedef struct  starts_ends {
	int start;
	int end;
}st;


typedef struct pars {
	int id;
	int points;
}par;

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

int main() {

	int* arr = malloc(3 * sizeof(int));
	arr[0] = 2;
	arr[1] = 10;
	arr[2] = 123;
	int* new1 = bin_search(&arr[0], arr, 3, sizeof(int), compare_int);
	int result = (new1 - arr);
	printf("%d", result);
	return 0;
}

/*

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
