// �迭�� �� ���Ҹ� ��ȯ�ϴ� �Լ� 
void Swap(int *A, int item1, int item2)
{
	int temp = A[item1];
	A[item1] = A[item2];
	A[item2] = temp;
}

// �迭�� �Է¹޾� heap�� �����ϴ� �Լ� 
void build_heap(int *A, int size)
{
	int * tempAry = new int[size];
	int index = 0;
	// �迭�� ���� ���� 
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
