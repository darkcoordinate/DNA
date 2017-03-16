#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;

class pointer{
public:
	vector<double> k;
	pointer():k(2){
	}
	pointer(double a, double c): k(2){
		k[0] = a;
		k[1] = c;
	}

	void operator=(const pointer &p){
		this->k[0] = p.k[0];
		this->k[1] = p.k[1];
	}
};
class line {
public:
	vector<pointer> l;
	line():l(2){
	}
	line(pointer a, pointer b): l(2){
		l[0] = a;
		l[1] = b;
	}
	void operator=(const line& p){
		this->l[0] = p.l[0];
		this->l[1] = p.l[1];
	}
	double min_x(){
		if(l[0].k[0] < l[1].k[0]){
			return l[0].k[0];
		}
		else{
			return l[1].k[0];
		}
	}
	double max_x(){
		if(l[0].k[0] > l[1].k[0]){
			return l[0].k[0];
		}
		else{
			return l[1].k[0];
		}
	}
	double min_y(){
		if(l[0].k[1] < l[1].k[1]){
			return l[0].k[1];
		}
		else{
			return l[1].k[1];
		}
	}
	double max_y(){
		if(l[0].k[1] > l[1].k[1]){
			return l[0].k[1];
		}
		else{
			return l[1].k[1];
		}
	}
};


pointer* lineIntersection( line lin, line lin2){
	double k1 = (lin.l[0].k[0] - lin.l[1].k[0]);
	double k2 = (lin2.l[0].k[0] - lin2.l[1].k[0]);
	if( k1 == 0 || k2 == 0){
		double m1 = k1/(lin.l[0].k[1] - lin.l[1].k[1]);
		double m2 = k2/(lin2.l[0].k[1] - lin2.l[1].k[1]);
		double c1 = lin.l[0].k[0] - lin.l[0].k[1]*m1;
		double c2 = lin2.l[0].k[0] - lin2.l[0].k[1]*m2;
		if(m1 == m2)
			return NULL;
		double x = (c2 - c1)/(m1 - m2);

		double y =  m1*x + c1;
		return new pointer(y,x);
	}
	else{
		double m1 = (lin.l[0].k[1] - lin.l[1].k[1])/k1;
		double m2 = (lin2.l[0].k[1] - lin2.l[1].k[1])/k2;
		double c1 = lin.l[0].k[1] - lin.l[0].k[0]*m1;
		double c2 = lin2.l[0].k[1] - lin2.l[0].k[0]*m2;
		if(m1 == m2)
			return NULL;
		double x = (c2 - c1)/(m1 - m2);

		double y =  m1*x + c1;
		return new pointer(x,y);
	}
}

int main(){
	srand(time(NULL));
	double s[10];
	for( int  i = 0; i < 10; i++){
		s[i] = (double)(rand()%1000)/1000.0;
	}
	line lina = line(pointer(s[0], s[1]), pointer(s[2], s[3]));
	line linb = line(pointer(s[4], s[5]), pointer(s[6], s[7]));
	cout<<lina.l[0].k[0]<<" " <<lina.l[0].k[1]<<" "<<lina.l[1].k[0]<<" "<<lina.l[1].k[1]<<endl;
	cout<<linb.l[0].k[0]<<" "<<linb.l[0].k[1]<<" "<<linb.l[1].k[0]<<" "<<linb.l[1].k[1]<<endl;
	pointer* k = lineIntersection(lina, linb);
	cout<<k->k[0]<<" "<<k->k[1]<<endl;
	return 0;
}
