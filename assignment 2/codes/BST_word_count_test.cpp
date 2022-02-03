#include <iostream>
#include <fstream>
#include "treeRecord.h"
using namespace std;

// �迭�� ����ϴ� �Լ� 
void PrintAry(dataType *A, int arySize)
{
	for (int i = 0; i < arySize; i++)
	{
		cout << A[i].Key << " " << A[i].count << endl;
	}
	cout << endl;
}

// ������ �� ���� ����ϴ� �Լ� 
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

// ������ �о� �迭�� ����� �Լ� 
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

// ����Ž���� �����ϴ� �Լ� 
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

	// ���ڰ� ����� �Էµ��� �ʾ��� ��� 
	if (argc != 2)
	{
		cout << "Argument Error..." << endl;
		return 0;
	}
	// ���ڰ� ����� �Էµ� ���
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
		// "EXIT"�� �Է����� ��� ���� 
		if(strcmp(input, "EXIT") == 0)
			break;
		// ����Ž�� ���� 
		int count = BinarySearch(ary, 0, arySize, input);
		if(count == 0)
			cout << "Not found" << endl;
		else
			cout << count << endl;
	}
	
	// �迭 ��ȯ 
	delete [] ary;
	
	return 0;
}
