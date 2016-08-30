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
#include <set>
using namespace std;

//template<class T>
class BinomialHeap {
    private:
    vector<int> Max;
   // priority_queue< vector< pair<int,int> > > q;
    //vector< vector< pair<int,int> > > Store;
   public:
    BinomialHeap();
    BinomialHeap(int&);
    vector< vector< pair<int,int> > > Store;
    vector< vector< pair<int,int> > > Store_max;
    void Assign(const int&,const int&,const int&);
    void Merge(const int&,const int&,const int&);
    void Execute(const int&);
   /* struct Comp{
   	bool operator()(const pair<int,int>& s1, const pair<int,int>& s2){
       return s1.second < s2.second ;}
	};*/
    struct SortPair{
     bool operator()(const std::pair<int, int> &p1,const std::pair<int, int> &p2) const{
         return p1.second < p2.second;
     } };

};

BinomialHeap::BinomialHeap(){}

BinomialHeap::BinomialHeap(int& c){
        Store.resize(c);
	Max.resize(c);
        }

void BinomialHeap::Assign(const int& cm,const int& id,const int& p){
	//make_heap(Store_max[cm].begin(),Store_max[cm].end(),Comp());
        Store[cm].push_back(make_pair(p,id));
	push_heap(Store[cm].begin(),Store[cm].end());
        int n = Store[cm].size();

	/*if(p > Max[cm]){
	Store_max[cm].clear();
	Store_max[cm].push_back(make_pair(p,id));
	Max[cm] = p;
	}
	else if(p == Max[cm]){
	make_heap(Store_max[cm].begin(),Store_max[cm].end(),Comp());
	Store_max[cm].push_back(make_pair(p,id));
	push_heap(Store_max[cm].begin(),Store_max[cm].end(),Comp());
	}*/
        cout<<"There are "<<n<<" tasks on computer "<<cm<<"."<<endl;
        }

void BinomialHeap::Merge(const int& cm1,const int& cm2,const int& w){
	int n2 = Store[cm2].size();
	int n1 = Store[cm1].size();
	int p_max;
	if(n2 >= w){
	/*if(Store_max[cm1].size()!=0 && Store_max[cm1][0].first > Store_max[cm2][0].first){
		p_max = Store_max[cm1][0].first;
	}
	else if(Store_max[cm1].size()!=0 && Store_max[cm1][0].first == Store_max[cm2][0].first){
		p_max = Store_max[cm1][0].first;
		vector< pair<int,int> > Tmp = Store_max[cm1];
		int m1 = Store_max[cm1].size();
		int m2 = Store_max[cm2].size();
		Store_max[cm1].clear();
		Store_max[cm1].resize(m1+m2);
		std::merge(Tmp.begin(),Tmp.end(),Store_max[cm2].begin(),Store_max[cm2].end(),Store_max[cm1].begin());
		make_heap(Store_max[cm1].begin(),Store_max[cm1].end(),Comp());
		}
	else if(Store_max[cm1].size()!=0 && Store_max[cm1][0].first < Store_max[cm2][0].first){
		p_max = Store_max[cm2][0].first;
		}
	else if(Store_max[cm1].size()==0){
		p_max = Store_max[cm2][0].first;
		}*/
	vector< pair<int,int> > Tmp1 = Store[cm1];
	Store[cm1].clear();
	Store[cm1].resize(n1+n2);
	std::merge(Tmp1.begin(),Tmp1.end(),Store[cm2].begin(),Store[cm2].end(),Store[cm1].begin());
	Store[cm2].clear();
	make_heap(Store[cm1].begin(),Store[cm1].end());
	p_max = Store[cm1].front().first;
	cout<<"The largest priority number is now "<<p_max<<" on "<<cm1<<"."<<endl;
	}
	else{
	cout<<"Merging request failed."<<endl;
	}

	}

void BinomialHeap::Execute(const int& cm){

	/*vector< pair<int,int> >::iterator it = Store[cm].begin();
	 for(;it != Store[cm].end();it++){*/
	int prev = Store[cm].front().first;
	multiset< pair<int, int> , SortPair > mset;

	while(prev == Store[cm].front().first){
	mset.insert(pair<int , int>(Store[cm].front().first,Store[cm].front().second));
	pop_heap(Store[cm].begin(),Store[cm].end());
	Store[cm].pop_back();
	}
	multiset< pair<int, int>,SortPair >::iterator it = mset.begin();
	//cout<<"multiset :"<<mset<<endl;
	for( ;it != mset.end();it++){

	//int pop = Store[cm1].front().first;
	cout<<"Computer "<<cm<<" executed task "<<it->second<<"."<<endl;
	}
}

int main(int argc,char** argv){
	 string c;
	//vector< vector<int> > Store;
	int c1,w;
	cin>>c1>>w;
	BinomialHeap A(c1);
	vector< vector<int> > input;
	vector<int> ass(3),mer(2),exe(1);
	while(cin>>c){
	 //if(cin>>c){
	//if(!cin.eof()){
	/*if(c != "assign" &&c != "merge" &&c != "execute"){
                int c1 = atoi(c.c_str());
                BinomialHeap A(c1);
                int w;
                cin>>w;
         }*/
	if(c == "assign"){
	int cm,id,p;
	 cin>>cm>>id>>p;
        ass[0] = cm;
        ass[1] = id;
        ass[2] = p;
	input.push_back(ass);
		}
	else if(c == "merge"){
	int cm1,cm2;
	cin>>cm1>>cm2;
	mer[0] = cm1;
	mer[1] = cm2;
	input.push_back(mer);
         	}
         else if(c == "execute"){
	int cm_;
	cin>>cm_;
	exe[0] = cm_;
	input.push_back(exe); }
	//}
       /* else{
		break;  }*/
	}
	vector<vector<int> >::iterator itTot = input.begin();
  	for(;itTot != input.end();itTot++){
	 if(input[distance(input.begin(),itTot)].size() == 3){
	A.Assign(input[distance(input.begin(),itTot)][0],input[distance(input.begin(),itTot)][1],input[distance(input.begin(),itTot)][2]);
	 }
	else if(input[distance(input.begin(),itTot)].size() == 2){
	//cout<<"Seph"<<endl;
	A.Merge(input[distance(input.begin(),itTot)][0],input[distance(input.begin(),itTot)][1],w);
	//cout<<"Sephria"<<endl;
	 }
	 else if(input[distance(input.begin(),itTot)].size() == 1){
	A.Execute(input[distance(input.begin(),itTot)][0]);
	}
	}
	system("pause");
	return 0;
}
