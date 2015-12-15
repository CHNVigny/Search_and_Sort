#include <stdio.h>  
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <tchar.h>
#include <cstdlib>
#include <sys/timeb.h>
#include <ctime>
#include <climits>
#define N 10000

using namespace std;

typedef int data_type;

static int count_i = 0;

struct timeb startTime, endTime;

/*
template <class T>

int getArrayLen(T& array)

{//使用模板定义一 个函数getArrayLen,该函数将返回数组array的长度

	return (sizeof(array) / sizeof(array[0]));

}
*/
//建立二叉查找树节点
typedef struct bst_node {
	data_type data;
	struct bst_node *lchild, *rchild;
}bst_t,*bst_p;

//输入数据
void input_data(data_type *data, int n)
{
	int i;
	for (i = 0;i < n;i++)
	{
		cin >> data[i];
	}
}

//输出数据
void output_data(data_type *data, int n)
{
	int i;
	cout << "升序序列为：" << endl;
	for (i = 0;i < n;i++)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}

//打印数据
void Print(int *Num)            
{
	int i;
	for (i = 0; i<N; i++, Num++)
	{
		printf("%d ", *Num);
	}
	printf("\n");
	cout << "运行了：" << (endTime.time - startTime.time) * 1000 + (endTime.millitm - startTime.millitm) << "毫秒" << endl;
}

//寻找插入位置，返回其地址。
static bst_p search_bst_for_insert(bst_p *root, data_type key)
{
	bst_p s, p = *root;
	s = (bst_p)malloc(sizeof(struct bst_node));
	while (p) {
		s = p;

		if (p->data == key)
			return NULL;

		p = (key < p->data) ? p->lchild : p->rchild;
	}

	return s;
}

//插入节点
void insert_bst_node(bst_p *root, data_type data)
{
	bst_p s, p;

	s = (bst_p)malloc(sizeof(struct bst_node));
	if (!s)
		perror("Allocate dynamic memory");

	s->data = data;
	s->lchild = s->rchild = NULL;

	if (*root == NULL)
		*root = s;
	else {
		p = search_bst_for_insert(root, data);
		if (p == NULL) {
			fprintf(stderr, "The %d already exists.\n", data);
			free(s);
			return;
		}

		if (data < p->data)
			p->lchild = s;
		else
			p->rchild = s;
	}
}

//建立查找二叉树
void creat_bst(bst_p *root, data_type *data, int n)
{
	int i;
	for (i = 0;i < n;i++)
	{
		insert_bst_node(root, data[i]);
	}
}

//查找算法，返回节点地址。
bst_p search(bst_p root, data_type key)
{
	if (root == NULL)
		return NULL;
	if (key > root->data) //查找右子树  
		return search(root->rchild, key);
	else if (key < root->data) //查找左子树  
		return search(root->lchild, key);
	else
		return root;
}

//删除节点
void delete_bst_node(bst_p *root, data_type data)
{
	bst_p p = *root, parent, s;
	parent = (bst_p)malloc(sizeof(struct bst_node));
	if (!p) {
		fprintf(stderr, "没找到%d。\n", data);
		return;
	}

	if (p->data == data) {
		/* 叶子处理办法 */
		if (!p->rchild && !p->lchild) {
			*root = NULL;
			free(p);
		}
		/* 右儿子为空 */
		else if (!p->rchild) {
			*root = p->lchild;
			free(p);
		}
		/* 左儿子为空 */
		else if (!p->lchild) {
			*root = p->rchild;
			free(p);
		}
		/* 该节点有两个儿子 */
		else 
		{
			s = p->rchild;
			/* s没有左儿子 */
			if (!s->lchild)
				s->lchild = p->lchild;
			/* 有左儿子 */
			else 
			{
				/* 在s的左子树中找到最小的节点 */
				while (s->lchild) /*s的左儿子不为空时*/
				{
					parent = s;
					s = s->lchild;
				}
				parent->lchild = s->rchild;
				s->lchild = p->lchild;
				s->rchild = p->rchild;
			}
			*root = s;
			free(p);
		}
	}
	else if (data > p->data) {
		delete_bst_node(&(p->rchild), data);
	}
	else if (data < p->data) {
		delete_bst_node(&(p->lchild), data);
	}

}

//中序遍历二叉树，得到序列。
void Inread(bst_p root, int *data_in_order_traverse)
{
	if (root->lchild != NULL)
	{
		Inread(root->lchild, data_in_order_traverse);
	}
	data_in_order_traverse[count_i++] = root->data;
	if (root->rchild != NULL)
	{
		Inread(root->rchild, data_in_order_traverse);
	}
}

//折半查找
int BinSearch1(int k, int order[], int n)     
{
	int low, up, mid;
	low = 0;
	up = n - 1;
	while (low <= up)
	{
		mid = (low + up) / 2;
		if (order[mid] == k)
		{
			return mid;
		}
		else if (order[mid]>k)
		{
			up = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	return -1;
}

//生成数据
void CreateNum(int a[])
{
	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		a[i] = rand() % 10000;
	}
}

//冒泡排序
void Bubble(int *Num, int n)          
{
	int i, j;
	int tmp;
	ftime(&startTime);
	for (i = 0; i<n - 1; i++)
	{
		for (j = 0; j<n - 1 - i; j++)
		{
			if (Num[j]>Num[j + 1])
			{
				tmp = Num[j];
				Num[j] = Num[j + 1];
				Num[j + 1] = tmp;
			}
		}
	}
	ftime(&endTime);
}

//插入排序
void Insert(int *Num,int n)             
{
	int i, j;
	int temp;
	ftime(&startTime);
	for (i = 1; i<n; i++)
	{
		temp = *(Num + i);
		for (j = i; j>0 && *(Num + j - 1)>temp; j--)
		{
			*(Num + j) = *(Num + j - 1);
		}
		*(Num + j) = temp;
		//printf("%d\n", temp);
	}
	ftime(&endTime);
}

//选择排序
void Selection(int *Num, int n)    
{
	int i, j, Min, t;
	ftime(&startTime);
	for (i = 0; i<n; i++)
	{
		Min = i;//查找最小值
		for (j = i + 1; j<n; j++)
			if (Num[Min]>Num[j])
				Min = j;//交换
		if (Min != i)
		{
			t = Num[Min];
			Num[Min] = Num[i];
			Num[i] = t;
		}
	}
	ftime(&endTime);
}

//快排法
void Quick(int *v, int left, int right)
{
	ftime(&startTime);
	if (left < right)
	{
		int key = v[left];
		int low = left;
		int high = right;
		while (low < high)
		{
			while (low < high && v[high] > key)
			{
				high--;
			}
			v[low] = v[high];
			while (low < high && v[low] < key)
			{
				low++;
			}
			v[high] = v[low];
		}
		v[low] = key;
		Quick(v, left, low - 1);
		Quick(v, low + 1, right);
	}
	ftime(&endTime);
}

//选择功能
void function(int num[])
{
	cout << "1--冒泡排序" << endl;
	cout << "2--插入排序" << endl;
	cout << "3--选择排序" << endl;
	cout << "4--快速排序" << endl;
	int choice;
	CreateNum(num);
	cout << "输入你的选择" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
		Bubble(num,N);
		cout << "冒泡排序的结果为：" << endl;
		Print(num);
		break;
	case 2:
		Insert(num,N);
		cout << "插入排序的结果为：" << endl;
		Print(num);
		break;
	case 3:
		Selection(num, N);
		cout << "选择排序的结果为：" << endl;
		Print(num);
		break;
	case 4:
		Quick(num, 0, N - 1);
		cout << "快速排序的结果为：" << endl;
		Print(num);
		break;
	default:
		cout << "Quit";
		exit(0);
	}
	system("pause");
}
int main()
{
	data_type *data, *data_in_order_traverse, to_delete;
	int n, i;
	bst_t *bst_root;
	int num[N];
	bool is_countinue = true;
	char choise;
	cout << "要输入多少个数据？" << endl;
	cin >> n;
	data = (data_type*)malloc(n*sizeof(data_type));
	data_in_order_traverse = (data_type*)malloc(n*sizeof(data_type));
	cout << "请输入数据" << endl;
	input_data(data, n);
	bst_root = NULL;
	for (i = 0;i < n;i++)
	{
		insert_bst_node(&bst_root, data[i]);
	}//创建查找二叉树完毕
	Inread(bst_root, data_in_order_traverse);
	count_i = 0;
	output_data(data_in_order_traverse, n);
	cout << "请输入想要删除的节点" << endl;
	cin >> to_delete;
	delete_bst_node(&bst_root, to_delete);
	Inread(bst_root, data_in_order_traverse);
	output_data(data_in_order_traverse, n-1);
	CreateNum(num);
	while (is_countinue)
	{
		function(num);
		cout << "继续？<y/n>/n" << endl;
		cin >> choise;
		if (choise == 'n' || choise == 'N')
			is_countinue = false;
	}
	return 0;
}