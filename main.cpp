/***************************************************************************************************************************************************
 * Auther: Anurag Singh
 *	   Integrated M.Sc. Chemistry
 *	   Department of Chemistry
 *	   Indian Institute of Technology Roorkee
 * email : sagacious112358@gmail.com sagasucy@iitr.ac.in singh@kofo.mpg.de
 * ALL RIGHT RESERVED
 *
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;
#define MODE_X 1
#define MODE_Y 2

struct Point2D{
	double x,y;
	Point2D(double ax, double ay){
		x = ax;
		y = ay;
	}
};

struct Point3D {
	double x,y,z;
	Point3D(){
		x = 0;
		y = 0;
		z = 0;
	}
	Point3D(double ax,double ay,double az){
		x = ax;
		y = ay;
		z = az;
	}

	Point2D xy(){
		return Point2D(x,y);
	}
	Point2D yz(){
		return Point2D(y,z);
	}
	Point2D zx(){
		return Point2D(z,x);
	}
	~Point3D(){}
};

struct LineSet{
	int a,b;
	LineSet(){
		a = 0;
		b = 0;
	}
	LineSet(int aa, int bb){
		a = aa;
		b = bb;
	}
	~LineSet(){}
};


struct Polygon{
	vector<Point3D> Points;
	vector<LineSet> lineSet;
	vector<int> nlineSet;
	Polygon(vector<Point3D> &p, vector<LineSet> &l, vector<int> &nl){
		Points  = p;
		lineSet = l;
		nlineSet = nl;
	}
};

char* fread_line(FILE* fs);
double IntersectionWithXN2Dline(Point2D a, Point2D b, double n);
Point2D IntersectWithXN3DPlane(Point3D a, Point3D b, double n);

void merge(float A[], int start, int mid, int end){
	int p = start, q = mid+1;
	int Arr[end - start + 1] , k = 0;
	for(int i = start; i <= end; i++) {
		if( p > mid)
			Arr[k++] = A[q++];
		else if( q > end)
			Arr[k++] = A[p++];
		else if(A[p] < A[q])
			Arr[k++] = A[p++];
		else
			Arr[k++] = A[q++];
	}
	for(int p = 0; p < k; p++) {
		A[start++] = Arr[p];
	}
}

void merge_sort(float A[], int start, int end){
	if(start < end) {
		int mid = (start + end) /2;
		merge_sort(A, start, mid);
		merge_sort(A, mid+1, end);
		merge(A, start, mid, end);
	}
}
/*
void swap(int &a, int &b){
	a = a+b;
	b = a-b;
	a = a-b;
}*/

int partition ( vector<int> &indexes, vector<Point3D> &pointset , int base, int start, int end){
	int i = start + 1;
	int piv = indexes[start];
	for(int j = start + 1; j <= end; j++) {
		if(base == MODE_X){
			if(pointset[indexes[j]].x < pointset[piv].x) {
				swap(indexes[i] , indexes[j]);
				i += 1;
			}
		}
		if( base == MODE_Y){
			if(pointset[indexes[j]].y < pointset[piv].y) {
				swap(indexes[i] , indexes[j]);
				i += 1;
			}
		}
	}
	swap(indexes[start], indexes[i - 1]);
	return i-1;
}

void quick_sort ( vector<int> &indexes, vector<Point3D> &pointset, int base, int start, int end) {
	if(start < end){
		int piv_pos = partition(indexes, pointset, base, start, end);
		quick_sort(indexes, pointset,base, start, piv_pos - 1);
		quick_sort(indexes, pointset,base, piv_pos + 1, end);
	}
}

vector<int> sort_line_segment(vector<Point3D> &pointset,int base){  //sort the set of line on the basis of X coordinate or Y coordinate as per your choices
	vector<int> return_index(pointset.size());
	for(int i = 0; i < return_index.size(); i++){
		return_index[i] = i;
	}
	quick_sort(return_index, pointset, base,0, return_index.size() -1);
	return return_index;
}

char* fread_line(FILE* fs) {
	char* ret = (char*)malloc(100*sizeof(char));
	for(int i = 0; i < 100; i++){
		ret[i] =fgetc(fs);
		if(ret[i] == '\n'|| i == 100){
			ret[i] = '\0';
			break;
		}
		if(ret[i] == EOF){
			return NULL;
		}
	}
	return ret;
}

//determining whether line intersect or not.
//We assume a sweep line passes through geometric object

//this function return intersection point of the line x=n where n is any real number
Point2D IntersectWithXN3DPlane(Point3D a, Point3D b, double n) {
	Point3D DcLine(a.x - b.x, a.y - b.y, a.z - b.z);
	if(DcLine.x != 0.0){
		return Point2D(a.y - ((a.x-n)*DcLine.y/DcLine.x), a.z - ((a.x-n)*DcLine.z/DcLine.x));
	}
	else{
		throw exception();
	}
}

double IntersectionWithXN2Dline(Point2D a, Point2D b, double n){
	Point2D DcLine(a.x - b.x, a.y - b.y);
	if(DcLine.x != 0.0) {
		return a.y - ((a.x - n)*DcLine.y/DcLine.x);
	}
	else{
		throw exception();
	}
}

double IntersectionWithYN2Dline(Point2D a, Point2D b, double n){
	Point2D DcLine(a.x - b.x, a.y - b.y);
	if(DcLine.x != 0.0) {
		return a.x - ((a.y - n)*DcLine.x/DcLine.y);
	}
	else{
		throw exception();
	}
}

//intersection of two line

vector<Point3D*> max_mode(Point3D &p1, Point3D &p2){
	vector<Point3D*> ret(2);
	if(p1.x > p2.x){
		ret[0] = &p1;
		ret[1] = &p2;
	}
	else{
		ret[0] = &p2;
		ret[1] = &p1;
	}
	return ret;
}

vector<int> Lineset_in_between(int indz_key_line, vector<LineSet> &lines, vector<Point3D> &Points){
	/* we are taking only xy coordinates only. It is like making projection on xy plane
	* we will take a line and then check it's possibility to other with all other lines
	* To do  that we  will consider  a line  parallel to y  axis and passing throught x
	* coordinate  and see if  it intersect  with the  generated line segment and how it
	* does. So if
	*/
	vector<int> ret(2);
	vector<Point3D*> pa = max_mode(Points[lines[indz_key_line].a], Points[lines[indz_key_line].b]);
	for(int i = 0; i < lines.size(); i++){
		if(i != indz_key_line){
			if((!(Points[lines[i].a].x < pa[1]->x && Points[lines[i].b].x < pa[1]->x))&&(!(Points[lines[i].a].x > pa[0]->x && Points[lines[i].b].x > pa[0]->x))){

			}
		}
	}
	return ret;
}


int main(int argc, char** argv){
	FILE* fs = fopen(argv[1], "rb");
	vector<Point3D> Points(1000);
	vector<LineSet> lineset(1000);
	int pointCounter = 0, linesetCounter = 0;
	double max_x =0,max_y =0, max_z = 0, min_x = 0, min_y = 0, min_z = 0;
	for(int i = 0; i < 1000; i++){
		char* s = fread_line(fs);
		if(s == NULL){
			break;
		}
		if(s[0] == '#'){};
		if(s[0] == 'o'){};
		if(s[0] == 'v'){
			sscanf(s+1,"%lf %lf %lf",&Points[pointCounter].x,&Points[pointCounter].y,&Points[pointCounter].z);
			pointCounter++;
		}
		if(s[0] == 'l'){
			sscanf(s+1,"%d %d",&lineset[linesetCounter].a,&lineset[linesetCounter].a);
			linesetCounter++;
		}
		printf("%d %s\n",i, s);
	}
	if(Points.size()> pointCounter){
		Points.erase(Points.begin() + pointCounter, Points.end());
	}
	if( lineset.size() > linesetCounter){
		lineset.erase(lineset.begin() + linesetCounter, lineset.end());
	}
	printf("uihifhihfrer\n");
		
	vector<int> indx = sort_line_segment(Points,MODE_X);
	for(int i = 0; i < indx.size(); i++){
		cout<< indx[i]<<" "<<Points[indx[i]].x<<" "<<Points[indx[i]].y<<" "<<Points[indx[i]].z<<endl;
	}
	// checing intersection of line


	return 0;
}
