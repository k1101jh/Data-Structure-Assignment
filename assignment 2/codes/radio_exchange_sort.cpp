#include <iostream>
#include <fstream>
#define VAL_W 20
using namespace std;

void PrintToken(char **T, int TSize)
{
	for(int i = 0; i < TSize; i++)
	{
		for(int j = 0; j < VAL_W; j++)
		{
			cout << T[i][j];
		}
		cout << endl;
	}
}

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

	return elementNum;
}

char **MakeAryByToken(ifstream& fin, int& size)
{
	int c;
	int arynum = 0;
	int arySize = GetLineNum(fin);
	char **ary = new char*[arySize];
	
	fin.seekg(0);
	for(int i = 0; i < arySize; i++)
	{
		ary[i] = new char[VAL_W];
		fin >> ary[i];
	}

	size = arySize;
	return ary;
}

///////////////////////////////////////
/// QuickSort ���� ��Ʈ

// �迭�� ���Ҹ� ��ȯ�ϴ� �Լ�
void Swap(char **T, int item1, int item2)
{
	char temp;
	
	for(int i = 0; i < VAL_W; i++)
	{
		temp = T[item1][i];
		T[item1][i] = T[item2][i];
		T[item2][i] = temp;
	}
}

char* GetToken(char **T, int index)
{
	char *token = new char[VAL_W];
	for(int i = 0; i < VAL_W; i++)
	{
		token[i] = T[index][i];
	}
	return token;
}

void InsertToken(char **T, int index, char* token)
{
	for(int i = 0; i < VAL_W; i++)
	{
		T[index][i] = token[i];
	}
}

void PrintToken1(char **T, int index)
{
	for(int i = 0; i < VAL_W; i++)
		cout << T[index][i];
	cout << endl;
}

// �ǹ��� ���� �ǹ��� �������� ������ ���Ҹ� �����Ѵ�.
void Partition(char **T, int first, int last, int index, int &firstP, int &lastP)
{
	int low, high, pivotF;
	char p;
	// ������ ��Ҹ� �ǹ����� ����
	pivotF = last;
	p = T[last][index];
	//cout << endl << "pivot : " << p << endl << endl;
	low = first;		// �� ������
	high = last - 1;	// �ٿ� ������
	//cout << "low : " << low << " high : " << high << endl;
	while(low <= high)
	{
		while(p > T[low][index]) low++;
		while(high >= first && p < T[high][index]) high--;
		if(low <= high)
		{
			// �� ���Ҹ� ��ȯ
			Swap(T, low, high);
			// �� ���Ұ� ���� �� �߻��ϴ� ���ѷ����� ���� 
			if(T[low][index] == T[high][index])
			{
				if(p == T[low][index])
				{
					//Swap(T, low, last);
					char *token = GetToken(T, low);
					for(int i = low; i < last; i++)
						Swap(T, i, i + 1);
					InsertToken(T, last, token);
					pivotF--;
					high--;
					delete []token;
				}
				else
					low++;
			}
		}
	}
	// �� �����Ͱ� �ٿ� �����ͺ��� Ŀ����
	// �� �������� ���ҿ� �ǹ��� ��ȯ 
	//Swap(T, low, pivotF);
	firstP = low;
	//cout << "Token : " << endl;
	while(pivotF <= last)
	{
		Swap(T, low++, pivotF++);
		//PrintToken1(T, low - 1);
	}
	//cout << endl;
	lastP = low - 1;
}

// �� ������ �����ϴ� �Լ� 
void QuickSort_Token(char **T, int first, int last, int index)
{
	if(first < last)
	{
		int pivotFirstIndex, pivotLastIndex;
		Partition(T, first, last, index, pivotFirstIndex, pivotLastIndex);
		/*
		for(int i = first; i <= last; i++)
		{
			for(int j = 0; j < VAL_W; j++)
				cout << T[i][j];
			cout << endl;
		}
		*/
		if(pivotLastIndex - pivotFirstIndex > 0)
			QuickSort_Token(T, pivotFirstIndex, pivotLastIndex, index + 1);
		if(pivotFirstIndex - 1 - first > 0)
			QuickSort_Token(T, first, pivotFirstIndex - 1, index);
		if(last - pivotLastIndex - 1 > 0)
			QuickSort_Token(T, pivotLastIndex + 1, last, index);
	}
}

/// Quick Sort ���� ���� 
///////////////////////////////////////////

int main(int argc, char *argv[])
{
	int tokenSize;
	char **token;

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
		token = MakeAryByToken(fin, tokenSize);
		fin.close();
	}
	
	QuickSort_Token(token, 0, tokenSize - 1, 0);
	PrintToken(token, tokenSize);
	
	for(int i = 0; i < VAL_W; i++)
		delete[] token[i];
	delete[] token;

	return 0;
}
