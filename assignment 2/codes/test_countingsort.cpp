#include <iostream>
#include <fstream>
#include "countingsort.cpp"
#include "make_random_array.cpp"
#include "make_array.cpp"
using namespace std;

// �迭 ������ �ִ밪�� ���ϴ� �Լ� 
int GetK(int *A, int arySize)
{
	int max = A[0];
	for (int i = 1; i < arySize; i++)
	{
		if (A[i] > max)
		{
			max = A[i];
		}
	}
	return max;
}

int main(int argc, char *argv[])
{
	int arySize;
	int aryMaxNum;
	int *ary;
	
	if (argc == 2)
	{	// ���ڰ� �ϳ� �ԷµǾ��� ��� 
		ifstream fin;
		fin.open(argv[1]);
		if (!fin)
		{
			cout << "Can't open file" << endl;
			return 0;
		}
		ary = MakeAry(fin, arySize);
		fin.close();
	}
	else if(argc > 2)
	{	// ���ڰ� �ʹ� ���� �ԷµǾ��� ��� 
		cout << "Argument Error..." << endl;
		return 0;
	}
	else
	{	// ���ڰ� �Էµ��� �ʾ��� ��� 
		cout << "arySize >>";
		cin >> arySize;
		cout << "MaxNum >>";
		cin >> aryMaxNum;
		
		ary = MakeRandomArray(aryMaxNum, arySize);
		cout << "Random Array Generated!" << endl;
	}
	PrintAry(ary, arySize);

	// �迭�� �ִ밪 ���� 
	int k = GetK(ary, arySize);
	// �� ���� 
	cout << "Counting sort : " << endl;
	countingsort(ary, arySize, k);
	PrintAry(ary, arySize);
	
	delete[] ary;

	return 0;
}

