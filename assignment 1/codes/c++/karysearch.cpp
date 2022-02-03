#include <iostream>
#include <fstream>
using namespace std;

int KarySearch(int A[], int k, int start, int end, int key)
{
	int dividedNum = (end - start + 2) / k;				// k ���� ���� �� 
	if(start > end)										// ���� �������� ������ 
		return 0;										// 0 ���� 
	else
	{
		if(dividedNum == 0)								// ���� ���� ���� k������ ���� ��� 
		{
			int remainder = end - start + 1;		// ���� ���� �� ��� 
			for(int i = 0; i < remainder; i++)			// ���������� �� 
			{
				if(A[start + i] == key)					// ���� ã���� 
					return start + i + 1; 				// �� ���� 
			}
			return 0;
		}
		else
		{
			int checkNum;								// �񱳸� ������ ���� ��ġ 
			for(int i = 1; i < k; i++)
			{
				checkNum = (start - 1) + i * dividedNum;
				//cout << A[checkNum] << " "; Ž�� ��ġ�� �� 
				if (A[checkNum] == key)					// �񱳰��� ã�� ���� ��� 
					return checkNum + 1;				// ��ġ ���� 
				else if(A[checkNum] > key)				// �񱳰��� Ŭ ��� 
				{										// ����Լ� ȣ�� 
					return KarySearch(A, k, checkNum - dividedNum + 1, checkNum - 1, key);
				}
			}										// ������ �񱳰��� �迭�� end��ġ�� �� 
			if(key > A[end])		// �迭�� ������ ������ ū ��� 
				return 0;			// ���� ã�� �� ���� 
			else
			{						// ����Լ� ȣ�� 
				return KarySearch(A, k, checkNum + 1, end, key);
			}	
		}
	}
}

int main(int argc, char *argv[])
{	
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
		fin >> ary[count++];
		if(count >= arysize)
		{
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
	
	int numToFind = 0, k;
	 
	cout << "ã���÷��� ���ڸ� �Է��� �ּ���>> ";
	cin >> numToFind;
	
	cout << "�����͸� �� ���� ��Ʈ�� ������ �Է��� �ּ��� >> ";
	cin >> k;
	
	int rank = KarySearch(ary, k, 0, count - 1, numToFind);
	if(rank == 0)
		cout << "ã���÷��� ���ڴ� �������� �ʽ��ϴ�." << endl;
	else 
		cout << numToFind << "�� " << rank << "��°�� ��ġ�� �ֽ��ϴ�." << endl;
}
