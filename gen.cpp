#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char** argv){
	srand(time(NULL));
	int point = 30;
	printf("o plane\n");
	for(int i = 0; i < point; i++){
		int a = rand()%100000;
		double k = (double)a/10000.0;
		int b = rand()%100000;
		double l = (double)b/10000.0;
		int c = rand()%100000;
		double m = (double)c/10000.0;
		printf("v %lf %lf %lf\n",k,l,0.0);
	}
	for(int i = 0; i < 20; i++){
		int a = rand()%point+ 1;
		int b = rand()%point + 1;
		printf("l %d %d\n",a, b);
	}
	return 0;
}
