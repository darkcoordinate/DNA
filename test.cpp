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
			i+= 1;
		}
	}
	swap(B[start] , B[i -1]);
	return i -1;
}

void quick_sort_line(vector<line*> &A, vector<int> &B, int start, int end){
	if(start < end){
		int piv_pos = partition_line(A,B,start, end);
		quick_sort_line(A,B,start,end);
		quick_sort_line(A,B,start,piv_pos - 1);
	}
}
int main(int argc, char** argv){
	ifstream file(argv[1]);
	string line2;
	vector<pointer*> Points(1000);
	vector<line*> lineset(1000);
	int pointCounter = 0, linesetCounter = 0;
	double max_x =0,max_y =0, max_z = 0, min_x = 0, min_y = 0, min_z = 0;
	for(int i = 0; i < 1000; i++){
		if(getline(file,line2) == NULL){
			break;
		}
		const char* s = line2.c_str();
		cout<<"file"<<line2<<endl;
		cout<<"prog"<<s<<endl;
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
	cout<<"Line set counter :"<<linesetCounter<<endl;
	if(Points.size()> pointCounter){
		Points.erase(Points.begin() + pointCounter, Points.end());
	}
	if( lineset.size() > linesetCounter){
		lineset.erase(lineset.begin() + linesetCounter, lineset.end());
	}
	printf("uihifhihfrer\n");
	vector<int> asn(pointCounter);
	vector<int> linar(linesetCounter);
	//I don't know what I did, so if any one can help please welcome
	for(int i = 0; i < pointCounter; i++){
		asn[i] = i;
	}
	for(int i = 0; i < linesetCounter; i++){
		linar[i] = i;
	}
	quick_sort(Points,asn,0,pointCounter - 1, 0);
	for(int i = 0; i < pointCounter; i++){
		cout<<Points[asn[i]]->k[0]<<" "<<Points[asn[i]]->k[1]<<endl;
	}
	for(int i = 0; i < linesetCounter; i++){
		cout<<lineset[i]->l[0].k[0]<<" "<<lineset[i]->l[0].k[1]<<" "<<lineset[i]->l[1].k[0]<<" "<<lineset[i]->l[1].k[1]<<endl;
	}
	cout<< "fair work";
	quick_sort_line(lineset, linar,0, linesetCounter -1);
	for(int i = 0; i < linesetCounter; i++){
		cout<<lineset[linar[i]]->l[0].k[0]<<" "<<lineset[linar[i]]->l[0].k[1]<<" "<<lineset[linar[i]]->l[1].k[0]<<" "<<lineset[linar[i]]->l[1].k[1]<<endl;
	}
#ifdef MSG1
	for(int i = 0; i < 10; i++){
		cout<<asn[i]<<" "<<point[asn[i]]->k[0]<<" "<<point[asn[i]]->k[1]<<endl;
	}
#endif
#ifdef MSG2
	cout<<lin.l[0].k[0]<<" "<<lin.l[0].k[1]<<" "<<lin.l[1].k[0]<<" "<<lin.l[1].k[1]<<endl;
	cout<<lin2.l[0].k[0]<<" "<<lin2.l[0].k[1]<<" "<<lin2.l[1].k[0]<<" "<<lin2.l[1].k[1]<<endl;
	cout<<lin3.l[0].k[0]<<" "<<lin3.l[0].k[1]<<" "<<lin3.l[1].k[0]<<" "<<lin3.l[1].k[1]<<endl;
	cout<<lin4.l[0].k[0]<<" "<<lin4.l[0].k[1]<<" "<<lin4.l[1].k[0]<<" "<<lin4.l[1].k[1]<<endl<<endl;
	for(int i = 0; i < 5; i++){
		cout<<i<<li[i].l[0].k[0]<<" "<<li[i].l[0].k[1]<<" "<<li[i].l[1].k[0]<<" "<<li[i].l[1].k[1]<<endl;
	}
#endif
	vector<pointer*> point2(linesetCounter);
	vector<int> not_nul_indx(linesetCounter);
	int ntnlsz = 0;
	for(double i = 0; i < pointCounter; i++){
		pointer p;
		int mi = 0;
		int ntnlsz = 0;
		for(int j = 0; j < linesetCounter; j++){
			try{
				//point2[j] = new pointer();
				//cout<<j<<" "<<i<<" "<<i*0.025<<endl;
				point2[j] = line_intersection_with(*(lineset[j]),Points[asn[i]]->k[0]);
				not_nul_indx[ntnlsz] = j;
				ntnlsz++;
				//cout<<" "<<point2[j]->k[0]<<" "<<point2[j]->k[1]<<endl;
				mi = 1;
			}
			catch(exception e){
				//cout<<j<<endl;
				point2[j] = NULL;
				mi = 0;
			}
		}
		quick_sort(point2, not_nul_indx,0,ntnlsz -1,1);
		cout<<endl<<ntnlsz<<endl;
		for(int j = 0; j < ntnlsz; j++){
			//cout<<endl;
			cout<<not_nul_indx[j]<<" "<<point2[not_nul_indx[j]]->k[0]<<" "<<point2[not_nul_indx[j]]->k[1]<<endl;
		}
		if(ntnlsz > 0)
			cout<<endl<<endl;
	}
	return 0;
}
