#include <iostream>
#include <fstream>
#include <iomanip>
#include <sys/time.h>
#include <unistd.h>
#include <random>
#include <time.h>
#include "Hash.cpp"
using namespace std;

//////////////////////////////
// wordcount ���� �ҷ����� 
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

// BST
///////////////////////////////

double getdtime()
{
	struct timeval tv = { 0 };
	double dtime;

	gettimeofday(&tv, NULL);
	dtime = tv.tv_sec + (tv.tv_usec / 1000000.0);
	return dtime;
}

int main(int argc, char **argv)
{
	int arySize;
	dataType *ary;
	
	if (argc != 3)
	{
		cout << "Argument Error..." << endl;
		return 0;
	}
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
	
	Hash hash;
	hash.Open(argv[2]);
	
	srand((int)time(0));
	////////
	// Hash �ӵ� ���� 
	double oldtime = getdtime();
	string key;
	int N = 1000000;
	cout << "N : " << N << endl;

	for(int i = 0; i < N; i++)
	{
		int randIndex = rand() % arySize;
		key = ary[randIndex].Key;
		
		// �Է��� �޾� hash Ž�� 
		Nptr temp = hash.Search(key.c_str());
	}
	double elapsed_time = getdtime() - oldtime;
	
	cerr << "hash elapsed_time: " << elapsed_time << " sec" << endl;
	////////
	
	////////
	// ����Ž��Ʈ�� �ӵ� ���� 
	oldtime = getdtime();
	
	for(int i = 0; i < N; i++)
	{
		int randIndex = rand() % arySize;
		key = ary[randIndex].Key;
		
		int count = BinarySearch(ary, 0, arySize, key.c_str());
	}
	elapsed_time = getdtime() - oldtime;
	cerr << "binary elapsed_time: " << elapsed_time << " sec" << endl;
	////////
	
	delete[] ary;

	return 1;
}
