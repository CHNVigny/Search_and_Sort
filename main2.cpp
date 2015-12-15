#include <stdio.h>  
#include <stdlib.h>
#include <iostream>

using namespace std;
typedef int data_type;

//�ڵ���Ϣ
typedef struct bst_node {
	data_type val;
	struct bst_node *lchild, *rchild;
}bst_t,*bst_p;

bst_p insert(bst_p root, int x)
{
	bst_p p = (bst_p)malloc(sizeof(bst_p));
	p->val = x;
	p->lchild = NULL;
	p->rchild = NULL;
	if (root == NULL) 
	{
		root = p;
	}
	else if (x < root->val) {
		root->lchild = insert(root->lchild, x);
	}
	else {
		root->rchild = insert(root->rchild, x);
	}
	return root;
}

int main()
{
	data_type *data;
	int n;
	bst_t *bst_root;
	cout << "Ҫ������ٸ����ݣ�" << endl;
	cin >> n;
	data = (data_type*)malloc(n*sizeof(data_type));
	cout << "����������" << endl;
	print_data(data, n);
	bst_root = NULL;
	creat_bst(bst_root, data, n);
	return 0;
}