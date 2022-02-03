#include <iostream>
#include <fstream>
#include <iomanip>
#include <sys/time.h>
#include <unistd.h>
#include <random>
#include <time.h>
#include "Hash.cpp"
#include "Trie.cpp"

bool IsAlphabetWord(string item)
{
	int i = 0;
	for(i = 0; i < 20; i++)
	{
		if(item[i] == '\0')
			break;
		if(item[i - 1] < 'a' || item[i - 1] > 'z')
			return false;
	}
	return true;
}

string *MakeAry(ifstream& fin, int& size)
{
	char line[25];
	fin.getline(line, 25);
	int arySize = stoi(strtok(line, " "));
	string *ary = new string[arySize];
	int aryIndex = 0;
	
	string item;
	if(fin.eof()) return ary;
	while(true)
	{
		fin >> item;
		
		ary[aryIndex] = item;
		aryIndex++;

		fin >> item;
		if(fin.eof()) break;
	}

	size = arySize;
	return ary;
}

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
	string *ary;
	
	if (argc != 3)
	{
		cout << "Argument Error..." << endl;
		return 0;
	}
	else
	{
		ifstream fin;
		fin.open(argv[2]);
		if (!fin)
		{
			cout << "Can't open file" << endl;
			return 0;
		}
		ary = MakeAry(fin, arySize);
		fin.close();
	}
	
	Trie trie;
	trie.Open(argv[1]);
	
	Hash hash;
	hash.Open(argv[2]);
	
	srand((int)time(0));
	
	string key;
	
	////////
	// Trie 속도 측정 
	double oldtime;
	double elapsed_time = 0;
	int N = 1000000;
	cout << "N : " << N << endl;
	
	for(int i = 0; i <= N; i++)
	{
		do
		{
			int randIndex = rand() % arySize;
			key = ary[randIndex];
		} while(!IsAlphabetWord(key));
		
		oldtime = getdtime();
		int count = trie.Search(key.c_str())->val;
		elapsed_time += getdtime() - oldtime;
	}
	cerr << "trie elapsed_time: " << elapsed_time << " sec" << endl;
	////////
	
	////////
	// Hash 속도 측정 
	oldtime = getdtime();
	elapsed_time = 0;

	for(int i = 0; i < N; i++)
	{
		int randIndex = rand() % arySize;
		key = ary[randIndex];
		
		// 입력을 받아 hash 탐색
		oldtime = getdtime();
		NptrH temp = hash.Search(key.c_str());
		elapsed_time += getdtime() - oldtime;
	}
	
	cerr << "hash elapsed_time: " << elapsed_time << " sec" << endl;
	////////
	
	delete[] ary;

	return 1;
}
