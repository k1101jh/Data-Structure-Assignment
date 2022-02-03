// 배열의 원소를 교환하는 함수
void Swap(int *A, int item1, int item2)
{
	int temp = A[item1];
	A[item1] = A[item2];
	A[item2] = temp;
}

// 피벗을 구해 피벗을 기준으로 나머지 원소를 정렬한다.
// 피벗보다 작은 원소는 피벗의 왼쪽에 위치
// 피벗보다 큰 원소는 피벗의 오른쪽에 위치
int Partition(int *A, int first, int last)
{
	int low, high, p;
	// 마지막 요소를 피벗으로 설정
	p = A[last];
	low = first;		// 업 포인터
	high = last - 1;	// 다운 포인터
	while(low <= high)
	{
		while(p > A[low]) low++;
		while(p < A[high]) high--;
		if(low <= high)
		{
			// 두 원소를 교환
			Swap(A, low, high);
			// 두 원소가 같을 시 발생하는 무한루프를 방지 
			if(A[low] == A[high])
				low++;
		}
	}
	// 업 포인터가 다운 포인터보다 커지면
	// 업 포인터의 원소와 피벗을 교환 
	Swap(A, low, last);
	return low;
}

// 퀵 정렬을 수행하는 함수 
void quicksort(int *A, int first, int last)
{
	if(first < last)
	{
		int pivotIndex = Partition(A, first, last);
		quicksort(A, first, pivotIndex - 1);
		quicksort(A, pivotIndex + 1, last);
	}
}
