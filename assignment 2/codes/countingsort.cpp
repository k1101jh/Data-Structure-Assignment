#include <iostream>
using namespace std;

void countingsort(int *A, int size, int k)
{
	// ũ�Ⱑ k + 1�� �迭 ���� 
	int Count[k + 1] = {0};
	int *tempArray = new int[size];
	for(int i = 0; i < size; i++)
	{
		// �󵵸� ���� 
		Count[A[i]]++;
		// �迭 ���� 
		tempArray[i] = A[i]; 
	}
	
	// �迭 ��ġ�� 1���� �����ϴ°��� ���� ����
	Count[0]--;
	// ���踦 ���� 
	for(int i = 0; i < k; i++)
		Count[i + 1] += Count[i];
	
	for(int i = size - 1; i >= 0; i--)
	{
		int pos = Count[tempArray[i]];
		A[pos] = tempArray[i];
		Count[tempArray[i]]--;
	}
	delete[] tempArray;
}
