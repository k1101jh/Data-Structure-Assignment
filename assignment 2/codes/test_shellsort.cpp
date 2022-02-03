#include <iostream>
#include <fstream>
#include "shellsort.h"
#include "make_random_array.cpp"
#include "make_array.cpp"
using namespace std;

int main(int argc, char* argv[])
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
		PrintAry(ary, arySize);
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
		// ���� �迭�� ����� �Լ�
		// (���� ������ �ִ밪, �迭�� ũ��)
		ary = MakeRandomArray(aryMaxNum, arySize);
		cout << "Random Array Generated!" << endl;
		PrintAry(ary, arySize);
	}
	
	int K = 0;
	while (K > 3 || K < 1)
	{	// K�� ������ ���� �Էµ� ������ �ݺ� 
		cout << "Input(K) >>";
		cin >> K;
	}
	
	// �� ���� ���� 
	cout << "Shell Sort : " << endl;
	shellsort(ary, arySize, K);
	
	// �迭�� ��� 
	PrintAry(ary, arySize);
	
	delete[] ary;

	return 0;
}
