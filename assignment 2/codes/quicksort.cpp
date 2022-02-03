// �迭�� ���Ҹ� ��ȯ�ϴ� �Լ�
void Swap(int *A, int item1, int item2)
{
	int temp = A[item1];
	A[item1] = A[item2];
	A[item2] = temp;
}

// �ǹ��� ���� �ǹ��� �������� ������ ���Ҹ� �����Ѵ�.
// �ǹ����� ���� ���Ҵ� �ǹ��� ���ʿ� ��ġ
// �ǹ����� ū ���Ҵ� �ǹ��� �����ʿ� ��ġ
int Partition(int *A, int first, int last)
{
	int low, high, p;
	// ������ ��Ҹ� �ǹ����� ����
	p = A[last];
	low = first;		// �� ������
	high = last - 1;	// �ٿ� ������
	while(low <= high)
	{
		while(p > A[low]) low++;
		while(p < A[high]) high--;
		if(low <= high)
		{
			// �� ���Ҹ� ��ȯ
			Swap(A, low, high);
			// �� ���Ұ� ���� �� �߻��ϴ� ���ѷ����� ���� 
			if(A[low] == A[high])
				low++;
		}
	}
	// �� �����Ͱ� �ٿ� �����ͺ��� Ŀ����
	// �� �������� ���ҿ� �ǹ��� ��ȯ 
	Swap(A, low, last);
	return low;
}

// �� ������ �����ϴ� �Լ� 
void quicksort(int *A, int first, int last)
{
	if(first < last)
	{
		int pivotIndex = Partition(A, first, last);
		quicksort(A, first, pivotIndex - 1);
		quicksort(A, pivotIndex + 1, last);
	}
}
