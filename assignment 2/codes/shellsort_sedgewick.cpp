//  sedgewick 방식의 M을 구하는 함수 
int CalcM_sedgewick(int size)
{
	int i = 1;
	while ( pow(4, i) + 3 * pow(2, (i - 1)) + 1 < size)
	{
		i++;
	}
	i--;
	return i;
}

void insertionsort_sedgewick(int *A, int size, int start, int h)
{
	for(int Pick = start; Pick < size; Pick += h)
	{
		int Current = Pick;
		int Temp = A[Pick];
		for(; (Current >= h) && (A[Current - h] > Temp); Current -= h)
			A[Current] = A[Current - h];
		A[Current] = Temp;
	}
}

// sedgewick 방식의 shellsort 
void shellsort_sedgewick(int *A, int size)
{
	int m = CalcM_sedgewick(size);
	for (int i = m; i > 0; i--)
	{
		int h = pow(4, i) + 3 * pow(2, (i - 1)) + 1;
		for (int j = 0; j < h; j++)
			insertionsort_sedgewick(A, size, j, h);
	}
	insertionsort_sedgewick(A, size, 0, 1);
}

