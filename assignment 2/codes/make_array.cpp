#include <fstream>

// 파일을 입력받아 배열을 생성하는 함수 
int *MakeAry(ifstream& fin, int& size)
{
	int arySize = 100;
	int *ary = new int[arySize];
	int item, index = 0;
	fin >> item;
	while(!fin.eof())
	{
		if(index >= arySize)
		{
			arySize *= 2;
			int* ary2 = new int[arySize];
			for(int i = 0; i < arySize/2; i++)
				ary2[i] = ary[i];
			delete[] ary;
			ary = ary2;
		}
		ary[index++] = item;
		fin >> item;
	}
	ary[index] = item;

	size = index;
	return ary;
}
