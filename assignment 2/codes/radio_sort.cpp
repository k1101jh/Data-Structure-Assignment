#include <iostream>
#include <fstream>
#define VAL_W 20
using namespace std;

// ��� ��ū�� ����ϴ� �Լ� 
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
	return elementNum;
}

// ��ū ������ �о�鿩 �迭�� ����� �Լ� 
char **MakeAryByToken(ifstream& fin, int& size)
{
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

// �� ���� 
void CountingSort_Token(char **T, int start, int end, int level)
{
	int CountSize = 'z' - 'a' + 2;
	int size = end - start + 1;
	int Count[CountSize] = {0};
	char **tempArray = new char*[size];
	
	for(int i = 0; i < size; i++)
	{
		// tempArray �� Token ����
		tempArray[i] = new char[VAL_W];
		for(int j = 0; j < VAL_W; j++)
			tempArray[i][j] = T[start + i][j];
		
		// �󵵸� ���� 
		char cmp_char = tempArray[i][level];
		if(cmp_char == '\0')
			Count[0]++;
		else
			Count[cmp_char - 'a' + 1]++;
	}

	// ���踦 ���� 
	Count[0]--;
	for(int i = 0; i < CountSize; i++)
	{
		Count[i + 1] += Count[i];
	}

	// ���� ���� 
	for(int i = size - 1; i >= 0; i--)
	{
		int pos;
		char cmp_char = tempArray[i][level];
		
		if(cmp_char == '\0')
			pos = start + Count[0]--;
		else
			pos = start + Count[cmp_char - 'a' + 1]--;

		for(int k = 0; k < VAL_W; k++)
			T[pos][k] = tempArray[i][k];
	}
}

// MSD ��� ���� 
void RadioSort(char **token, int start, int end, int index)
{
	// index��°�� ���� ���� 
	CountingSort_Token(token, start, end, index);
	char prev_char = token[start][index];
	int new_start = start;
	for(int i = start; i <= end; i++)
	{
		char current_char = token[i][index];
		
		// ������ ������ ���ڰ� ���� �׷쿡 ���� ���� 
		if(prev_char != current_char)
		{
			// ���� ���ڰ� �� �̻��̸鼭 NULL�� �ƴ� �� ���� ���� 
			if((i - 1) != new_start && prev_char != '\0')
				RadioSort(token, new_start, i - 1, index + 1);
			new_start = i;
			prev_char = current_char;
		}
	}

	// ���������� ���ĵ� ���ڿ� ���� ���� 
	if(new_start != end && prev_char != '\0')
		RadioSort(token, new_start, end, index + 1);
}

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
	
	// MSD ��� ���� ���� 
	RadioSort(token, 0, tokenSize - 1, 0);
	PrintToken(token, tokenSize);
	
	for(int i = 0; i < VAL_W; i++)
		delete[] token[i];
	delete[] token;

	return 0;
}
