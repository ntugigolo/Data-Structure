#include "binomial_heap.h"
#include <utility>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

int main(){
	
	BinomialHeap<int> B1;
	BinomialHeap<int> B2;
	B1 = (10,20,30,5,15);
	
	std::make_heap(B1.std::begin(),B1.std::end());
	std::make_heap(B2.begin(),B2.end());
	
}
