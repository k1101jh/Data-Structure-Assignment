#include <iostream>
#include <random>
#include <time.h>
using namespace std;

// 배열을 깊은복사하는 함수 
int *CopyAry(int *ary, int arySize)
{
	int *newAry = new int[arySize];
	for(int i = 0; i < arySize; i++)
		newAry[i] = ary[i];
	return newAry;
}

// 배열을 출력하는 함수 
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

// 랜덤 배열을 생성하는 함수 
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

