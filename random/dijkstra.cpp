#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include <iterator>

//#define INT_MAX 2147483648

enum state { visited, unvisited };

using namespace std;

/*============================================================================
 * Class prototypes
 *1) adjacency list node
 *2) undirected graph
 *3) fibonacci node
 *4) fibonacci heap
 *============================================================================*/

struct adjListNode{
	int dest;
	int weight;
	map<int , int> neighbors; //destination mapped to weight from source to that node
};

class graph{
    
public:
	int n;
	int e;
	adjListNode *list;
    
	graph(int, int);
	graph(int, float);
	void createGraph();
	void printGraph(int);
	int random(int);
	int findWeight(int, int);
	void createGraphFile(vector<vector<int> >&);
};

class fnode{
    
public:
	int key;
	int index;
	fnode *left;
	fnode *right;
	fnode *parent;
	fnode *child;
	int degree;
	bool childCut;
	fnode(int, int);
	void delNode();
	void insertRight(fnode *);
	void link(fnode *);
};

class fiboHeap{

public:
	fnode *min;
	int nH;
    std::vector<fnode *> nodeaddress;
	fiboHeap();
	void insert(fnode *);
	void insert(int, int);
	int getMinKey();
	int getMinIndex();
	int getKey(int);
	fnode *getMin();
	int numNodes();
	void removeMin();
	void consolidate();
	void display();
	void decreaseKey(int, int);
	void cut(fnode *);
	void cascadeCut(fnode *);
    void print(fnode *, fnode *);
};

/*============================================================================
 * This class defines the graphs based on the adjacency list
 * The graph can be created using either a file or random number
 * generator
 *============================================================================*/


graph::graph(int vertices, float density){
	n = vertices;
	e = (int)(density * vertices * (vertices - 1) / 200);
	cout << "edges : " << e << endl;
	list = new adjListNode[n];
	for(int i = 0; i < n; i++ ){ //point the next to NULL for each node
        list[i].dest = i;
        list[i].weight = 0;
	}
}

graph::graph(int vertices, int edges){
	n = vertices;
	e = edges;
	list = new adjListNode[n];
	for(int i = 0; i < n; i++ ){
        list[i].dest = i;
        list[i].weight = 0;
	}
}

int graph::random(int k){
	return rand() % k;
}

void graph::createGraph(){
	int i, j, weight;
	int k = 0;
	int flag_i = 0, flag_j = 0;
	bool isconnected = true;
	map<int, int> nodes_accounted;
	do{
		srand(time(NULL)); //1394919331 -- seed to create infinite loop
		//cout << time(NULL) << endl;
		while(k < e) {
            
			flag_i = 0;
			flag_j = 0;
			if(k < n)
				i = k;
			else
				i = random(n);
			j = random(n);
			weight = random(1000) + 1;
            
			nodes_accounted[i]++;
			nodes_accounted[j]++;
            
			if(i != j){
                
				if(list[j].neighbors.count(i) > 0) {// (j, i) already exists
					weight = list[j].neighbors[i];
				} else {
					list[j].neighbors[i] = weight; //if (j, i) doesn't exist then create one
				}
                
				if(list[i].neighbors.count(j) == 0){
					list[i].neighbors[j] = weight; //j is the destination and mapped to its weight forming i, j
					cout << "(" << k << ") " << i << ", " << j << " -- "<< list[i].neighbors[j] <<" ------- ";
					cout << "(" << k << ") " << j << ", " << i << " -- "<< list[j].neighbors[i] << endl;
					k++;
				}
			}
		}
        
		isconnected = true; //start with assuming the graph is connected
		for(int i = 0; i < n; i++){ //check if the graph is connected
			if(nodes_accounted.count(i) == 0){
				isconnected = false;
				cout << "isconnected : " << isconnected << endl;
				break;
			}
		}
        
		if(!isconnected){ //clear the graph if it is not connected
			cout << "cleared" << endl;
			for(int i = 0; i < n; i++ ){
				list[i].neighbors.clear();
				list[i].dest = i;
				list[i].weight = 0;
				nodes_accounted.clear();
				k = 0;
			}
		}
	}while(!isconnected);
}

void graph::createGraphFile(vector<vector<int> >& graphNodes){
	for(int i = 0; i < e; i++){
		list[graphNodes[i][0]].neighbors[graphNodes[i][1]] = graphNodes[i][2];
		list[graphNodes[i][1]].neighbors[graphNodes[i][0]] = graphNodes[i][2];
		cout << "(" << i << ") " << graphNodes[i][0] << ", " << graphNodes[i][1] << " -- "<< list[graphNodes[i][0]].neighbors[graphNodes[i][1]] <<" ------- ";
		cout << "(" << i << ") " << graphNodes[i][1] << ", " << graphNodes[i][0] << " -- "<< list[graphNodes[i][1]].neighbors[graphNodes[i][0]] << endl;
	}
}

int graph::findWeight(int i, int j){
	return list[i].neighbors[j];
}

/*============================================================================
 * Methods of class fnode
 * These are the methods of the fibonacci node class
 *============================================================================*/
fnode::fnode(int ind, int k){
	key = k;
	index = ind;
	degree = 0;
	left = this;
	right = this;
	parent = NULL;
	child = NULL;
	childCut = false;
}

void fnode::delNode(){
	parent = NULL;
	child = NULL;
	left = NULL;
	right = NULL;
}

void fnode::insertRight(fnode *f){
    
	assert(f != NULL);
	assert(this != NULL);
	f->right = this->right;
	f->left = this;
	this->right->left = f;
	this->right = f;
}

void fnode::link(fnode *f){
	assert(f != NULL);
	assert(this != NULL);
	
    if(f->right != NULL)
        f->right->left = f->left;
	if(f->left != NULL)
        f->left->right = f->right;
	
    f->parent = this;
	
    if(this->child != NULL){
		this->child->insertRight(f);
		if(f->key < this->child->key)
			this->child = f;
	} else {
		this->child = f;
		f->right = f;
		f->left = f;
	}

	f->childCut = false;
	this->degree += 1;
}

/*int main(){
 fiboNode *node = new fiboNode(10);
 return 0;
 }*/

/*============================================================================
 * Methods of class fibonacci Heap (fiboHeap class)
 *============================================================================*/
fiboHeap::fiboHeap(){
	min = NULL;
	nH = 0;
}

int fiboHeap::getMinKey(){
	return min->key;
}

int fiboHeap::getMinIndex(){
	return min->index;
}

int fiboHeap::getKey(int index){
	return nodeaddress[index]->key;
}

fnode * fiboHeap::getMin(){
	return min;
}

int fiboHeap::numNodes(){
	return nH;
}

void fiboHeap::insert(int index, int key){
	fnode *f = new fnode(index, key);
	insert(f);
	nodeaddress.push_back(f);
}

void fiboHeap::insert(fnode *f){
	if(min == NULL){
		min = f;
        f->right = f;
        f->left = f;
		nH = 0;
	} else {
		min->insertRight(f);
        
		if(min->key > f->key)
			min = f;
	}
	nH = nH + 1;
}

void fiboHeap::removeMin(){
	fnode *z = min;
	fnode *traverse = NULL;
	fnode *x = NULL;

    assert(z != NULL);
    
	if(z != NULL)
		traverse = z->child;
    
	if(traverse != NULL){ //add all the children to the root list
		do{
			x = traverse;
			traverse = traverse->right;
            
			min->insertRight(x); //add x to the root by adding right to the min
			x->parent = NULL;
			if(min->key > x->key)
				min = x;
		}while(traverse != NULL && traverse != z->child);
	}
    
	//remove the old min stored in z
	z->right->left = z->left;
	z->left->right = z->right;
    
	if(z == z->right){
		//min = NULL;
	} else {
		min = z->right;
		//this->print(min, min->parent); //print the fibheap
        consolidate(); //consolidate after removeMin
        //this->print(min, min->parent); //print the fibheap
	}
    
	nH = nH - 1;
	z->delNode();
}

void fiboHeap::consolidate(){
    
	int D = ceil(log(nH) / log(2)) + 1;
	int d = 0; //degree
    
	//cout << "D : " << D << "min : "<<  min->key <<endl;
	fnode *A[D];
    
	for(int i = 0; i <= D; i++){
		A[i] = NULL;
    }
    
    //this->print(min, min->parent); //print the fibheap
	fnode *traverse = min;
	fnode *x = NULL;
	fnode *y = NULL;
	fnode *temp = NULL;
    
    //break the link here so that it doesn't go into infinite loop
    min->left->right = NULL;
    min->left = NULL;
    
	do{
		x = traverse;
        
		d = x->degree;

        traverse = traverse->right;
        assert(d <= D);
        cout << "" ;
		
        while (A[d] != NULL){
			y = A[d];
			//cout << "(in while)y key : " << y->key << ", x : " << x->key << endl;
			assert (A[d] != NULL);
			assert(x != NULL);
			assert(y != NULL);
            
			if(x->key > y->key){
				temp = x;
				x = y;
				y = temp;
			}
            
            if(traverse == y)
                traverse = y->right;
            
			if(y == min)	//min should always point something in root list so that the do-while loop terminates
				min = x;
            
			//cout << "(in while)y key : " << y->key << ", x : " << x->key << endl;
			//cout << "(in while)key before link : " << y->key << ", min : " << min->key <<endl;
            
            x->link(y);
			A[d] = NULL;
			d = d + 1;
			//cout << "(in while) after link degree : " << d << "x : " << x->key<< endl;
		}
        
		A[d] = x;
		//traverse= x->right;
	}while(traverse != NULL);
    
	min = NULL;
    
	for(int i = 0; i < D; i++){ //to set the new min
		if(A[i] != NULL){
            
            A[i]->left = A[i];
            A[i]->right = A[i];
            
			if(min == NULL){
				min = A[i];
			} else {
                min->insertRight(A[i]);
                if(min->key > A[i]->key)
                    min = A[i];
			}
		}
	}
}

void fiboHeap::decreaseKey(int index, int k){
	fnode *x = nodeaddress[index];
	fnode *y = x->parent;
	if(x->key < k)
		throw "ERROR: new key greater than the old key";
	if(min == NULL)
		throw "ERROR: HEAP EMPTY";
    
	x->key = k;
	if(y != NULL && x->key < y->key){ //if x is a node in the root list or key(x) > key(parent of x)
		//this->print(min, min->parent); //print the fibheap
        cut(x);
		//this->print(min, min->parent); //print the fibheap
		cascadeCut(y);
		//this->print(min, min->parent); //print the fibheap
	}
    
	if(min->key > x->key)
		min = x;
}

void fiboHeap::cut(fnode *x){
	fnode *y = x->parent;
	if(y->child == x){
		if(x->right == x)
			y->child = NULL;
		else
			y->child = x->right;
	}
    
	x->right->left = x->left; //to remove the node from the link
	x->left->right = x->right;
	y->degree -= 1; //decrease the degree of the parent after the child is removed
    
	min->insertRight(x);
	x->parent = NULL;
	x->childCut = false;
}

void fiboHeap::cascadeCut(fnode *y){
	fnode *z = y->parent;
	if(z == NULL) //base case : if the node is in the root list
		return;
    
	if(z != NULL){
		if(y->childCut == false){
			y->childCut = true;
		} else {
			cut(y);
			cascadeCut(z); //call recursively progressing up towards the root list
		}
	}
}

void fiboHeap::print(fnode * start , fnode * parent){ //to debug the fiboheap
    
    if(start != NULL){
        if (min == start) {
            //cout<<"root list(print) = index : " << min->index << " min key: " << min->key << endl;
        }
        
        fnode * traverse = NULL;
        
        traverse = start;
        do{
            //cout << iter->toString();
            if (traverse->left == NULL) {
                cout<<"*ln";
                assert(0);
            }
            if (traverse->parent != parent) {
                cout<<"*pw";
                assert(0); //IGNORING THIS FOR A WHILE
            }
            if (traverse->right == NULL) {
                cout<<"*rn";
                assert(0);
            }else if(traverse->right->left != traverse){
                cout<<"*le ->";
                assert(0);
            }else{
                //cout<<" <-> ";
            }
            
            traverse = traverse->right;
        }while (traverse != NULL && traverse != start);
        
        //TODO uncomment cout<<"\n";
        traverse = start;
        
        do{
            //cout<<"Children of "<<iter->toString() << " : ";
            if (traverse->child == NULL) {
                //cout<< "(" << traverse->index << ")"<<" NONE " << endl;
            } else {
                print(traverse->child, traverse);
            }
            traverse = traverse->right;
        }while (traverse != NULL && traverse != start) ;
    }else{
        cout<<"The heap is empty \n";
    }
    
}

void fiboHeap::display(){ //needs to be enhanced displays only the root list
	fnode *traverse;
	if(min != NULL){
		traverse = min;
		cout << "root list : ";
		do{
			cout << traverse->key <<"(" << traverse->index << ")" << "-->" ;
			traverse = traverse->right;
		}while(traverse != min);
		cout << traverse->key << endl;
	}
}

/*============================================================================
 * Helper functions
 * 1) create graph based on no. of vertices and edges
 * 2) create graph based on no. of vertices and desnsity
 * 3) readfile to read the edge configuration for undirected graph
 *============================================================================*/

graph *dijkstraGraph(int n, int e){
	graph *g = new graph(n, e); //to store the edges
	g->createGraph();
	return g;
}

graph *dijkstraGraph(int n, float d){
	graph *g = new graph(n, d); //to store the edges
	g->createGraph();
	return g;
}

void readFile(vector<vector<int> >& graphNodes, string filename, int & n, int & e){
	fstream fh;
	filename = "/Users/rutayanpatro/Dropbox/ADS/adsproject/adsproject/" + filename;
	char *fname = new char[filename.length() + 1];
	strcpy(fname, filename.c_str());
	fh.open(fname, fstream::in);
	assert(fh.is_open()); //check if the file is open
    
    string line;
	int u, v, weight;
    //	fh>> numlines;
    //	cout << numlines << endl;
    
	getline(fh, line);
	istringstream ss(line);
	cout << line << endl;
	fh>> n >> e;
	cout << n << ", " << e << endl;
    
	for(int i = 0; i < e; i++){
		fh >> u >> v >> weight;
		vector<int > temp;
		temp.push_back(u);
		temp.push_back(v);
		temp.push_back(weight);
		graphNodes.push_back(temp);
		//cout << graphNodes[i][0] << " " << graphNodes[i][1] << " " << graphNodes[i][2] << endl;
	}
}

/*============================================================================
 * Name			: dijkstraSimpleSequence.cpp
 * Author		: Rutayan Patro
 * Version		:
 * Copyright		: Please don't use it for assignments
 * Description	: Dijkstra's shortest path algorithm using fibonacci heap
 * Time			: O(nlogn + e)
 *============================================================================*/
void stpfibo(graph *g, int n, int x){
	fiboHeap *dist = new fiboHeap();
	int dist_u;
	int u;
    
	for(int i = 0; i < n; i++){
		dist->insert(i, INT_MAX);
	}
    
	//dist->display(); //debug
	dist->decreaseKey(x, 0);
	//cout << "new min : " << dist->getKey(x) << ", index : " << dist->getMinIndex() << endl; //debug
	//dist->display(); //debug
    
	for(int i = 0; i < n; i++){
		dist_u = dist->getMinKey();
		u = dist->getMinIndex();
		cout << "(" << i << ")(loop)to be removed index : " << dist->getMinIndex() << ", min : " << dist_u << endl;
		//dist->print(dist->min, dist->min->parent);
        dist->removeMin();
        //dist->print(dist->min, dist->min->parent); //print the fibheap
        assert(dist->min != NULL);
        
		for(map<int, int>::iterator v = g->list[u].neighbors.begin(); v != g->list[u].neighbors.end(); v++){
			//cout << u << "-->" << v->first << " weight : " << v->second << endl;
			if(dist->getKey(v->first) > (dist_u + g->findWeight(u, v->first))){
                dist->decreaseKey(v->first, dist_u + g->findWeight(u, v->first));
                //dist->print(dist->min, dist->min->parent); //print the fibheap
                //cout << v->first << " : " << dist->getKey(v->first) << endl;
			}
			//cout << "2 : " << dist->getKey(2) << endl;
		}
        
	}
    
	for(int i = 0; i < n; i++){
		cout << i << "=> " << dist->getKey(i) << endl;
	}
}


/*============================================================================
 * Name        : dijkstraSimpleSequence.cpp
 * Author      : Rutayan Patro
 * Version     :
 * Copyright   : Please don't use it for assignments
 * Description : Dijkstra's shortest path algorithm
 * Time			: O(n^2)
 *============================================================================*/
int removeMin(int *dist, state *isvisited, int n){
    
	int min = INT_MAX;
	int min_index;
    
	for(int i = 0; i < n; i++){
		if (dist[i] < min && isvisited[i] == unvisited){
			min = dist[i];
			min_index = i;
		}
	}
	//cout << min_index << endl;
	return min_index;
}

void stpSimpleSequence(graph *g, int n, int x){
    
	int *dist = new int[n];
	state *isvisited = new state[n];
	int u;
    
	for(int i = 0; i < n; i++){
		dist[i] = INT_MAX;
		isvisited[i] = unvisited;
	}
    
	dist[x] = 0;
    
	for(int i = 0; i < n; i++){
		u = removeMin(dist, isvisited, n); //implementation required
		isvisited[u] = visited;
		for(map<int, int>::iterator v = g->list[u].neighbors.begin(); v != g->list[u].neighbors.end(); v++){
			//cout << u << "-->" << v->first << " weight : " << v->second << endl;
			if(isvisited[v->first] == unvisited && (dist[v->first] > dist[u] + g->findWeight(u, v->first))){
				dist[v->first] = dist[u] + g->findWeight(u, v->first);
			}
		}
        
	}
    
	for(int i = 0; i < n; i++){
		cout << i << "=> " << dist[i] << endl;
	}
}

/*int main(){
 int n = 0;
 int e = 0;
 vector<vector<int> > graphNodes;
 string fileName = "nodeedge3.txt";
 readFile(graphNodes, fileName, n, e);
 //graph *g = new graph(n, e);
 cout << "\n======\n" << endl;
 //g->createGraphFile(graphNodes);
 }*/
int main(int argc, char *argv[]) {
    
	int n = 10;
	float d = 10;
	int e = 45;
	vector<vector<int> > graphNodes;
	char fileName[] = "nodeedge.txt";
	int x = 0; //starting node
	graph *g = dijkstraGraph(n, e);
    
    /*readFile(graphNodes, fileName, n, e);
    cout << "n : " << n << endl;
    cout << "e : " << e << endl;
    graph *g = new graph(n, e);
    g->createGraphFile(graphNodes);*/
    
    for(int x = 0; x < 1; x++){
        stpSimpleSequence(g, n, x);
        cout << "\n======\n" <<endl;
        stpfibo(g, n, x);
        cout << "finish ========\n\n";
    }
	return 0;
}

