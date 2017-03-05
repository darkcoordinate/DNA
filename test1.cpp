#include <iostream>
#include <vector>
#include <fstream>
#include <fileread.h>
using namespace std;
class pointer{
	double a[2];
};

class line_set{
	int k[2];
	bool if_intersect;
	pointer a;
	int direction;  //a to b 0,and b and a 1;
};


class Line_node{
public:
	Line_node* next,*prev;
	Line_node* inter_lin;
	line_set* line;
	Line_node(){
		next = NULL;
		prev = NULL;
		line = NULL;
	}
	Line_node(Line_node* nxt, Line_node* prv, line_set* lin){
		next = nxt;
		prev = prv;
		line = lin;
	}
	Line_node(line_set* lin){
		next = NULL;
		prev = NULL;
		line = lin;
	}
};

class Node_list{
	Line_node* first;
	Line_node* last;
	Node_list(){
		first = NULL;
		last = NULL;
	}
	void add(Line_node* a){
		if( first == NULL){
			first = a;
			last = a;
		}
		else{
			last->next = a;
			a->prev = last;
			last = a;
		}
	}
};






int main(int argc, char** argv){
	DataSet d = read_file(argv[1]);
	cout<< d.pointset.size();
	for(int i = 0; i < d.pointset.size(); i++){
		cout<<d.pointset[i].x<<" "<<d.pointset[i].y<<" "<<d.pointset[i].z<<endl;
	}
	
	return 0;
};
