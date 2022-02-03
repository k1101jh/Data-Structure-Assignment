#include <iostream>
#include "Hash.cpp"
using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "Argument Error..." << endl;
		return 0;
	}
	
	Hash hash;
	// hash ������ �о ���� 
	hash.Open(argv[1]);
	
	char input[20];
	while(true)
	{
		cout << "input (Exit : \"EXIT\")> ";
		cin >> input;
		// "EXIT"�� �Է����� ��� ���� 
		if(strcmp(input, "EXIT") == 0)
			break;
		
		// �Է��� �޾� hash Ž�� 
		Nptr temp = hash.Search(input);
		if(temp == NULL)
			cout << "Not found" << endl;
		else
			cout << temp->Data.count << endl;
	}
	
	return 0;
}
