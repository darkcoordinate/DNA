#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <exception>
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

// An AVL tree node
struct Node
{
	int indx;
	pointer key;
	Node *left;
	Node *right;
	int height;
	Node(){
		key = pointer();
	}
	Node(pointer key, int indx){
		this->indx = indx;
		this->key = key;
		left = NULL;
		right = NULL;
		height = 1;
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
	if((n >= min(lin.l[0].k[0], lin.l[1].k[0]) ) && (n <= max(lin.l[0].k[0], lin.l[1].k[0]))) {
		double k= (n-lin.l[0].k[0])/(lin.l[1].k[0] - lin.l[0].k[0]);
		//cout<<k<<" "<<"file\n";
		if((k <= 1)&&(k >= 0)){
			return new pointer(n,lin.l[0].k[1]+ (lin.l[1].k[1] - lin.l[0].k[1])*k);
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

int partition(vector<pointer*> &A, vector<int> &B, int start, int end, int p_1){
	int i =  start + 1;
	pointer* piv = A[B[start]];
	for(int j = start + 1; j <= end; j++) {
		if(A[B[j]]->k[p_1] < piv->k[p_1]) {
			swap(B[i], B[j]);
			i += 1;
		}
	}
	swap(B[start], B[i - 1]);
	return i - 1;
}


void quick_sort(vector<pointer*> &A, vector<int> &B, int start, int end, int p_1){
	if(start < end){
		int piv_pos = partition(A, B, start, end, p_1);
		quick_sort(A, B, start, piv_pos - 1, p_1);
		quick_sort(A, B, piv_pos + 1, end, p_1);
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

void read(char* argv, vector<pointer*> &Points, vector<line*> &lineset){
	ifstream file(argv);
	string line2;
	int pointCounter = 0, linesetCounter = 0;
	for(int i = 0; i < 1000; i++){
		if(getline(file,line2) == NULL){
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
			line* li1 = new line(*(Points[a - 1]), *(Points[b -1 ]));
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



int main(int argc, char**argv){
	vector<pointer*> Points(1000);
	vector<line*> lineset(1000);
	read(argv[1],Points, lineset);
	//cout<<Points.size()<<" "<<lineset.size()<<endl;
	vector<int> point(Points.size());
	for(int i = 0; i < Points.size();i++){
		point[i] = i;
	}
	vector<int> line_arr(lineset.size());
	for(int i = 0; i < lineset.size(); i++){
		line_arr[i] = i;
	}
	quick_sort(Points, point,0, Points.size() - 1, 0);
	quick_sort_line(lineset, line_arr,0,lineset.size() - 1);
	cout<<lineset.size()<<endl;
	for(int i = 0; i < lineset.size();i++){
		cout<<i<<" "<<line_arr[i]<<" "<<lineset[line_arr[i]]->l[0].k[0]<<" "<<lineset[line_arr[i]]->l[0].k[1]<<" "<<lineset[line_arr[i]]->l[1].k[0]<<" "<<lineset[line_arr[i]]->l[1].k[1]<<endl;
	}

	for(int i = 0; i < line_arr.size(); i++){
		//cout<<" printing the details ";
		//cout<<lineset[line_arr[i]]->max_x()<<" "<<lineset[line_arr[i]]->min_x()<<endl;
		int h = line_arr.size() - 1;
		int l = i;
		int m = (h + l)/2;
		while(l < h){
			if(lineset[line_arr[i]]->max_x() >= lineset[line_arr[line_arr.size() - 1]]->min_x()){
				m = h;
				break;
			}
			m = (h + l)/2;
			//cout<<m<<" "<<h<<" "<<l<<endl;
			//checking equality to the nearest y value
			if( (lineset[line_arr[i]]->max_x() < lineset[line_arr[m+1]]->min_x()) && (lineset[line_arr[i]]->max_x() >= lineset[line_arr[m]]->min_x())) {
					//( (lineset[line_arr[i]]->max_x() <= lineset[line_arr[m]]->min_x()) && (lineset[line_arr[i]]->max_x() > lineset[line_arr[m - 1 ]]->min_x()))){
				break;
			}
			else if(lineset[line_arr[i]]->max_x() >= lineset[line_arr[m + 1]]->min_x() ) {
				l = m;
			}
			else {
				h = m;
			}
		}
		//cout<<m<<endl;
		if(!(m-i == 0)){
			vector<int>y_data_max(m-i);
			for(int j =i+1, ji = 0  ; j <= m; j++, ji++){
				y_data_max[ji] = j;
			}
			quick_sort_line_ymax_if_x_sorted(lineset,line_arr,y_data_max, 0,m-i-1);
			//cout<<"y max data size "<<y_data_max.size()<<endl;
			//for(int j =0; j < y_data_max.size(); j++){
			//	cout<<y_data_max[j]<<" ";
			//}
			//cout<<endl;
			h = y_data_max.size() - 1;
			l = 0;
			m = (h + l)/2;
			while(l < h){
				if(lineset[line_arr[i]]->min_y() >= lineset[line_arr[y_data_max[y_data_max.size() - 1]]]->max_y()){
					m = h;
					break;
				}
				if(lineset[line_arr[i]]->min_y() < lineset[line_arr[y_data_max[0]]]->max_y()){
					m = -1;
					break;
				}
				m = (h + l)/2;
				if((lineset[line_arr[i]]->min_y() >= lineset[line_arr[y_data_max[m]]]->max_y()) && (lineset[line_arr[i]]->min_y() < lineset[line_arr[y_data_max[m + 1]]]->max_y())){
					break;
				}

				/*else if(( lineset[line_arr[i]]->min_y() < lineset[line_arr[y_data_max[m]]]->max_y()) && ( lineset[line_arr[i]]->min_y() >= lineset[line_arr[y_data_max[m - 1]]]->max_y())){

					break;
				}*/
				else if( lineset[line_arr[i]]->min_y() >= lineset[line_arr[y_data_max[m + 1]]]->max_y()){
					l = m;
				}
				else{
					h = m;
				}
			}
			//cout<<"y_max_data: "<<m<<endl;

			int max_y_length = m;
			if( y_data_max.size() - m - 1 > 0) {
				vector<int>y_data_min(y_data_max.size() - m - 1 );
				for(int j = 0; j < y_data_min.size(); j++){
					y_data_min[j] = j+m;
				}
				//cout<<"file N "<<y_data_min.size()<<"\n";
				quick_sort_line_ymin_if_x_sorted(lineset, line_arr, y_data_max,y_data_min, 0,  y_data_min.size() -1);
				//for(int j = 0; j < y_data_min.size(); j++){
				//	cout<<y_data_min[j]<<" ";
				//}
				//cout<<endl;
				//cout<<"Cine N "<< i <<"\n";
				h = y_data_min.size() -1;
				l = 0;
				m = (h + l)/2;
				while(l < h){
					//cout<<"line1 \n";
					if( lineset[line_arr[i]]->max_y() >= lineset[line_arr[y_data_max[y_data_min.size() - 1]]]->min_y()){
						m = h;
						break;
					}
					if( lineset[line_arr[i]]->max_y() >= lineset[line_arr[y_data_max[0]]]->min_y()){
						m = -1;
						break;
					}
					//cout<<"line 2 "<<m<<" d\n";
					m = (h + l)/2;
					if((lineset[line_arr[i]]->max_y() >= lineset[line_arr[y_data_max[y_data_min[m]]]]->min_y()) && (lineset[line_arr[i]]->max_x() < lineset[line_arr[y_data_min[y_data_max[m + 1]]]]->min_y())){
							//(( lineset[line_arr[i]]->max_y() < lineset[line_arr[y_data_max[y_data_min[m]]]]->min_y()) && ( lineset[line_arr[i]]->max_y() > lineset[line_arr[y_data_max[y_data_min[m - 1]]]]->min_y()))){
						break;
					}
					else if( lineset[line_arr[i]]->max_y() >= lineset[line_arr[y_data_max[y_data_min[m + 1]]]]->min_y()){
						l = m;
					}
					else{
						h = m;
					}
					//cout<<"line 5\n";
				}
				//cout<<"y_min_data: "<<m<<" "<<y_data_min.size()<<endl;
				for(int j = 0; j <= m; j++){
					pointer* ki1= lineIntersection(*lineset[line_arr[i]], *lineset[line_arr[y_data_max[j]]]);
					if(ki1 != NULL){
						cout<<ki1->k[0]<<" "<< ki1->k[1]<<endl;
					}
				}
				y_data_min.erase(y_data_min.begin(),y_data_min.end());
			}
			y_data_max.erase(y_data_max.begin(), y_data_max.end());
		}
	}

	return 0;
}
