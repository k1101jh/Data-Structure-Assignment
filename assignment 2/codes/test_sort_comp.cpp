#include <iostream>
#include <fstream>
#include <iomanip>
#include <sys/time.h>
#include <unistd.h>
#include "shellsort.cpp"
#include "shellsort_sedgewick.cpp"
#include "make_random_array.cpp"
#include "mergesort.cpp"
#include "quicksort.cpp"
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
	int *ary3;
	int *ary4;
	int arySize;
	
	int K = 3;
	for(int N = 1000; N <= 10000000; N *= 10)
	{
		// 나올 수 있는 값의 최대와 길이를 N으로 설정 
		arySize = N;
		ary1 = MakeRandomArray(N, arySize);
		ary2 = CopyAry(ary1, arySize);
		ary3 = CopyAry(ary1, arySize);
		ary4 = CopyAry(ary1, arySize);
		
		// Pratt
		double oldtime = getdtime();
	
		shellsort(ary1, arySize, K);
	
		double elapsed_time = getdtime() - oldtime;
		cout << "N=" << N << ", Shellsort-Pratt, K=" << K << ", ";
		cerr << "elapsed_time: " << elapsed_time << " sec" << endl;
		
		// Sedgewick
		oldtime = getdtime();
	
		shellsort_sedgewick(ary2, arySize);
	
		elapsed_time = getdtime() - oldtime;
		cout << "N=" << N << ", Shellsort-Sedgewick, ";
		cerr << "elapsed_time: " << elapsed_time << " sec" << endl;
		
		// Mergesort
		oldtime = getdtime();
	
		mergesort(ary3, 0, arySize - 1);
	
		elapsed_time = getdtime() - oldtime;
		cout << "N=" << N << ", Mergesort, ";
		cerr << "elapsed_time: " << elapsed_time << " sec" << endl;
		
		// Quicksort
		oldtime = getdtime();
	
		quicksort(ary4, 0, arySize - 1);
	
		elapsed_time = getdtime() - oldtime;
		cout << "N=" << N << ", Quicksort, ";
		cerr << "elapsed_time: " << elapsed_time << " sec" << endl;
		
		delete[] ary1;
		delete[] ary2;
		delete[] ary3;
		delete[] ary4;
	}
	return 1;
}
