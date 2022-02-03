#include <iostream>
#include <fstream>
#include "treeRecord.h"
using namespace std;

// 배열을 출력하는 함수 
void PrintAry(dataType *A, int arySize)
{
	for (int i = 0; i < arySize; i++)
	{
		cout << A[i].Key << " " << A[i].count << endl;
	}
	cout << endl;
}

// 파일의 줄 수를 계산하는 함수 
int GetLineNum(ifstream& fin)
{
	int c;
	int elementNum = 0;
	fin.seekg(0, ios::end);
	int fileSize = fin.tellg();
	for (int i = 0; i < fileSize; i++)
	{
		fin.seekg(i, ios::beg);
		c = fin.get();
		if (c == '\n')
			elementNum++;
	}
	
	fin.seekg(0);
	return elementNum;
}

// 파일을 읽어 배열로 만드는 함수 
dataType *MakeAry(ifstream& fin, int& size)
{
	char line[25];
	int arySize = GetLineNum(fin);
	dataType *ary = new dataType[arySize];
	int aryIndex = 0;
	
	while(true)
	{
		fin.getline(line, 25);
		if(fin.eof()) break;
		ary[aryIndex].Key = strtok(line, " ");
		ary[aryIndex].count = stoi(strtok(NULL, " "));
		aryIndex++;
	}

	size = arySize;
	cout << "Loading is complete" << endl;

	return ary;
}

// 이진탐색을 수행하는 함수 
int BinarySearch(dataType *A, int start, int end, const char *key)
{
	while(end >= start)
	{
		int mid = (start + end) / 2; 
		if(A[mid].Key == key)
			return A[mid].count;
		else if(strcmp(A[mid].Key.c_str(), key) > 0)
			end = mid - 1;
		else
			start = mid + 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int arySize;
	dataType *ary;

	// 인자가 제대로 입력되지 않았을 경우 
	if (argc != 2)
	{
		cout << "Argument Error..." << endl;
		return 0;
	}
	// 인자가 제대로 입력된 경우
	else
	{
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
	
		
	char input[20];
	while(true)
	{
		cout << "input (Exit : \"EXIT\")> ";
		cin >> input;
		// "EXIT"를 입력했을 경우 종료 
		if(strcmp(input, "EXIT") == 0)
			break;
		// 이진탐색 실행 
		int count = BinarySearch(ary, 0, arySize, input);
		if(count == 0)
			cout << "Not found" << endl;
		else
			cout << count << endl;
	}
	
	// 배열 반환 
	delete [] ary;
	
	return 0;
}
