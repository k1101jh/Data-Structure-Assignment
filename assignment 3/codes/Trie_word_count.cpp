#include <iostream>
#include "Trie.cpp"
using namespace std;

bool IsAlphabetWord(char* const item)
{
	int i = 0;
	for(i = 0; i < 20; i++)
	{
		if(item[i] == '\0')
			break;
		if(item[i] < 'a' || item[i - 1] > 'z')
			return false;
	}
	return true;
}

void TokensToTrie(ifstream& fin, Trie& trie)
{
	trie.Create();
	
	char item[20];
	int val = 0;
	fin >> item;
	while(!fin.eof())
	{
		if(IsAlphabetWord(item))
		{
			val = 0;
			Nptr temp = trie.Search(item);
			if(temp != NULL)
				val = temp->val;
			trie.Insert(item, val + 1);
		}
		fin >> item;
	}
	fin.close();
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "Argument Error..." << endl;
		return 0;
	}
	else
	{
		ifstream fin;
		fin.open(argv[1]);
		if(!fin)
		{
			cout << "File Load Failed..." << endl;
			return 0; 
		}
		Trie trie;
		TokensToTrie(fin, trie);
		trie.Save(strcat(strtok(argv[1], "."), ".trie"));
	}
	

	return 0;	
}
