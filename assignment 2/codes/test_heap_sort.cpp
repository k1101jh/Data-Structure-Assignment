#include <iostream>
#include <fstream>
#include "build_heap.cpp"
#include "heap_sort.cpp"
#include "make_random_array.cpp"
#include "make_array.cpp"
using namespace std;

// Heap�� ���� ����Ʈ�� ������� ����ϴ� �Լ� 
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
	cout << endl;
	
	// ����� �� ���� 
	cout << "build_heap : " << endl; 
	build_heap(ary, arySize);
	PrintHeap(ary, arySize);
	cout << endl;
	// �� �����Լ� 
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
