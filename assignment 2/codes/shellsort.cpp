#include <math.h>
#include "shellsort.h"

// M을 구하는 함수 
int CalcM(int size, int K)
{
	int i = 1;
	int newN = size * (K - 1) + 1;
	while (pow(K, i) < newN)
	{
		i++;
	}
	i--;
	return i;
}

// 삽입 정렬 
void insertionsort(int *A, int size, int start, int h)
{
	for (int Pick = start; Pick < size; Pick += h)
	{
		// 검사할 원소의 위치 
		int Current = Pick;
		// 삽입할 원소 
		int Temp = A[Pick];
		// 삽입 위치가 나올 때까지 원소들을 한 칸씩 오른쪽으로 민다. 
		for (; (Current >= h) && (A[Current - h] > Temp); Current -= h)
			A[Current] = A[Current - h];
		// 원소 삽입 
		A[Current] = Temp;
	}
}

// 셸 정렬 
void shellsort(int *A, int size, int K)
{
	// K가 1인 경우 간격 1인 삽입정렬 실행 
	if (K == 1)
		insertionsort(A, size, 1, 1);
	else
	{
		int m = CalcM(size, K);
		for (int i = m; i > 0; i--)
		{
			int h = (pow(K, i) - 1) / (K - 1);
			for(int j = 0; j < h; j++)
				insertionsort(A, size, j, h);
		}
	}
}
