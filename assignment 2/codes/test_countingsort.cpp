#include <iostream>
#include <fstream>
#include "countingsort.cpp"
#include "make_random_array.cpp"
#include "make_array.cpp"
using namespace std;

// 배열 원소의 최대값을 구하는 함수 
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
	{	// 인자가 하나 입력되었을 경우 
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
	{	// 인자가 너무 많이 입력되었을 경우 
		cout << "Argument Error..." << endl;
		return 0;
	}
	else
	{	// 인자가 입력되지 않았을 경우 
		cout << "arySize >>";
		cin >> arySize;
		cout << "MaxNum >>";
		cin >> aryMaxNum;
		
		ary = MakeRandomArray(aryMaxNum, arySize);
		cout << "Random Array Generated!" << endl;
	}
	PrintAry(ary, arySize);

	// 배열의 최대값 구함 
	int k = GetK(ary, arySize);
	// 셈 정렬 
	cout << "Counting sort : " << endl;
	countingsort(ary, arySize, k);
	PrintAry(ary, arySize);
	
	delete[] ary;

	return 0;
}

