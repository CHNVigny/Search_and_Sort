#include <stdio.h>  
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef int data_type;

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

//Ѱ�Ҳ���λ�ã��������ַ��
static bst_t *search_bst_for_insert(bst_t *root, data_type key)
{
	bst_t *s, *p = root;
	s = (bst_t*)malloc(sizeof(struct bst_node));
	while (p) {
		s = p;

		if (p->data == key)
			return NULL;

		p = (key < p->data) ? p->lchild : p->rchild;
	}

	return s;
}

//����Ҷ������в���ڵ�
void insert_bst_node(bst_p *root, data_type data)
{
	bst_t *s, *p;
	s = (bst_t*)malloc(sizeof(struct bst_node));
	if (!s)
		perror("Allocate dynamic memory");

	s->data = data;
	s->lchild = s->rchild = NULL;

	if (*root == NULL)
	{
		*root = s;
	}
	else {
		p = search_bst_for_insert(*root, data);
		if (p == NULL) {
			fprintf(stderr, "����%d�Ѿ����ڡ�\n", data);
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
/*
void creat_bst(bst_t *root, data_type *data, int n)
{
	int i;
	for (i = 0;i < n;i++)
	{
		insert_bst_node(root, data[i]);
	}
}*/

int main()
{
	data_type *data;
	int n, i;
	bst_t *bst_root;
	cout << "Ҫ������ٸ����ݣ�" << endl;
	cin >> n;
	data = (data_type*)malloc(n*sizeof(data_type));
	cout << "����������" << endl;
	input_data(data, n);
	bst_root = NULL;
	for (i = 0;i < n;i++)
	{
		insert_bst_node(bst_root, data[i]);
	}
	return 0;
}