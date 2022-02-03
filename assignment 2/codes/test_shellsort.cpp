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
		PrintAry(ary, arySize);
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
		// 랜덤 배열을 만드는 함수
		// (랜덤 원소의 최대값, 배열의 크기)
		ary = MakeRandomArray(aryMaxNum, arySize);
		cout << "Random Array Generated!" << endl;
		PrintAry(ary, arySize);
	}
	
	int K = 0;
	while (K > 3 || K < 1)
	{	// K에 적절한 값이 입력될 때까지 반복 
		cout << "Input(K) >>";
		cin >> K;
	}
	
	// 셸 정렬 실행 
	cout << "Shell Sort : " << endl;
	shellsort(ary, arySize, K);
	
	// 배열을 출력 
	PrintAry(ary, arySize);
	
	delete[] ary;

	return 0;
}
