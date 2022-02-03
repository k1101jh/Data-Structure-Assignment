#include <iostream>
#include <fstream>
#include "BST.cpp"
using namespace std;

// ������ȸ�� �����ϴ� �Լ� 
void InOrderSave(ofstream& fout, Nptr T)
{
	if(T != NULL)
	{
		InOrderSave(fout, T->LChild);
		fout << T->Data.Key << " " << T->Data.count << endl;
		InOrderSave(fout, T->RChild);
	}
}

// ������ȸ�� ����ϴ� �Լ� 
void InOrderPrint(Nptr T)
{
	if(T != NULL)
	{
		InOrderPrint(T->LChild);
		cout << T->Data.Key << " " << T->Data.count << endl;
		InOrderPrint(T->RChild);
	}
}

// WordCount������ �����ϴ� �Լ� 
void SaveWordCount(Nptr T, string fileName)
{
	ofstream fout(fileName);
	if (!fout) {
		cout << "Failed" << endl;
		return;
	}
	// Tree�� �����Ͽ� ���� 
	InOrderSave(fout, T);
	fout.close();
	
	cout << "Saved!" << endl;
}

// ������ �Է¹޾� Tree�� ����� �Լ� 
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
	// ���ڰ� ����� �Էµ��� �ʾ��� ��� 
	if (argc != 2)
	{
		cout << "Argument Error..." << endl;
		return 0;
	}
	// ���ڰ� ����� �Էµ� ��� 
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
	
	// ������ȸ ��� 
	InOrderPrint(tree);
	
	// Tree ���� 
	SaveWordCount(tree, strcat(strtok(argv[1], "."), ".wordcount"));
	
	// Tree ���� ��ȯ 
	while(tree != NULL)
	{
		Delete(tree, tree->Data.Key.c_str());
	}
	
	return 0;
}
