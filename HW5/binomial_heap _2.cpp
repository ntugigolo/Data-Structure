//#include "binomial_heap.h"
#include <utility>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include<queue> 
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <limits>

using namespace std;

template<class T>
class BinomialHeap {
    private:   	
    priority_queue<T> q;
/*	struct Node{
    	Node* parent;
    	Node* child;
    	Node* sibling;
    	T value;
    	int degree;
    	Node(){
        	parent = NULL;
        	child = NULL;
        	sibling = NULL;
        	value = 0;
        	degree = 0;
    	}
	};*/
	public:
    BinomialHeap(){
    	
	}	
	/*void Assign(const int& cm,const int& id,const int& p){
		
	}*/	
	
};
int main(int argc,char** argv){


	 string c;
	 cin>>c;
	 if(c == "assign"){
	 int cm,id,p;	
	 cin>>cm>>id>>p;
	 cout<<" id :"<<id;	
	 }
	 /*else if(c == "merge"){
	 	
	 }
	 else if(c == "execute"){
	 	
	 }
	 else if(c != "assign" &&c != "merge" &&c != "execute"){
	 	
	 }*/	
/*	BinomialHeap<int> B1;
	BinomialHeap<int> B2;
	B1 = (10,20,30,5,15);
	std::make_heap(B1.std::begin(),B1.std::end());
	std::make_heap(B2.begin(),B2.end());*/
	system("pause");
	return 0;
}
