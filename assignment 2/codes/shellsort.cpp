#include <math.h>
#include "shellsort.h"

// M�� ���ϴ� �Լ� 
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

// ���� ���� 
void insertionsort(int *A, int size, int start, int h)
{
	for (int Pick = start; Pick < size; Pick += h)
	{
		// �˻��� ������ ��ġ 
		int Current = Pick;
		// ������ ���� 
		int Temp = A[Pick];
		// ���� ��ġ�� ���� ������ ���ҵ��� �� ĭ�� ���������� �δ�. 
		for (; (Current >= h) && (A[Current - h] > Temp); Current -= h)
			A[Current] = A[Current - h];
		// ���� ���� 
		A[Current] = Temp;
	}
}

// �� ���� 
void shellsort(int *A, int size, int K)
{
	// K�� 1�� ��� ���� 1�� �������� ���� 
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
