#include <iostream>
#include <fstream>
#include "build_heap.cpp"
#include "heap_sort.cpp"
#include "make_random_array.cpp"
#include "make_array.cpp"
using namespace std;

// Heap을 완전 이진트리 모양으로 출력하는 함수 
void PrintHeap(int *ary, int arySize)
{
	int expr2 = 2;
	for(int i = 0; i < arySize; i++)
	{
		cout << ary[i] << " ";
		if((i + 1) == (expr2 - 1))
		{
			cout << endl;
			expr2 *= 2;
		}
	}
	cout << endl;
}

int main(int argc, char* argv[])
{
	int arySize;
	int aryMaxNum;
	int* ary;
	
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
	cout << endl;
	
	// 하향식 힙 구성 
	cout << "build_heap : " << endl; 
	build_heap(ary, arySize);
	PrintHeap(ary, arySize);
	cout << endl;
	// 힙 삭제함수 
	while(arySize > 0)
	{
		char answer;
		cout << "remove?(Y/N) >>";
		cin >> answer;
		if(answer == 'N' || answer == 'n')
			break;
		else if(answer == 'Y' || answer == 'y')
		{
			cout << "remove_heap : " << endl;
			arySize = remove_heap(ary, arySize);
			PrintHeap(ary, arySize);
			cout << endl;
		}
	}
	
	delete[] ary;
	
	return 0;
}
