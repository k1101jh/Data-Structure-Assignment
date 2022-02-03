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
	// hash 파일을 읽어서 저장 
	hash.Open(argv[1]);
	
	char input[20];
	while(true)
	{
		cout << "input (Exit : \"EXIT\")> ";
		cin >> input;
		// "EXIT"를 입력했을 경우 종료 
		if(strcmp(input, "EXIT") == 0)
			break;
		
		// 입력을 받아 hash 탐색 
		Nptr temp = hash.Search(input);
		if(temp == NULL)
			cout << "Not found" << endl;
		else
			cout << temp->Data.count << endl;
	}
	
	return 0;
}
