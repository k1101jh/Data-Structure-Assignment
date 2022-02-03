#include <iostream>
#include <fstream>
using namespace std;

int BinarySearch(int A[], int start, int end, int key)
{
	while(end >= start)								// 끝 위치가 시작 위치보다 클 경우 
	{												// 0을 리턴 
		int mid = (start + end) / 2; 
		if(A[mid] == key)							// 중간값과 찾으려는 값이 같을 경우  
			return mid + 1;							// 중간 위치 리턴 
		else if(A[mid] > key)						// 중간값보다 작을 경우 
			end = mid - 1;							// 끝 값을 중간 위치 - 1 로 설정 
		else										// 중간값보다 클 경우 
			start = mid + 1;						// 시작 값을 중간 위치 + 1 로 설정 
	}
	return 0;
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
	
	int arysize = 2;
	int *ary = new int[arysize];
	int count = 0;
	
	while(!fin.eof())
	{
		fin >> ary[count++];
		if(count >= arysize)						// 배열의 공간이 부족하다면 
		{											// 배열의 크기를 2배로 늘리기 
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
	
	int numToFind = 0;
	 
	cout << "찾으시려는 숫자를 입력해 주세요>> ";
	cin >> numToFind;
	
	int rank = BinarySearch(ary, 0, count - 1, numToFind);
	if(rank == 0)
		cout << "찾으시려는 숫자는 존재하지 않습니다." << endl;
	else 
		cout << numToFind << "는 " << rank << "번째에 위치해 있습니다." << endl;
}
