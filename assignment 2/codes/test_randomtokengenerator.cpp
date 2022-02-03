#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <random>
#include <time.h>
#include <string>
#define VAL_W 20
#define VAL_N 10000
using namespace std;

// 모든 토큰을 출력하는 함수 
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

// 토큰을 TXT로 저장하는 함수 
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

// 누적분포함수를 계산하는 함수 
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

// 누적분포함수를 받아 길이를 생성하는 함수 
int RandomLengthGenerator(double *CDF, int length_stat_size)
{
	// 0~100 사이의 난수 생성 
	double randV = (double)rand()/(double)RAND_MAX * 100;
	int i = 0;
	for (i = 0; i < length_stat_size; i++)
	{
		if (randV < CDF[i])
			break;
	}
	return i + 1;
}

// 무작위 알파벳을 생성하는 함수 
char RandomCharGenerator()
{
	int randV = rand() % ('z' - 'a' + 1);
	return randV + 'a';
}

// 무작위 토큰을 생성하는 함수 
char **RandomTokenGenerator(double *wordStatAry, int& arySize, int length_stat_size)
{
	srand((unsigned)time(NULL));
	int size = VAL_N;
	// 누적분포함수 
	double *CDF = CDFGenerator(wordStatAry, length_stat_size);
	char **ary = new char*[size];
	for (int i = 0; i < size; i++)
	{
		// 확률에 따른 길이 생성 
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

// 파일의 줄 수를 구하는 함수 
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

// 확률 분포 테이블을 읽어들이는 함수 
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
	// 랜덤 토큰 생성 
	char **token = RandomTokenGenerator(wordLengthStatAry, arySize, wordLengthStatArySize);
	SaveTokenTXT(token, arySize);
	
	delete[] wordLengthStatAry;
	for(int i = 0; i < VAL_N; i++)
		delete[] token[i];
	delete[] token;

	return 0;
}
