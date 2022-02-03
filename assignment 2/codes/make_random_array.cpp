#include <iostream>
#include <random>
#include <time.h>
using namespace std;

// �迭�� ���������ϴ� �Լ� 
int *CopyAry(int *ary, int arySize)
{
	int *newAry = new int[arySize];
	for(int i = 0; i < arySize; i++)
		newAry[i] = ary[i];
	return newAry;
}

// �迭�� ����ϴ� �Լ� 
void PrintAry(int *A, int arySize)
{
	for (int i = 0; i < arySize; i++)
	{
		cout << A[i] << " ";
		if ((i + 1) % 15 == 0)
			cout << endl;
	}
	cout << endl;
}

// ���� �迭�� �����ϴ� �Լ� 
int *MakeRandomArray(int maxNum, int length)
{
	srand((int)time(0));
	int size = length;
	int *ary = new int[size];
	for (int i = 0; i < size; i++)
	{
		ary[i] = rand() % maxNum;
	}
	return ary;
}

