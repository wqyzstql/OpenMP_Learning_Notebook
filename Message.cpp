#include<cstdio>
#include<iostream>
#include<omp.h>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

const int N = 1005;

string sq[N];
int head = 1, tail = 0;
int finish_sender = 0;
int threads_count = 8;

void Message() {
	int rank = omp_get_thread_num();
	if (rank % 2 == 0) { //sender
		string send = "This Message is Send by thread";
		send += to_string(rank);
		sq[++tail] = send;
#pragma omp critical
		finish_sender++;
	}
	else { //receiver
		while (finish_sender != threads_count / 2){
			while (head > tail && finish_sender != threads_count / 2);
			string rec;
#pragma omp critical
			rec = sq[head++];
#pragma omp critical
			cout << "Thread "<<rank<<" received Message: "<<rec << endl;		
		}

	}
	return;
}

int main() {
	omp_set_num_threads(threads_count);// i^1=0, sender, else receiver
#pragma omp parallel 
	Message();
	return 0;
}
