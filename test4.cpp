#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
//A holds the actual value and the B hold indexes
int partition(int A[],int B[], int start, int end){
	int i = start + 1;
	int piv = A[B[start]];
	for(int j = start +1 ; j <= end; j++){
		if(A[B[j]] < piv) {
			swap(B[i] , B[j]);
			i += 1;
		}
	}
	swap(B[start] , B[i - 1]);
	return i -1;
}

void quick_sort(int A[],int B[], int start, int end){
	if(start < end){
		int piv_pos = partition(A,B, start, end);
		quick_sort(A,B, start,  piv_pos -1);
		quick_sort(A,B, piv_pos + 1, end);
	}
}


int main(){
	srand(time(NULL));
	int a[10];
	int b[10];
	for(int i = 0; i < 10; i++){
		b[i] = i;
	}
	
	for(int i = 0; i <  10; i++){
		a[i] = rand()%100;
		cout<< a[i] << endl;
	}
	quick_sort(a,b,0, 9);
	cout<<endl;
	for(int i = 0; i < 10; i++){
		cout<< a[b[i]]<< endl;
	}
	return 0;
}
