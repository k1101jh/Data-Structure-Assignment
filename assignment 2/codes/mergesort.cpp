// mergesort로 나눈 배열을 합쳐서 정렬하는 함수
void Merge(int *A, int first, int mid, int last)
{
	int* temp = new int[last - first + 1];
	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;
	int index = 0;
	// 임시 저장 공간에 데이터 정렬 
	for(; (first1 <= last1) && (first2 <= last2); ++index)
	{
		if(A[first1] < A[first2])
		{
			temp[index] = A[first1];
			++first1;
		}
		else
		{
			temp[index] = A[first2];
			++first2;
		}
	}
	for(; first1 <= last1; ++first1, ++index)
		temp[index] = A[first1];
	for(; first2 <= last2; ++first2, ++index)
		temp[index] = A[first2];
	// 임시 저장 공간의 데이터를 원래 배열로 복사시킴 
	for(index = first; index <= last; ++index)
		A[index] = temp[index - first];
	delete[] temp;
}

// 합병 정렬을 실행하는 함수 
void mergesort(int A[], int first, int last)
{
	if(first < last)
	{
		int middle = (first + last) / 2;
		mergesort(A, first, middle);
		mergesort(A, middle + 1, last);
		Merge(A, first, middle, last);
	}
}
