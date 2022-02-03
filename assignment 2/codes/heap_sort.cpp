#include <iostream>
using namespace std;

// 루트 노드에 있는 원소를 정렬하는 함수 
void DownHeap(int *A, int size, int current)
{
	int Child = 2 * current + 1;
	// 왼쪽 자식이 존재하지 않으면 함수 종료 
	if(Child > size)
		return;
	else
	{
		int rChild = Child + 1;
		// 오른쪽 자식이 존재하고 오른쪽 자식이 왼쪽 자식보다 크면
		// 가장 큰 것의 인덱스를 오른쪽 자식으로 
		if((rChild <= size) && (A[rChild] > A[Child]))
			Child = rChild;
		// 두 자식 중 큰 자식이 현재 노드보다 크면
		// 교환 후 재귀함수 호출 
		if(A[current] < A[Child])
		{
			Swap(A, current, Child);
			DownHeap(A, size, Child);
		}
	}
}

// 힙의 루트노드를 삭제하는 함수 
int remove_heap(int *A, int size)
{
	A[0] = A[size - 1];
	size--;
	DownHeap(A, size, 0);
	return size;
}

