#include <iostream>
#include <fstream>
using namespace std;

int BinarySearch(int A[], int start, int end, int key)
{
	if(start > end)									// ���� �������� ���� ��� 
		return 0;									// 0 ���� 
	else
	{
		int mid = (start + end) / 2;				// �߰� ��ġ ���ϱ� 
		if(A[mid] == key)							// �߰����� ã������ ���� ���� ��� 
			return (mid + 1);						// �� ���� 
		else if(A[mid] > key)						// �߰������� ���� ��� 
			BinarySearch(A, start, mid - 1, key);	// ��� ȣ�� 
		else										// �߰������� Ŭ ��� 
			BinarySearch(A, mid + 1, end, key);		// ��� ȣ�� 
	}
}

int main(int argc, char *argv[])
{
	// ���� ���� 
	ifstream fin;
	fin.open(argv[1]);
	if(!fin)
	{
		cout << "������ �� �� �����ϴ�." << endl;
		return 0;
	}
	
	int arysize = 10;
	int *ary = new int[arysize];
	int count = 0; 
	
	while(!fin.eof())
	{
		fin >> ary[count++];						// ary�� ������ �� �߰� 
		if(count >= arysize)						// ���� �迭�� ������ �����ϴٸ� 
		{											// �迭�� ũ�⸦ 2��� �ø��� 
			arysize *= 2;
			int *newAry = new int[arysize];
			for(int i = 0; i < arysize/2; i++)
			{
				newAry[i] = ary[i];
			}
			delete [] ary;
			ary = newAry;
		}

	}
	
	int numToFind = 0;
	 
	cout << "ã���÷��� ���ڸ� �Է��� �ּ���>> ";
	cin >> numToFind;
	
	int rank = BinarySearch(ary, 0, count - 1, numToFind);	// ����Ž�� ���� 
	if(rank == 0)
		cout << "ã���÷��� ���ڴ� �������� �ʽ��ϴ�." << endl;
	else 
		cout << numToFind << "�� " << rank << "��°�� ��ġ�� �ֽ��ϴ�." << endl;
}
