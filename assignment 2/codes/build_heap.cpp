// 배열의 두 원소를 교환하는 함수 
void Swap(int *A, int item1, int item2)
{
	int temp = A[item1];
	A[item1] = A[item2];
	A[item2] = temp;
}

// 배열을 입력받아 heap을 구성하는 함수 
void build_heap(int *A, int size)
{
	int * tempAry = new int[size];
	int index = 0;
	// 배열의 원소 복사 
	for(int i = 0; i < size; i++)
		tempAry[i] = A[i];
	
	for(int i = 0; i < size; i++)
	{
		A[index] = tempAry[i];
		int current = index;
		int parent = (current - 1) /2;
		while((current != 0) && (A[current] > A[parent]))
		{
			Swap(A, current, parent);
			current = parent;
			parent = (current - 1) / 2;
		}
		index++;
	}
	delete[] tempAry;
}
