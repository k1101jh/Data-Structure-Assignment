#include <iostream>
#include <fstream>
using namespace std;

int KarySearch(int A[], int k, int start, int end, int key)
{
	int dividedNum = (end - start + 2) / k;				// k 개로 나눈 수 
	if(start > end)										// 값이 존재하지 않으면 
		return 0;										// 0 리턴 
	else
	{
		if(dividedNum == 0)								// 남은 값의 수가 k개보다 적을 경우 
		{
			int remainder = end - start + 1;		// 남은 값의 수 계산 
			for(int i = 0; i < remainder; i++)			// 순차적으로 비교 
			{
				if(A[start + i] == key)					// 값을 찾으면 
					return start + i + 1; 				// 값 리턴 
			}
			return 0;
		}
		else
		{
			int checkNum;								// 비교를 실행할 값의 위치 
			for(int i = 1; i < k; i++)
			{
				checkNum = (start - 1) + i * dividedNum;
				//cout << A[checkNum] << " "; 탐색 위치의 값 
				if (A[checkNum] == key)					// 비교값이 찾는 값일 경우 
					return checkNum + 1;				// 위치 리턴 
				else if(A[checkNum] > key)				// 비교값이 클 경우 
				{										// 재귀함수 호출 
					return KarySearch(A, k, checkNum - dividedNum + 1, checkNum - 1, key);
				}
			}										// 마지막 비교값은 배열의 end위치의 값 
			if(key > A[end])		// 배열의 마지막 값보다 큰 경우 
				return 0;			// 값을 찾을 수 없음 
			else
			{						// 재귀함수 호출 
				return KarySearch(A, k, checkNum + 1, end, key);
			}	
		}
	}
}

int main(int argc, char *argv[])
{	
	ifstream fin;
	fin.open(argv[1]); 
	if(!fin)
	{
		cout << "파일을 열 수 없습니다." << endl;
		return 0;
	}
	int arysize = 10;
	int *ary = new int[arysize];
	int count = 0;
	
	while(!fin.eof())
	{
		fin >> ary[count++];
		if(count >= arysize)
		{
			arysize *= 2;
			int *newAry = new int[arysize];
			for(int i = 0; i < arysize/2; i++)
			{
				newAry[i] = ary[i];
			}
			delete [] ary;
			ary = newAry;
		}

	}
	
	int numToFind = 0, k;
	 
	cout << "찾으시려는 숫자를 입력해 주세요>> ";
	cin >> numToFind;
	
	cout << "데이터를 몇 개의 파트로 나눌지 입력해 주세요 >> ";
	cin >> k;
	
	int rank = KarySearch(ary, k, 0, count - 1, numToFind);
	if(rank == 0)
		cout << "찾으시려는 숫자는 존재하지 않습니다." << endl;
	else 
		cout << numToFind << "는 " << rank << "번째에 위치해 있습니다." << endl;
}
