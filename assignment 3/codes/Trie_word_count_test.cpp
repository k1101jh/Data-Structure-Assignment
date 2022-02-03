#include <iostream>
#include "Trie.cpp"
using namespace std;

void PrintTrie(Nptr T)
{
	for(int i = 0; i < NUM_ALPHABET; i++)
	{
		if(T->nodes[i] != NULL)
		{
			cout << i << " " << T->nodes[i]->val << endl;
			PrintTrie(T->nodes[i]);
		}
	}
	//cout << -1 << endl;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "Argument Error..." << endl;
		return 0;
	}
	
	Trie trie;
	// hash ������ �о ���� 
	trie.Open(argv[1]);
	Nptr temp = *(trie.root);
	cout << endl;
	//PrintTrie(temp);
	
	char input[20];
	while(true)
	{
		cout << "input (Exit : \"EXIT\")> ";
		cin >> input;
		// "EXIT"�� �Է����� ��� ���� 
		if(strcmp(input, "EXIT") == 0)
			break;
		
		// �Է��� �޾� hash Ž�� 
		Nptr temp = trie.Search(input);
		if(temp == NULL)
			cout << "Not found" << endl;
		else
			cout << temp->val << endl;
	}
	
	return 0;
}
