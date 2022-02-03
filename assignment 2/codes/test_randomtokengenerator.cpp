#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <random>
#include <time.h>
#include <string>
#define VAL_W 20
#define VAL_N 10000
using namespace std;

// ��� ��ū�� ����ϴ� �Լ� 
void PrintToken(char **A, int arySize) 
{
	for (int i = 0; i < arySize; i++)
	{
		for(int j = 0; j < VAL_W; j++)
			cout << A[i][j];
		cout << endl;
	}
	cout << endl;
}

// ��ū�� TXT�� �����ϴ� �Լ� 
void SaveTokenTXT(char **A, int arySize)
{
	ofstream fout("tokens.txt");
	if (!fout) {
		cout << "Failed Save Tokens" << endl;
		return;
	}
	int i = 0;
	for (i = 0; i < arySize - 1; i++)
	{
		for (int j = 0; j < VAL_W; j++)
			fout << A[i][j];
		fout << endl;
	}
	for (int j = 0; j < VAL_W; j++)
		fout << A[i][j];
		
	fout.close();
	cout << "Tokens Saved!" << endl;
}

// ���������Լ��� ����ϴ� �Լ� 
double *CDFGenerator(double *wordStatAry, int length_stat_size)
{
	double *CDF = new double[length_stat_size];
	CDF[0] = wordStatAry[0];
	for (int i = 1; i < length_stat_size; i++)
	{
		CDF[i] = CDF[i - 1] + wordStatAry[i];
	}
	return CDF;
}

// ���������Լ��� �޾� ���̸� �����ϴ� �Լ� 
int RandomLengthGenerator(double *CDF, int length_stat_size)
{
	// 0~100 ������ ���� ���� 
	double randV = (double)rand()/(double)RAND_MAX * 100;
	int i = 0;
	for (i = 0; i < length_stat_size; i++)
	{
		if (randV < CDF[i])
			break;
	}
	return i + 1;
}

// ������ ���ĺ��� �����ϴ� �Լ� 
char RandomCharGenerator()
{
	int randV = rand() % ('z' - 'a' + 1);
	return randV + 'a';
}

// ������ ��ū�� �����ϴ� �Լ� 
char **RandomTokenGenerator(double *wordStatAry, int& arySize, int length_stat_size)
{
	srand((unsigned)time(NULL));
	int size = VAL_N;
	// ���������Լ� 
	double *CDF = CDFGenerator(wordStatAry, length_stat_size);
	char **ary = new char*[size];
	for (int i = 0; i < size; i++)
	{
		// Ȯ���� ���� ���� ���� 
		int length = RandomLengthGenerator(CDF, length_stat_size);
		ary[i] = new char[VAL_W];
		for(int j = 0; j < VAL_W; j++)
			ary[i][j] = '\0';
		for (int j = 0; j < length; j++)
			ary[i][j] = RandomCharGenerator();
	}
	arySize = size;
	delete []CDF;
	return ary;
}

// ������ �� ���� ���ϴ� �Լ� 
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

// Ȯ�� ���� ���̺��� �о���̴� �Լ� 
double *MakeWordLengthStatAry(ifstream& fin, int& size)
{
	string line;
	double element = 0;
	int arynum = 0;
	int arySize = GetLineNum(fin);
	double *ary	= new double[arySize];

	while (true)
	{
		getline(fin, line);
		if (fin.eof()) break;
		int index = line.find(" ");
		line = line.substr(index);
		element = atof((char*)line.c_str());
		ary[arynum++] = element;
	}
	int index = line.find(" ");
	line = line.substr(index);
	element = atof((char*)line.c_str());
	ary[arynum] = element;

	size = arySize;
	return ary;
}

int main(int argc, char *argv[])
{
	int wordLengthStatArySize;
	double *wordLengthStatAry;

	if (argc != 2)
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
		wordLengthStatAry = MakeWordLengthStatAry(fin, wordLengthStatArySize);
		fin.close();
	}

	int arySize = 0;
	// ���� ��ū ���� 
	char **token = RandomTokenGenerator(wordLengthStatAry, arySize, wordLengthStatArySize);
	SaveTokenTXT(token, arySize);
	
	delete[] wordLengthStatAry;
	for(int i = 0; i < VAL_N; i++)
		delete[] token[i];
	delete[] token;

	return 0;
}
