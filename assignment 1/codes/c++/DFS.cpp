#include <iostream>
#include <fstream>
#include "genericStackDL.cpp"
using namespace std;

int GetPairNum(ifstream& fin)				// ��� edge�� ���� ���ϴ� �Լ� 
{
	int c;
	int spaceNum = 0;							// ' '�� �� 
	int pairNum = 0;							// ¦�� �� 
	fin.seekg(0, ios::end);
	int fileSize = fin.tellg();					// ������ ũ�� 
	for(int i = 0; i < fileSize; i++)
	{
		fin.seekg(i, ios::beg);
		c = fin.get();
		if(c == '\n')							// �ٹٲ� �� 
		{
			pairNum += spaceNum;				// edge�� ���� ' '�� ���� ���� 
			spaceNum = 0;						// ' '�� �� 0���� �ʱ�ȭ 
		}
		else if(c == ' ')						// ' '�� ��� 
			spaceNum++;							// ' '�� �� ���� 
	}
	pairNum += spaceNum;
	return pairNum;								// edge�� �� ���� 
}

int GetNodeNum(int ary[][2], int arySize)		// ��� ����� ���� ���ϴ� �Լ� 
{
	int num = 0;
	bool exist1 = false;						// ���� ��� ���� ���� 
	bool exist2 = false;						// �� ��� ���� ���� 
	int item = 0;
	listClass<int> *nodeList = new listClass<int>();
	for(int i = 0; i < arySize; i++)			// �迭�� ũ�⸸ŭ �ݺ� 
	{
		for(int j = 1; j <= nodeList->Length(); j++)
		{
			if(exist1 == true && exist2 == true)
				break;
			nodeList->Retrieve(j, item);		// ����Ʈ�� �� �޾ƿ� 
			if(item == ary[i][0])				// ���� ��尡 �����ϸ� 
				exist1 = true;
			else if(item == ary[i][1])			// �� ��尡 �����ϸ� 
				exist2 = true;
		}
		if(exist1 == false)						// ���� ��尡 �����ϸ� 
		{
			nodeList->Insert(1, ary[i][0]);		// ����Ʈ�� ��� ���� 
			num++;								// ��� �� ���� 
		}
		if(exist2 == false)						// �� ��尡 �����ϸ� 
		{
			nodeList->Insert(1, ary[i][1]);		// ����Ʈ�� ��� ���� 
			num++;								// ��� �� ���� 
		}
		exist1 = exist2 = false;
	}
	delete nodeList;							// ����Ʈ ���� 
	return num;									// ��� �� ��ȯ 
}

void PrintAry(int ary[][2], int arySize)	// ��� edge�� ��� 
{
	for(int i = 0; i < arySize; i++)
	{
		cout << ary[i][0] << " " << ary[i][1] << endl;
	}
}

int (*MakeAry(ifstream& fin, int& size))[2]	// edge�� ary�� ����� �Լ� 
{
	int c;
	int prev_c;
	int start, end = 0;							// ���� ��� ��ȣ, �� ��� ��ȣ 
	int arynum = 0;
	int arySize = GetPairNum(fin);				// �迭�� ũ�� = edge�� �� 
	bool isFirst = true;
	
	int (*ary)[2];
	ary = new int[arySize][2];					// �迭 ���� 
	fin.seekg(0);
	c = fin.get();
	while(c != EOF) 
	{
		start = c - '0';						// ���� ��忡 �� ���� 
		prev_c = c;
		
		c = fin.get();
		while(c != EOF)
		{
			if(c >= '0' && c <= '9')			// ���� ���ڰ� ������ ��� 
			{
				if(prev_c >= '0' && prev_c <= '9')	// ���� ���ڵ� ���ڿ��� ��� 
				{
					if(isFirst)							// ���� ���� ��ġ�� ��� 
						start = 10*start + (c - '0');	// ���� ���� �ڸ��� ���� 
					else
						end = 10*end + (c - '0');		// �� ���� �ڸ��� ���� 
				}
				else if(prev_c == '\n')				// ���� ���ڰ� �ٹٲ� ������ ��� 
				{
					start = c - '0';					// ���� ���� ���� ���� 
					isFirst = true;						// ���� ���� ���� ���̶�� ���� 
				}
				else								// ���� ���ڰ� �ٹٲ� ���ڳ� ���ڰ� �ƴ� ��� 
				{
					end = c - '0';						// �� ���� ���� 
				}
				prev_c = c;							// ���� ���� ���� ������ ���� 
				c = fin.get();						// ���� �� �޾ƿ� 
			}
			else								// ���� ���ڰ� ���ڰ� �ƴ� ��� 
			{
				if((c == ' ' || c == '\n') && prev_c >= '0' && prev_c <= '9') 
				{									// ���� ���ڰ� ' ' �Ǵ� '\n' �̰� ���� ���ڰ� ������ ��� 
					if(isFirst)							// ���� ���� ��ġ�� ��� 
						isFirst = false;					// ���� ���� ��ġ�� �ƴ� 
					else								// ���� ���� ��ġ�� �ƴ� ��� 
					{
						ary[arynum][0] = start;			// �迭�� ���۰��� ���� ���� 
						ary[arynum][1] = end;
						arynum++;
						end = 0;
					}
					prev_c = c;
					c = fin.get();
				}
				else
				{		
					prev_c = c;
					c = fin.get();
				}
			}
		}
	}
	ary[arynum][0] = start;				// �迭�� ���۰��� ���� ���� 
	ary[arynum][1] = end;				// �迭�� ���۰��� ���� ���� 
	
	size = arySize;				// �迭 ũ�� ���� 
	return ary;					// �迭 ���� 
}

void DFS(int ary[][2], int arySize, int start, int end)
{
	stackClass<int> S;				// Ž���� ���� ���� 
	stackClass<int> route;			// ��Ʈ�� ���ϴ� ���� 
	stackClass<int> sequence;		// ������ ����� ������ ��� ���� 
	int nodeNum = GetNodeNum(ary, arySize);				// ��� ���� 
	bool visited[nodeNum];			// ��� ������ŭ �迭 ����  
	for(int i = 0; i < nodeNum; i++)
		visited[i] = false;
	
	S.Push(start);					// ���� ��� push 
	sequence.Push(start);
	while(!S.IsEmpty())				// ���ÿ� ���� �����ϴ� ���� 
	{
		int sItem = S.Pop();			// ������ ���� pop 
		route.Push(sItem);
		if(sItem == end)				// pop�� ���� ���� �������� ��� 
		{									// ��� ��� 
			stackClass<int> tempStack;		// ��Ʈ ������ ������Ű�� ���� ���� 
			int pathLength = 0;				// ���� ���� 
			while(!route.IsEmpty())
			{
				tempStack.Push(route.Pop());	// ��Ʈ ������ ������ ���� 
				pathLength++;
			}
			cout << "path length: " << pathLength << endl;	// ��� ���� ��� 
			while(!tempStack.IsEmpty())
				cout << tempStack.Pop() << " ";				// ��� ��� 
			cout << endl;
			return;
		}
		for(int i = 0; i < arySize; i++)	// �迭�� Ž�� 
		{
			if(ary[i][0] == sItem)			// �������� pop�� ���� ���� edge �˻� 
			{
				int des = ary[i][1];			// edge�� ������ ���� 
				if(visited[des - 1] == false)	// �������� �湮���� �ʾҾ��ٸ� 
				{
					visited[des - 1] = true;		// �湮������ �ٲ� 
					S.Push(des);					// ���ÿ� ������ push
					sequence.Push(des);
				}
			}
		}
		int a, b;
		while(((a = route.Pop()) == (b = sequence.Pop())) &&
		(!route.IsEmpty() && !sequence.IsEmpty()))	// route ���ð� sequence ������ ���� ���� ���� pop�Ѵ�. 
		{
			if(route.IsEmpty() || sequence.IsEmpty())
				break;
		}
		route.Push(a);
		sequence.Push(b);
	}
	cout << "Not Found" << endl;				// ������ ��� ��� ���� ��� 
}

int main(int argc, char *argv[])
{
	/// ���� ����  
	ifstream fin;
	fin.open(argv[1]); 
	if(!fin)
	{
		cout << "������ �� �� �����ϴ�." << endl;
		return 0;
	}
	
	int arySize;
	int (*ary)[2] = MakeAry(fin, arySize);
	fin.close();
	
	//PrintAry(ary, arySize);					// �迭 ��� 
	
	int start, end;
	while(true)
	{
		cout << "enter starting and ending vertices (Exit : 0 0)>> ";
		cin >> start >> end;
		if(start == 0 && end == 0)
			break;							// ���α׷� ���� 
		DFS(ary, arySize, start, end);		// DFS ��� 
	}
}
