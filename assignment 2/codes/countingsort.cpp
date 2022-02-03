#include <iostream>
using namespace std;

void countingsort(int *A, int size, int k)
{
	// 크기가 k + 1인 배열 생성 
	int Count[k + 1] = {0};
	int *tempArray = new int[size];
	for(int i = 0; i < size; i++)
	{
		// 빈도를 구함 
		Count[A[i]]++;
		// 배열 복사 
		tempArray[i] = A[i]; 
	}
	
	// 배열 위치가 1부터 시작하는것을 막기 위함
	Count[0]--;
	// 누계를 구함 
	for(int i = 0; i < k; i++)
		Count[i + 1] += Count[i];
	
	for(int i = size - 1; i >= 0; i--)
	{
		int pos = Count[tempArray[i]];
		A[pos] = tempArray[i];
		Count[tempArray[i]]--;
	}
	delete[] tempArray;
}
