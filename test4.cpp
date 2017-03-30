#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <exception>
#include <string>

#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

using namespace std;
long MAX_LIN = 0;
long MAX_PNT = 0;
class line;
class pointer{
public:
	vector<double> k;
	vector<line*> parent;
	pointer():k(2){
	}
	pointer(double a, double c): k(2){
		k[0] = a;
		k[1] = c;
	}

	void operator=(const pointer &p){
		this->k[0] = p.k[0];
		this->k[1] = p.k[1];
		this->parent = p.parent;
	}
};
class line {
public:
	vector<pointer*> l;
	vector<pointer*> IntersectionPoints;
	line():l(2), IntersectionPoints(0){

	}
	line(pointer* a, pointer* b): l(2), IntersectionPoints(0){
		l[0] = a;
		l[1] = b;
	}
	void operator=(const line& p){
		this->l[0] = p.l[0];
		this->l[1] = p.l[1];
	}
	double min_x(){
		if(l[0]->k[0] < l[1]->k[0]){
			return l[0]->k[0];
		}
		else{
			return l[1]->k[0];
		}
	}
	double max_x(){
		if(l[0]->k[0] > l[1]->k[0]){
			return l[0]->k[0];
		}
		else{
			return l[1]->k[0];
		}
	}
	double min_y(){
		if(l[0]->k[1] < l[1]->k[1]){
			return l[0]->k[1];
		}
		else{
			return l[1]->k[1];
		}
	}
	double max_y(){
		if(l[0]->k[1] > l[1]->k[1]){
			return l[0]->k[1];
		}
		else{
			return l[1]->k[1];
		}
	}
};

// An AVL tree node
class Node{
	line*  nd;
	line* next;
	line* prev;
	Node(){
		nd = NULL;
		next = NULL;
		prev = NULL;
	}
	Node(line* a, line* b, line* c){
		nd = a;
		next = b;
		prev = c;
	}
};

double max( double a, double b){
	if(a > b){
		return a;
	}
	else{
		return b;
	}
}


pointer* line_intersection_with(line lin, double n){
	//cout<<n<<" "<<lin.l[0].k[0]<<" "<<lin.l[0].k[1]<<" "<<lin.l[1].k[0]<<" "<<lin.l[1].k[1]<<endl;
	if((n >= min(lin.l[0]->k[0], lin.l[1]->k[0]) ) && (n <= max(lin.l[0]->k[0], lin.l[1]->k[0]))) {
		double k= (n-lin.l[0]->k[0])/(lin.l[1]->k[0] - lin.l[0]->k[0]);
		//cout<<k<<" "<<"file\n";
		if((k <= 1)&&(k >= 0)){
			return new pointer(n,lin.l[0]->k[1]+ (lin.l[1]->k[1] - lin.l[0]->k[1])*k);
		}
		else{
			throw exception();
		}
	}
	else {
		throw exception();
	}
}


pointer* lineIntersection( line lin, line lin2){
	double k1 = (lin.l[0]->k[0] - lin.l[1]->k[0]);
	double k2 = (lin2.l[0]->k[0] - lin2.l[1]->k[0]);
	if( k1 == 0 || k2 == 0){
		double m1 = k1/(lin.l[0]->k[1] - lin.l[1]->k[1]);
		double m2 = k2/(lin2.l[0]->k[1] - lin2.l[1]->k[1]);
		double c1 = lin.l[0]->k[0] - lin.l[0]->k[1]*m1;
		double c2 = lin2.l[0]->k[0] - lin2.l[0]->k[1]*m2;
		if(m1 == m2)
			return NULL;
		double x = (c2 - c1)/(m1 - m2);

		double y =  m1*x + c1;
		return new pointer(y,x);
	}
	else{
		double m1 = (lin.l[0]->k[1] - lin.l[1]->k[1])/k1;
		double m2 = (lin2.l[0]->k[1] - lin2.l[1]->k[1])/k2;
		double c1 = lin.l[0]->k[1] - lin.l[0]->k[0]*m1;
		double c2 = lin2.l[0]->k[1] - lin2.l[0]->k[0]*m2;
		if(m1 == m2)
			return NULL;
		double x = (c2 - c1)/(m1 - m2);

		double y =  m1*x + c1;
		return new pointer(x,y);
	}
}




int partition_line(vector<line*> &A, vector<int> &B, int start, int end){

	int i = start +1;
	line* piv = A[B[start]];
	for(int j =  start + 1; j <= end; j++){
		if(A[B[j]]->min_x() < piv->min_x()){
			swap(B[i], B[j]);
			//cout<<j<<endl;
			i+= 1;
		}
	}
	swap(B[start] , B[i -1]);
	return i -1;
}

void quick_sort_line(vector<line*> &A, vector<int> &B, int start, int end){
	if(start < end){
		int piv_pos = partition_line(A,B,start, end);
		quick_sort_line(A,B,start,piv_pos - 1);
		quick_sort_line(A,B,piv_pos + 1, end);
	}
}

int partition_line_for_ymin(vector<line*> &A, vector<int> &B,vector<int> &C,vector<int> &D, int start, int end){
	int i = start +1;
	line* piv = A[B[C[D[start]]]];
	for(int j =  start + 1; j <= end; j++){
		if(A[B[C[D[j]]]]->min_y() < piv->min_y()){
		swap(D[i], D[j]);
			//cout<<j<<endl;
			i+= 1;
		}
	}
	swap(D[start] , D[i -1]);
	return i -1;
}

void quick_sort_line_ymin_if_x_sorted(vector<line*> &A, vector<int> &B,vector<int> &C,vector<int> &D, int start, int end){
	if(start < end){
		int piv_pos = partition_line_for_ymin(A,B,C,D,start, end);
		quick_sort_line_ymin_if_x_sorted(A,B,C,D,start,piv_pos - 1);
		quick_sort_line_ymin_if_x_sorted(A,B,C,D,piv_pos + 1, end);
	}
}


int partition_line_for_ymax(vector<line*> &A, vector<int> &B,vector<int> &C, int start, int end){

	int i = start +1;
	line* piv = A[B[C[start]]];
	for(int j =  start + 1; j <= end; j++){
		if(A[B[C[j]]]->max_y() < piv->max_y()){
			swap(C[i], C[j]);
			//cout<<j<<endl;
			i+= 1;
		}
	}
	swap(C[start] , C[i -1]);
	return i -1;
}

void quick_sort_line_ymax_if_x_sorted(vector<line*> &A, vector<int> &B,vector<int> &C, int start, int end){
	if(start < end){
		int piv_pos = partition_line_for_ymax(A,B,C,start, end);
		quick_sort_line_ymax_if_x_sorted(A,B,C,start,piv_pos - 1);
		quick_sort_line_ymax_if_x_sorted(A,B,C,piv_pos + 1, end);
	}
}


int partition_lineS(vector<line*> &A, int start, int end){

	int i = start +1;
	line* piv = A[start];
	for(int j =  start + 1; j <= end; j++){
		if(A[j]->min_x() < piv->min_x()){
			swap(A[i], A[j]);
			//cout<<j<<endl;
			i+= 1;
		}
	}
	swap(A[start] , A[i -1]);
	return i -1;
}

void quick_sort_lineS(vector<line*> &A,int start, int end){
	if(start < end){
		int piv_pos = partition_lineS(A,start, end);
		quick_sort_lineS(A,start,piv_pos - 1);
		quick_sort_lineS(A,piv_pos + 1, end);
	}
}

int partition_lineSminy(vector<line*> &A, int start, int end){

	int i = start +1;
	line* piv = A[start];
	for(int j =  start + 1; j <= end; j++){
		if(A[j]->min_y() < piv->min_y()){
			swap(A[i], A[j]);
			//cout<<j<<endl;
			i+= 1;
		}
	}
	swap(A[start] , A[i -1]);
	return i -1;
}

void quick_sort_lineSminy(vector<line*> &A,int start, int end){
	if(start < end){
		int piv_pos = partition_lineSminy(A,start, end);
		quick_sort_lineSminy(A,start,piv_pos - 1);
		quick_sort_lineSminy(A,piv_pos + 1, end);
	}
}

int partition_lineSmaxy(vector<line*> &A, int start, int end){

	int i = start +1;
	line* piv = A[start];
	for(int j =  start + 1; j <= end; j++){
		if(A[j]->max_y() < piv->max_y()){
			swap(A[i], A[j]);
			//cout<<j<<endl;
			i+= 1;
		}
	}
	swap(A[start] , A[i -1]);
	return i -1;
}

void quick_sort_lineSmaxy(vector<line*> &A,int start, int end){
	if(start < end){
		int piv_pos = partition_lineSmaxy(A,start, end);
		quick_sort_lineSmaxy(A,start,piv_pos - 1);
		quick_sort_lineSmaxy(A,piv_pos + 1, end);
	}
}

void read(char* argv, vector<pointer*> &Points, vector<line*> &lineset){
	ifstream file(argv);
	string line2;
	int pointCounter = 0, linesetCounter = 0;
	for(int i = 0; i < 1000; i++){
		if(!getline(file,line2)){
			break;
		}
		const char* s = line2.c_str();
		double k, m, n;
		if(s == NULL){
			break;
		}
		if(s[0] == '#'){};
		if(s[0] == 'o'){};
		if(s[0] == 'v'){
			sscanf(s+ 1,"%lf %lf %lf",&m,&n,&k);
			Points[pointCounter] = new pointer(m,n);
			pointCounter++;
		}
		if(s[0] == 'l'){
			int a, b;
			sscanf(s+ 1,"%d %d",&a,&b);
			line* li1 = new line((Points[a - 1]), (Points[b -1 ]));
			Points[a-1]->parent.insert(Points[a-1]->parent.end() ,li1);
			Points[b-1]->parent.insert(Points[b-1]->parent.end() ,li1);
			lineset[linesetCounter] = li1;
			linesetCounter++;
		}
		//printf("%d %s\n",i, s);
	}
	if(Points.size()> pointCounter){
		Points.erase(Points.begin() + pointCounter, Points.end());
	}
	if( lineset.size() > linesetCounter){
		lineset.erase(lineset.begin() + linesetCounter, lineset.end());
	}
}

int binarySearch_min_x(vector<line*> a,int l,int h, double key)
{
	//string fl ="binarySearch_min_x : ";
	//cout<<fl<<l<<endl;
	while(l<=h)
	{
		//cout<<fl<<l<<" "<<h<<endl;
		if(key <= a[l]->min_x()){
			break;
		}
		if(key >= a[a.size() - 1]->min_x()){
			return h;
		}
		int m = (h + l)/2;
		//cout<<key<<" "<<a[m]->min_x()<<" "<<a[m + 1]->min_x()<<" ";
		if((key >= a[m]->min_x())&&(key < a[m + 1]->min_x())){
			return m;
		}
		else if((key <= a[m]->min_x())&&(key > a[m -1]->min_x())) {
			return m ;
		}
		else if(key >= a[m + 1]->min_x() ) {
			l = m;
		}
		else {
			h = m;
		}
	}
	return -1;                //key not found
 }

int binarySearch_min_y(vector<line*> a,int l,int h,double key)
{
	//string fl ="binarySearch_min_x : ";
	//cout<<fl<<l<<endl;
	while(l<=h)
	{
		//cout<<fl<<l<<" "<<h<<endl;
		if(key <= a[l]->min_y()){
			break;
		}
		if(key >= a[a.size() - 1]->min_y()){
			return h;
		}
		int m = (h + l)/2;
		if((key >= a[m]->min_y())&&(key < a[m + 1]->min_y())){
			return m;
		}
		else if((key <= a[m]->min_y())&&(key > a[m -1]->min_y())) {
			return m ;
		}
		else if(key >= a[m + 1]->min_y() ) {
			l = m;
		}
		else {
			h = m;
		}
	}
	return -1;                //key not found
 }

int binarySearch_max_y(vector<line*> a,int l,int h,double key)
{
	//string fl ="binarySearch_min_x : ";
	//cout<<fl<<l<<endl;
	while(l<=h)
	{
		//cout<<fl<<l<<" "<<h<<endl;
		if(key <= a[l]->max_y()){
			break;
		}
		if(key >= a[a.size() - 1]->max_y()){
			return h;
		}
		int m = (h + l)/2;
		if((key >= a[m]->max_y())&&(key < a[m + 1]->max_y())){
			return m;
		}
		else if((key <= a[m]->max_y())&&(key > a[m -1]->max_y())) {
			return m ;
		}
		else if(key >= a[m + 1]->max_y() ) {
			l = m;
		}
		else {
			h = m;
		}
	}
	return -1;                //key not found
 }

int main(int argc, char**argv){
	vector<pointer*> Points(1000);
	vector<line*> lineset(1000);
	read(argv[1],Points, lineset);
	//cout<<Points.size()<<" "<<lineset.size()<<endl;
	vector<line*> line2 = lineset;
	ofstream filej;
	filej.open("shape.fl");
	quick_sort_lineS(line2,0,line2.size() - 1);
	filej<<line2.size()<<endl;
	/*for(int i = 0; i < Points.size(); i++){
		for(int j = 0; j < Points[i]->parent.size(); j++){
			cout<<Points[i]->parent[j]<<" ";
		}
		cout<<endl;
	}*/
	for(int i = 0; i < line2.size();i++){
		cout<<line2[i]->min_x()<<" "<<line2[i]->max_x()<<" "<<line2[i]->min_y()<<" "<<line2[i]->max_y()<<endl;
		filej <<line2[i]->l[0]->k[0]<<" "<<line2[i]->l[0]->k[1] <<" "<<line2[i]->l[1]->k[0] <<" "<<line2[i]->l[1]->k[1] <<endl;
	}
	/* we will link the lines which are connected to each other
	 * through this we will make arc for the connections
	 */
	/*Node* head = new Node();
	int linked_point = 0;
	while(linked_point < line2.size()){
		if(linked_point == 0){
			line* current = line2[0];

			line* pointN =
		}
	}
*/



	//filej<<endl<<endl;
	//cout<<endl<<"File arranged\n";
	for(int i= 0; i < line2.size(); i++){
		ofstream filei;
		filei <<line2[i]->l[0]->k[0]<<" "<<line2[i]->l[0]->k[1] <<" "<<line2[i]->l[1]->k[0] <<" "<<line2[i]->l[1]->k[1] <<endl;

		filei.open("line" + std::to_string(i) + ".fl");
		int me = line2.size();
		double ko = line2[i]->max_x();
		int j = binarySearch_min_x(line2,i,me - 1 , ko);
		cout<<"first binary search "<<j<<" "<<i<<endl;
		if( j >= 0){
			vector<line*>::const_iterator first = line2.begin() + i+1;
			vector<line*>::const_iterator last = line2.begin() + j+1;
			vector<line*> line3(first, last);
			cout<<"list from fist search\n";
			for(int in = 0; in < line3.size(); in++){
				cout<<line3[in]->min_x()<<" "<<line3[in]->max_x()<<endl;
			}
			quick_sort_lineSminy(line3,0, line3.size() - 1);

			for(int in = 0; in < line3.size() ; in++){
				cout<<KRED<<line3[in]->min_x()<<" "<<KGRN<<line3[in]->max_x()<<" "<<KBLU<<line3[in]->min_y()<<" "<<KMAG<<line3[in]->max_y()<<RST<<endl;
			}
			int fi = binarySearch_min_y(line3,0,line3.size() - 1, line2[i]->max_y());
			cout<<"for"<<fi<<endl;
			if(fi >= 0){
				cout<<i<<" "<<j<<" "<<fi<<" "<<line3[fi]->min_y()<<" "<<line3[fi]->max_y()<<" ";
				/*if( fi < line3.size() - 1 ){
					cout<<line3[fi]->min_y();
			
			quick_sort_lineSminy(line3,0, line3.size() - 1);
			filei<<line3.size()<<endl;
	}*/
				cout<<"\nafter y bunary search\n";
				for(int fl1 = 0; fl1 < line3.size(); fl1++){
					cout<<KRED<<line3[fl1]->min_x()<<" "<<KGRN<<line3[fl1]->max_x()<<" "<<KBLU<<line3[fl1]->min_y()<<" "<<KMAG<<line3[fl1]->max_y()<<RST<<endl;
					filei <<line3[fl1]->l[0]->k[0]<<" "<<line3[fl1]->l[0]->k[1]<<" "<<line3[fl1]->l[1]->k[0]<<" "<<line3[fl1]->l[1]->k[1]<<endl;
				}
				//cout<<endl<<"| ";
				first = line3.begin();
				last = line3.begin() + fi+1;
				vector<line*> line4(first, last);
				cout<<"-------------\n Printing from line4\n";
				for(int in = 0; in < line4.size() ; in++){
					cout<<KRED<<line4[in]->min_x()<<" "<<KGRN<<line4[in]->max_x()<<" "<<KBLU<<line4[in]->min_y()<<" "<<KMAG<<line4[in]->max_y()<<RST<<endl;
				}
				//cout<<line4.size()<<" ";
				filei<<line4.size()<<endl;
				quick_sort_lineSmaxy(line4, 0, line4.size() -1);
				//for(int lik = 0; lik < line4.size(); lik++){
				//	cout<<line4[lik]->max_y()<<" ";
				///}
				//cout<<"|"<<line2[i]->min_y()<<"::| ";
				int tfi = binarySearch_max_y(line4, 0, line4.size() - 1, line2[i]->min_y());
				cout<<"tfi value "<<tfi<<endl;
				if(tfi >= -1){
					cout<<"from here "<<tfi<<" "<<line4.size() - 1<<endl;
					int k = line4.size() - 1;
					if( tfi > k){
						cout<<"Yahe\n";
					}
					if(tfi < k){
						cout<<"fuck you";
						cout<<line4.size() - tfi<<endl;
						for(int fik  = tfi + 1; fik < line4.size(); fik++){
							//cout<<"file "<<line4[fik]->max_y()<<" "<<line4[fik]->min_y()<<endl;
							filei <<line4[fik]->l[0]->k[0]<<" "<<line4[fik]->l[0]->k[1]<<" "<<line4[fik]->l[1]->k[0]<<" "<<line4[fik]->l[1]->k[1];
							pointer* k1 = lineIntersection(line2[i][0], line4[fik][0]);
							if(k1 != NULL){
								if((k1->k[0] - line2[i]->min_x()) > 0.0001 && (k1->k[0] - line2[i]->max_x())< 0.0001 && (k1->k[1] - line2[i]->min_y()) > 0.0001 && (k1->k[1] - line2[i]->max_y()) < 0.0001){
									if((k1->k[0] - line4[fik]->min_x()) > 0.0001 && (k1->k[0] - line4[fik]->max_x()) < 0.0001 && (k1->k[1] - line4[fik]->min_y()) > 0.0001 && (k1->k[1] - line4[fik]->max_y()) < 0.0001){
										cout<<"inte "<< k1->k[0]<<" "<<k1->k[1]<<" "<<line2[i]->min_x()<<endl;
										filej<<" "<< k1->k[0]<<" "<<k1->k[1]<<" "<<endl;
										line2[i]->IntersectionPoints.insert(k1);
									}
									else{
										filei<<endl;
									}

								}
								else{
									filei<<endl;
								}
							}
							else{
								filei<<"file"<<endl;
							}
						}
					}
				}
			}
			filei.close();
		}
		cout<<endl<<endl;
	}
	return 0;
}
