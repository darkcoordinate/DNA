#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;
class fine{
public:
	int key;
	fine(){
		key = 0;
	}
	fine(int a){
		key =a;
	}
};

int main()
{
	srand(time(NULL));
	vector<fine> g(10);
	vector<int> k(10);
	for(int i = 0; i < 10; i++)
	{
		g[i].key = rand()% 50;
	}
	for(int i = 0; i < 10; i++){
		cout<<g[i].key<<endl;
	}
	return 0;
}
