#include <iostream>
#include <fstream>
#include "BST.cpp"
using namespace std;

// 중위순회로 저장하는 함수 
void InOrderSave(ofstream& fout, Nptr T)
{
	if(T != NULL)
	{
		InOrderSave(fout, T->LChild);
		fout << T->Data.Key << " " << T->Data.count << endl;
		InOrderSave(fout, T->RChild);
	}
}

// 중위순회로 출력하는 함수 
void InOrderPrint(Nptr T)
{
	if(T != NULL)
	{
		InOrderPrint(T->LChild);
		cout << T->Data.Key << " " << T->Data.count << endl;
		InOrderPrint(T->RChild);
	}
}

// WordCount파일을 저장하는 함수 
void SaveWordCount(Nptr T, string fileName)
{
	ofstream fout(fileName);
	if (!fout) {
		cout << "Failed" << endl;
		return;
	}
	// Tree를 정렬하여 저장 
	InOrderSave(fout, T);
	fout.close();
	
	cout << "Saved!" << endl;
}

// 파일을 입력받아 Tree로 만드는 함수 
void MakeTree(ifstream& fin, Nptr &T)
{
	char item[20];
	
	fin >> item;
	while(!fin.eof())
	{
		Update(T, item);
		fin >> item;
	}
}

int main(int argc, char *argv[])
{
	Nptr tree = NULL;
	// 인자가 제대로 입력되지 않았을 경우 
	if (argc != 2)
	{
		cout << "Argument Error..." << endl;
		return 0;
	}
	// 인자가 제대로 입력된 경우 
	else
	{
		ifstream fin;
		fin.open(argv[1]);
		if (!fin)
		{
			cout << "Can't open file" << endl;
			return 0;
		}
		MakeTree(fin, tree);
		fin.close();
	}
	
	// 중위순회 출력 
	InOrderPrint(tree);
	
	// Tree 저장 
	SaveWordCount(tree, strcat(strtok(argv[1], "."), ".wordcount"));
	
	// Tree 공간 반환 
	while(tree != NULL)
	{
		Delete(tree, tree->Data.Key.c_str());
	}
	
	return 0;
}
