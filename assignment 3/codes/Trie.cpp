#include <iostream>
#include <string.h>
#include <fstream>
#include "Trie.h"
#define DEBUG FALSE;
using namespace std;

void Trie::Create()
{
	root = new Nptr;
	*root = CreateTrieNode();
	(*root)->val = 0;
	size = 0;
}

int Trie::Insert(const char *key, int val)
{
	Nptr temp = Search(key);
	if(temp == NULL)
	{
		temp = *root;
		for(int i = 0; i < strlen(key); i++)
		{
			if(temp->nodes[key[i] - 'a'] == NULL)
			{
				temp->nodes[key[i] - 'a'] = CreateTrieNode();
				temp->nodes[key[i] - 'a']->val = 0;
			}
			temp = temp->nodes[key[i] - 'a'];
		}

		temp->val = val;
		size++;
	}
	else
	{
		temp->val = val;
	}
}

Nptr Trie::Search(const char *key)
{
	Nptr temp = *root;

	for(int i = 0; i < strlen(key); i++)
	{
		if(temp == NULL)
			break;
		else
		{
			temp = temp->nodes[key[i] - 'a'];
		}
	}
	return temp;
}

void Trie::Delete(const char *key)
{
	Nptr temp = Search(key);
	
	if(temp == NULL)
		cout << "No Record with Such Key" << endl;
	else if(temp != NULL)
	{
		temp->val = 0;
		size--;
	}
}

void RecursiveSave(ofstream& fout, Nptr T)
{
	for(int i = 0; i < NUM_ALPHABET; i++)
	{
		if(T->nodes[i] != NULL)
		{
			fout << i << " " << T->nodes[i]->val << endl;
			RecursiveSave(fout, T->nodes[i]);
		}
	}
	fout << -1 << endl;
}

void Trie::Save(const char *filename)
{
	ofstream fout(filename);
	if (!fout) {
		cout << "Save failed..." << endl;
		return;
	}
	
	// table의 크기를 파일의 첫 줄에 저장 
	fout << size << ": size" << endl;
	Nptr temp = *root;
	
	RecursiveSave(fout, temp);
	fout.close();
	
	cout << "Saved!" << endl;
}

void RecursiveOpen(ifstream &fin, Nptr& T)
{
	int index = 0, val = 0;
	fin >> index;
	//cout << index << endl;
	if(index == -1)
		return;
	else
	{
		fin >> val;
		if(T->nodes[index] == NULL)
			T->nodes[index] = CreateTrieNode();
		T->nodes[index]->val = val;
		RecursiveOpen(fin, T->nodes[index]);
		RecursiveOpen(fin, T);
	}
}

void Trie::Open(const char *filename)
{
	ifstream fin;
	fin.open(filename);
	if(!fin)
	{
		cout << "Open failed..." << endl;
		return; 
	}

	char line[20];
	int index = 0;
	int val = 0;
	
	// size 구하기 
	fin.getline(line, 25);
	if(fin.eof()) return;
	
	Create();
	size = stoi(strtok(line, ":"));
	
	Nptr temp = *root;
	
	RecursiveOpen(fin, temp);
	
	fin.close();
}
