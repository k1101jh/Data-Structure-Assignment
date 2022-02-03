#include <iostream>
#include <fstream>
#include <iomanip>
#include <sys/timeb.h>
#include <unistd.h>

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
	double oldtime = getdtime();

	for (int i = 0; i < 1000; i++) {
		usleep(1000);
	}

	double elapsed_time = getdtime() - oldtime;
	cerr << "elapsed_time: " << elapsed_time << " sec" << endl;
	return 1;
}
