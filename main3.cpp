#include<iostream>
#include <stdio.h>  
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <tchar.h>
#include <cstdlib>
#include <sys/timeb.h>
#include <ctime>
#include <climits>
struct timeb startTime, endTime;
#define N 10000
using namespace std;

void CreateNum(int a[]);
void Print(int *Num);
void Bubble(int *Num);
void Insert(int *Num);
void Selection(int *Num);
int BinSearch1(int k, int order[]);
void Quick(int *v, int left, int right);
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
		Bubble(num);
		cout << "冒泡排序的结果为：" << endl;
		Print(num);
		break;
	case 2:
		Insert(num);
		cout << "插入排序的结果为：" << endl;
		Print(num);
		break;
	case 3:
		Selection(num);
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
}
int main()
{
	int num[N];
	char answer;
	int k, n, is_countinue=1;
	CreateNum(num);
	while (is_countinue)
	{
		function(num);
		cout << "继续？" << endl;
		cin >> is_countinue;
	}
	
	system("pause");
	return 0;
}


void CreateNum(int a[])
{
	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		a[i] = rand() % 10000;
	}
}

void Print(int *Num)            //打印数据
{
	int i;
	for (i = 0; i<N; i++, Num++)
	{
		printf("%d ", *Num);
	}
	printf("\n");
}
int BinSearch1(int k, int order[])     //折半查找
{
	int low, up, mid;
	low = 0;
	up = N - 1;
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
void Insert(int *Num, int n)
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

//快排法  O(nlgn)
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