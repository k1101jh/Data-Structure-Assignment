#include <iostream>
#include <fstream>
#include <iomanip>
#include <sys/time.h>
#include <unistd.h>
#include "shellsort.cpp"
#include "shellsort_sedgewick.cpp"
#include "make_random_array.cpp"
using namespace std;

double getdtime()
{
	struct timeval tv = { 0 };
	double dtime;

	gettimeofday(&tv, NULL);
	dtime = tv.tv_sec + (tv.tv_usec / 1000000.0);
	return dtime;
}

int main(int argc, char **argv) {
	int *ary1;
	int *ary2;
	int arySize;
	
	int K = 3;
	for(int N = 1000; N <= 1000000; N *= 10)
	{
		// 나올 수 있는 값의 최대와 길이를 N으로 설정 
		arySize = N;
		// 동일한 배열에 대해 정렬을 실행하기 위해
		// 배열을 깊은복사한다. 
		ary1 = MakeRandomArray(N, arySize);
		ary2 = CopyAry(ary1, arySize);
		
		// Pratt
		double oldtime = getdtime();
	
		shellsort(ary1, arySize, K);
	
		double elapsed_time = getdtime() - oldtime;
		cout << "N=" << N << ", Pratt, K=" << K << ", ";
		cerr << "elapsed_time: " << elapsed_time << " sec" << endl;
		
		// Sedgewick
		oldtime = getdtime();
	
		shellsort_sedgewick(ary2, arySize);
	
		elapsed_time = getdtime() - oldtime;
		cout << "N=" << N << ", Sedgewick, ";
		cerr << "elapsed_time: " << elapsed_time << " sec" << endl;
		
		delete[] ary1;
		delete[] ary2;
	}
	return 1;
}
