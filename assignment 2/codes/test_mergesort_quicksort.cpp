#include <iostream>
#include <fstream>
#include "mergesort.cpp"
#include "quicksort.cpp"
#include "make_random_array.cpp"
#include "make_array.cpp"
using namespace std;

int main(int argc, char *argv[])
{
	int arySize;
	int aryMaxNum;
	int *ary1;
	int *ary2;
	
	if (argc == 2)
	{	// ���ڰ� �ϳ� �ԷµǾ��� ��� 
		ifstream fin;
		fin.open(argv[1]);
		if (!fin)
		{
			cout << "Can't open file" << endl;
			return 0;
		}
		ary1 = MakeAry(fin, arySize);
		fin.close();
		cout << "Ary : " << endl;
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
		
		ary1 = MakeRandomArray(aryMaxNum, arySize);
		cout << "Random Array Generated!" << endl;
	}
	ary2 = CopyAry(ary1, arySize);	
	
	PrintAry(ary1, arySize); 
	// �պ����� 
	cout << "Mergesort : " << endl;
	mergesort(ary1, 0, arySize - 1);
	PrintAry(ary1, arySize);
	// ������� 
	cout << "Quicksort : " << endl;
	quicksort(ary2, 0, arySize - 1);
	PrintAry(ary2, arySize);
	
	delete[] ary1;
	delete[] ary2;
	
	return 0;
}
