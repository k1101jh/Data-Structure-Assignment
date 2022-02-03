#include <iostream>
#include <fstream>
#include <iomanip>
#include <sys/time.h>
#include <unistd.h>
#include "shellsort.cpp"
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
	int *ary;
	int arySize;
	
	for(int N = 1000; N <= 1000000; N *= 10)
	{
		for(int K = 1; K <= 3; K++)
		{
			// ���� �� �ִ� ���� �ִ�� ���̸� N���� ���� 
			arySize = N;
			ary = MakeRandomArray(N, N); 
			
			// ���� ����
			double oldtime = getdtime();
		
			shellsort(ary, arySize, K);
			//���� ���� 
			double elapsed_time = getdtime() - oldtime;
			cout << "N=" << N << ", K=" << K << ", ";
			cerr << "elapsed_time: " << elapsed_time << " sec" << endl;
			delete[] ary;
		}
	}
	return 1;
}
