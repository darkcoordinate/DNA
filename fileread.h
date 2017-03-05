#ifndef FILEREAD_H
#define FILEREAD_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;



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


class DataSet{
public:
	vector<Point3D> pointset;
	vector<LineSet> lineset;
	DataSet(int a, int b){
		pointset.resize(a);
		lineset.resize(b);
	}
};

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

DataSet read_file(char* argv){
	FILE* fs = fopen(argv, "rb");
	DataSet d(1000,1000);
	int pointCounter = 0, linesetCounter = 0;
	for(int i = 0; i < 1000; i++){
		char* s = fread_line(fs);
		if(s == NULL){
			break;
		}
		if(s[0] == '#'){};
		if(s[0] == 'o'){};
		if(s[0] == 'v'){
			sscanf(s+1,"%lf %lf %lf",&d.pointset[pointCounter].x,&d.pointset[pointCounter].y,&d.pointset[pointCounter].z);
			pointCounter++;
		}
		if(s[0] == 'l'){
			sscanf(s+1,"%d %d",&d.lineset[linesetCounter].a,&d.lineset[linesetCounter].a);
			linesetCounter++;
		}
		printf("%d %s\n",i, s);
	}
	if(d.pointset.size()> pointCounter){
		d.pointset.erase(d.pointset.begin() + pointCounter, d.pointset.end());
	}
	if( d.pointset.size() > linesetCounter){
		d.lineset.erase(d.lineset.begin() + linesetCounter, d.lineset.end());
	}
	return d;
}

#endif // FILEREAD_H
