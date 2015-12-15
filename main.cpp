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

{//ʹ��ģ�嶨��һ ������getArrayLen,�ú�������������array�ĳ���

	return (sizeof(array) / sizeof(array[0]));

}
*/
//��������������ڵ�
typedef struct bst_node {
	data_type data;
	struct bst_node *lchild, *rchild;
}bst_t,*bst_p;

//��������
void input_data(data_type *data, int n)
{
	int i;
	for (i = 0;i < n;i++)
	{
		cin >> data[i];
	}
}

//�������
void output_data(data_type *data, int n)
{
	int i;
	cout << "��������Ϊ��" << endl;
	for (i = 0;i < n;i++)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}

//��ӡ����
void Print(int *Num)            
{
	int i;
	for (i = 0; i<N; i++, Num++)
	{
		printf("%d ", *Num);
	}
	printf("\n");
	cout << "�����ˣ�" << (endTime.time - startTime.time) * 1000 + (endTime.millitm - startTime.millitm) << "����" << endl;
}

//Ѱ�Ҳ���λ�ã��������ַ��
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

//����ڵ�
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

//�������Ҷ�����
void creat_bst(bst_p *root, data_type *data, int n)
{
	int i;
	for (i = 0;i < n;i++)
	{
		insert_bst_node(root, data[i]);
	}
}

//�����㷨�����ؽڵ��ַ��
bst_p search(bst_p root, data_type key)
{
	if (root == NULL)
		return NULL;
	if (key > root->data) //����������  
		return search(root->rchild, key);
	else if (key < root->data) //����������  
		return search(root->lchild, key);
	else
		return root;
}

//ɾ���ڵ�
void delete_bst_node(bst_p *root, data_type data)
{
	bst_p p = *root, parent, s;
	parent = (bst_p)malloc(sizeof(struct bst_node));
	if (!p) {
		fprintf(stderr, "û�ҵ�%d��\n", data);
		return;
	}

	if (p->data == data) {
		/* Ҷ�Ӵ���취 */
		if (!p->rchild && !p->lchild) {
			*root = NULL;
			free(p);
		}
		/* �Ҷ���Ϊ�� */
		else if (!p->rchild) {
			*root = p->lchild;
			free(p);
		}
		/* �����Ϊ�� */
		else if (!p->lchild) {
			*root = p->rchild;
			free(p);
		}
		/* �ýڵ����������� */
		else 
		{
			s = p->rchild;
			/* sû������� */
			if (!s->lchild)
				s->lchild = p->lchild;
			/* ������� */
			else 
			{
				/* ��s�����������ҵ���С�Ľڵ� */
				while (s->lchild) /*s������Ӳ�Ϊ��ʱ*/
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

//����������������õ����С�
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

//�۰����
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

//��������
void CreateNum(int a[])
{
	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		a[i] = rand() % 10000;
	}
}

//ð������
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

//��������
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

//ѡ������
void Selection(int *Num, int n)    
{
	int i, j, Min, t;
	ftime(&startTime);
	for (i = 0; i<n; i++)
	{
		Min = i;//������Сֵ
		for (j = i + 1; j<n; j++)
			if (Num[Min]>Num[j])
				Min = j;//����
		if (Min != i)
		{
			t = Num[Min];
			Num[Min] = Num[i];
			Num[i] = t;
		}
	}
	ftime(&endTime);
}

//���ŷ�
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

//ѡ����
void function(int num[])
{
	cout << "1--ð������" << endl;
	cout << "2--��������" << endl;
	cout << "3--ѡ������" << endl;
	cout << "4--��������" << endl;
	int choice;
	CreateNum(num);
	cout << "�������ѡ��" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
		Bubble(num,N);
		cout << "ð������Ľ��Ϊ��" << endl;
		Print(num);
		break;
	case 2:
		Insert(num,N);
		cout << "��������Ľ��Ϊ��" << endl;
		Print(num);
		break;
	case 3:
		Selection(num, N);
		cout << "ѡ������Ľ��Ϊ��" << endl;
		Print(num);
		break;
	case 4:
		Quick(num, 0, N - 1);
		cout << "��������Ľ��Ϊ��" << endl;
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
	cout << "Ҫ������ٸ����ݣ�" << endl;
	cin >> n;
	data = (data_type*)malloc(n*sizeof(data_type));
	data_in_order_traverse = (data_type*)malloc(n*sizeof(data_type));
	cout << "����������" << endl;
	input_data(data, n);
	bst_root = NULL;
	for (i = 0;i < n;i++)
	{
		insert_bst_node(&bst_root, data[i]);
	}//�������Ҷ��������
	Inread(bst_root, data_in_order_traverse);
	count_i = 0;
	output_data(data_in_order_traverse, n);
	cout << "��������Ҫɾ���Ľڵ�" << endl;
	cin >> to_delete;
	delete_bst_node(&bst_root, to_delete);
	Inread(bst_root, data_in_order_traverse);
	output_data(data_in_order_traverse, n-1);
	CreateNum(num);
	while (is_countinue)
	{
		function(num);
		cout << "������<y/n>/n" << endl;
		cin >> choise;
		if (choise == 'n' || choise == 'N')
			is_countinue = false;
	}
	return 0;
}