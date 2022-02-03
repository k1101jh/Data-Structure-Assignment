#include <iostream>
#include <fstream>
#include "genericStackDL.cpp"
using namespace std;

int GetPairNum(ifstream& fin)				// 모든 edge의 수를 구하는 함수 
{
	int c;
	int spaceNum = 0;							// ' '의 수 
	int pairNum = 0;							// 짝의 수 
	fin.seekg(0, ios::end);
	int fileSize = fin.tellg();					// 파일의 크기 
	for(int i = 0; i < fileSize; i++)
	{
		fin.seekg(i, ios::beg);
		c = fin.get();
		if(c == '\n')							// 줄바꿈 시 
		{
			pairNum += spaceNum;				// edge의 수에 ' '의 수를 더함 
			spaceNum = 0;						// ' '의 수 0으로 초기화 
		}
		else if(c == ' ')						// ' '일 경우 
			spaceNum++;							// ' '의 수 증가 
	}
	pairNum += spaceNum;
	return pairNum;								// edge의 수 리턴 
}

int GetNodeNum(int ary[][2], int arySize)		// 모든 노드의 수를 구하는 함수 
{
	int num = 0;
	bool exist1 = false;						// 시작 노드 존재 여부 
	bool exist2 = false;						// 끝 노드 존재 여부 
	int item = 0;
	listClass<int> *nodeList = new listClass<int>();
	for(int i = 0; i < arySize; i++)			// 배열의 크기만큼 반복 
	{
		for(int j = 1; j <= nodeList->Length(); j++)
		{
			if(exist1 == true && exist2 == true)
				break;
			nodeList->Retrieve(j, item);		// 리스트의 값 받아옴 
			if(item == ary[i][0])				// 시작 노드가 존재하면 
				exist1 = true;
			else if(item == ary[i][1])			// 끝 노드가 존재하면 
				exist2 = true;
		}
		if(exist1 == false)						// 시작 노드가 존재하면 
		{
			nodeList->Insert(1, ary[i][0]);		// 리스트에 노드 저장 
			num++;								// 노드 수 증가 
		}
		if(exist2 == false)						// 끝 노드가 존재하면 
		{
			nodeList->Insert(1, ary[i][1]);		// 리스트에 노드 저장 
			num++;								// 노드 수 증가 
		}
		exist1 = exist2 = false;
	}
	delete nodeList;							// 리스트 제거 
	return num;									// 노드 수 반환 
}

void PrintAry(int ary[][2], int arySize)	// 모든 edge를 출력 
{
	for(int i = 0; i < arySize; i++)
	{
		cout << ary[i][0] << " " << ary[i][1] << endl;
	}
}

int (*MakeAry(ifstream& fin, int& size))[2]	// edge를 ary로 만드는 함수 
{
	int c;
	int prev_c;
	int start, end = 0;							// 시작 노드 번호, 끝 노드 번호 
	int arynum = 0;
	int arySize = GetPairNum(fin);				// 배열의 크기 = edge의 수 
	bool isFirst = true;
	
	int (*ary)[2];
	ary = new int[arySize][2];					// 배열 생성 
	fin.seekg(0);
	c = fin.get();
	while(c != EOF) 
	{
		start = c - '0';						// 시작 노드에 값 저장 
		prev_c = c;
		
		c = fin.get();
		while(c != EOF)
		{
			if(c >= '0' && c <= '9')			// 현재 문자가 숫자일 경우 
			{
				if(prev_c >= '0' && prev_c <= '9')	// 이전 문자도 숫자였을 경우 
				{
					if(isFirst)							// 시작 값의 위치일 경우 
						start = 10*start + (c - '0');	// 시작 값의 자릿수 증가 
					else
						end = 10*end + (c - '0');		// 끝 값의 자릿수 증가 
				}
				else if(prev_c == '\n')				// 이전 문자가 줄바꿈 문자일 경우 
				{
					start = c - '0';					// 시작 값에 숫자 저장 
					isFirst = true;						// 현재 값은 시작 값이라고 설정 
				}
				else								// 이전 문자가 줄바꿈 문자나 숫자가 아닐 경우 
				{
					end = c - '0';						// 끝 값에 저장 
				}
				prev_c = c;							// 이전 값을 현재 값으로 저장 
				c = fin.get();						// 다음 값 받아옴 
			}
			else								// 현재 문자가 숫자가 아닐 경우 
			{
				if((c == ' ' || c == '\n') && prev_c >= '0' && prev_c <= '9') 
				{									// 현재 문자가 ' ' 또는 '\n' 이고 이전 문자가 숫자일 경우 
					if(isFirst)							// 시작 값의 위치일 경우 
						isFirst = false;					// 시작 값의 위치가 아님 
					else								// 시작 값의 위치가 아닐 경우 
					{
						ary[arynum][0] = start;			// 배열에 시작값과 끝값 저장 
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
	ary[arynum][0] = start;				// 배열에 시작값과 끝값 저장 
	ary[arynum][1] = end;				// 배열에 시작값과 끝값 저장 
	
	size = arySize;				// 배열 크기 리턴 
	return ary;					// 배열 리턴 
}

void DFS(int ary[][2], int arySize, int start, int end)
{
	stackClass<int> S;				// 탐색을 위한 스택 
	stackClass<int> route;			// 루트를 구하는 스택 
	stackClass<int> sequence;		// 지나는 노드의 순서를 담는 스택 
	int nodeNum = GetNodeNum(ary, arySize);				// 노드 개수 
	bool visited[nodeNum];			// 노드 개수만큼 배열 선언  
	for(int i = 0; i < nodeNum; i++)
		visited[i] = false;
	
	S.Push(start);					// 시작 노드 push 
	sequence.Push(start);
	while(!S.IsEmpty())				// 스택에 값이 존재하는 동안 
	{
		int sItem = S.Pop();			// 스택의 값을 pop 
		route.Push(sItem);
		if(sItem == end)				// pop한 값이 최종 목적지일 경우 
		{									// 결과 출력 
			stackClass<int> tempStack;		// 루트 스택을 반전시키기 위한 스택 
			int pathLength = 0;				// 스택 길이 
			while(!route.IsEmpty())
			{
				tempStack.Push(route.Pop());	// 루트 스택의 내용을 반전 
				pathLength++;
			}
			cout << "path length: " << pathLength << endl;	// 경로 길이 출력 
			while(!tempStack.IsEmpty())
				cout << tempStack.Pop() << " ";				// 경로 출력 
			cout << endl;
			return;
		}
		for(int i = 0; i < arySize; i++)	// 배열을 탐색 
		{
			if(ary[i][0] == sItem)			// 시작점이 pop한 값과 같은 edge 검색 
			{
				int des = ary[i][1];			// edge의 목적지 저장 
				if(visited[des - 1] == false)	// 목적지를 방문하지 않았었다면 
				{
					visited[des - 1] = true;		// 방문함으로 바꿈 
					S.Push(des);					// 스택에 목적지 push
					sequence.Push(des);
				}
			}
		}
		int a, b;
		while(((a = route.Pop()) == (b = sequence.Pop())) &&
		(!route.IsEmpty() && !sequence.IsEmpty()))	// route 스택과 sequence 스택의 값이 같을 동안 pop한다. 
		{
			if(route.IsEmpty() || sequence.IsEmpty())
				break;
		}
		route.Push(a);
		sequence.Push(b);
	}
	cout << "Not Found" << endl;				// 스택이 비면 결과 없음 출력 
}

int main(int argc, char *argv[])
{
	/// 파일 열기  
	ifstream fin;
	fin.open(argv[1]); 
	if(!fin)
	{
		cout << "파일을 열 수 없습니다." << endl;
		return 0;
	}
	
	int arySize;
	int (*ary)[2] = MakeAry(fin, arySize);
	fin.close();
	
	//PrintAry(ary, arySize);					// 배열 출력 
	
	int start, end;
	while(true)
	{
		cout << "enter starting and ending vertices (Exit : 0 0)>> ";
		cin >> start >> end;
		if(start == 0 && end == 0)
			break;							// 프로그램 종료 
		DFS(ary, arySize, start, end);		// DFS 계산 
	}
}
