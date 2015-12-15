#include <stdio.h>  
#include <stdlib.h>
#include <iostream>

using namespace std;
typedef int data_type;

//节点信息
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
	cout << "要输入多少个数据？" << endl;
	cin >> n;
	data = (data_type*)malloc(n*sizeof(data_type));
	cout << "请输入数据" << endl;
	print_data(data, n);
	bst_root = NULL;
	creat_bst(bst_root, data, n);
	return 0;
}