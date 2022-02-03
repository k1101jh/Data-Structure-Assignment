#include <iostream>
using namespace std;

// ��Ʈ ��忡 �ִ� ���Ҹ� �����ϴ� �Լ� 
void DownHeap(int *A, int size, int current)
{
	int Child = 2 * current + 1;
	// ���� �ڽ��� �������� ������ �Լ� ���� 
	if(Child > size)
		return;
	else
	{
		int rChild = Child + 1;
		// ������ �ڽ��� �����ϰ� ������ �ڽ��� ���� �ڽĺ��� ũ��
		// ���� ū ���� �ε����� ������ �ڽ����� 
		if((rChild <= size) && (A[rChild] > A[Child]))
			Child = rChild;
		// �� �ڽ� �� ū �ڽ��� ���� ��庸�� ũ��
		// ��ȯ �� ����Լ� ȣ�� 
		if(A[current] < A[Child])
		{
			Swap(A, current, Child);
			DownHeap(A, size, Child);
		}
	}
}

// ���� ��Ʈ��带 �����ϴ� �Լ� 
int remove_heap(int *A, int size)
{
	A[0] = A[size - 1];
	size--;
	DownHeap(A, size, 0);
	return size;
}

