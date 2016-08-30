#include <iostream>
#include <ctime>
#include <stdio.h>
#include <fstream>
#include <map>
#include <vector>
#include <iostream>
#include<iomanip>
#include "list" 
#include <stdlib.h>
#include <cstring>
#include <set>
#include <algorithm>
#include <sstream>
#define LINE_LEN 800
using namespace std;

class BD {

	public:
		BD();
		BD(string&,vector<string>&);
		~BD();
		void catchID(vector<string>&);
		void get(string&,string&,string&,string&,string&);
		void clicked(string&);
		void impressed(string&,string&);
		void profit(string&,double);
		void Sort(vector<vector<string> >&,long int);
		void swap(vector<string>&,vector<string>&);
		string Find(string&,int); 
	 
	private:
		void Sort(vector<vector<string> >&,long int,long int,long int);
		vector<vector<long int> > listPos;
		vector<string> listId;
		vector<string> profit_store;
		string Filename;	
};

BD::BD(string &Filename_,vector<string>& a_profit){
	Filename = Filename_;
	vector<long int> BegintoEnd(2,0); 
	listPos.assign(23907640,BegintoEnd);
	catchID(a_profit);	
	//catchID();
}
BD::~BD(){}
string BD::Find(string& S,int a){
	int ite=0;
	int index1,index2,begin;
	int Sephiria = 0;
	if(a==0){
		begin = S.find_first_of(" \t");	
		string Sub = S.substr(0,begin);
		return Sub;
		} 
 		
	for(string::iterator it=S.begin();it!=S.end();it++){
		if( *it == '\t') ite++;
		if (ite ==a && Sephiria==0 ){ 
			index1 = distance(S.begin(),it);
			Sephiria = 1;
		}	
		if(ite == a+1){
		 index2 = distance(S.begin(),it);
		break;	
			}
	}
	string Sub = S.substr(index1+1,index2-index1);
	return Sub;
}
void BD::swap(vector<string>& a,vector<string>& b){
	vector<string> Tmp(2);
	Tmp[0] = a[0];
	Tmp[1] = a[1];
	a[0] = b[0];
  	a[1] = b[1];
	b[0] = Tmp[0];
 	b[1] = Tmp[1];
}
void BD::Sort(vector<vector<string> >& Out,long int length)
{
    BD::Sort(Out, length, 0, length - 1);
}
 
void BD::Sort(vector<vector<string> >& Out,long int length,long int left,long int right)
{
    if (right <= left)
        return;
long int pivotIndex = (left + right) / 2;
    long int pivot = atol(Out[pivotIndex][0].c_str());
    swap(Out[pivotIndex], Out[right]);
    long int swapIndex = left;
    for (long int i = left; i < right; ++i)
    {
        if (atol(Out[i][0].c_str()) <= pivot)
        {
            swap(Out[i], Out[swapIndex]);
            ++swapIndex;
        }
    }
    swap(Out[swapIndex], Out[right]);
 
    BD::Sort(Out, length, left, swapIndex - 1);
    BD::Sort(Out, length, swapIndex + 1, right);
}

void BD::catchID(vector<string>& a_profit){
//  void BD::catchID(){
	vector<long int> subListPos(2,0);
	FILE* file;
	file = fopen(Filename.c_str(),"r");
	if (!file)
	{
		fprintf( stderr, "%s", "Could not open file.\n" );
		fclose( file );
	}
	fseek(file, 0, SEEK_END);
	long int TotalLength = ftell(file);
	fseek(file,0,SEEK_SET);
	string spaces(" \t");
	string number="0123456789";
	string PreUser="@";
	char line[LINE_LEN];
	long int length = 0;
	//long int plus=0;
	do{
		fgets(line, LINE_LEN, file);
		fseek(file,0 , SEEK_CUR);
		length = ftell(file);
		string Read(line);
		if(a_profit[atol(Find(Read,3).c_str())] != "@")//string::npos){
		profit_store.push_back(Read);
		long int begin = Read.find_last_of(spaces);
		long int end = Read.find_last_of(number);
		string UserId = Read.substr(begin+1,end-begin); 
		if(UserId != PreUser){
			if(PreUser != "@"){
				subListPos[1] = length - Read.size()-1;
				
				listPos[atol(PreUser.c_str())] = subListPos;
				subListPos[0] = length- Read.size();
			}
			PreUser = UserId;
		}
	}while(length<TotalLength);
	subListPos[1] = length;
	listPos[atol(PreUser.c_str())] = subListPos;
	fclose( file );
}

void BD::get(string& u,string& a,string& q,string& p,string& d){
	vector<string> Tmp,Tmp2 ;

	FILE* file;
	file = fopen(Filename.c_str(),"r");
	if (!file)
	{
		fprintf( stderr, "%s", "Could not open file.\n" );
		fclose( file );
	}

	char line[LINE_LEN];
	long int length = 0;
	//fseek(file, listPos[distance(listPos.begin(),itPos)][0], SEEK_SET);
	fseek(file, listPos[atol(u.c_str())][0], SEEK_SET);
	do{
		fgets( line, LINE_LEN, file );
		length = ftell(file)-1;
		string Read(line);
		//if(length <=listPos[atol(u.c_str())][1])
			Tmp.push_back(Read);
	}while(length <=listPos[atol(u.c_str())][1]);
	for(vector<string>::iterator it = Tmp.begin();it != Tmp.end();it++){
		if(atol(Find((*it),3).c_str())==atol(a.c_str()) && atol(Find((*it),7).c_str())==atol(q.c_str()) && atol(Find((*it),6).c_str())==atol(p.c_str()) && atol(Find((*it),5).c_str())==atol(d.c_str()))
                Tmp2.push_back(*it);
                }
	long int clic =0;
	long int impress=0;
	for(vector<string>::iterator it = Tmp2.begin();it != Tmp2.end();it++){
             clic  +=  atol(Find( *it,0).c_str());
	     impress  +=  atol(Find( *it,1).c_str());		
        }
		cout<<"********************"<<endl;
		cout<<clic<<"\t"<<impress<<endl;
		cout<<"********************"<<endl;

}

void BD::clicked(string& u){
	 vector<string> Tmp;
	vector<string> Tmp2(2);
	multimap <string,string> Out;
        FILE* file;
        file = fopen(Filename.c_str(),"r");
        if (!file)
        {
                fprintf( stderr, "%s", "Could not open file.\n" );
                fclose( file );
        }

        char line[LINE_LEN];
        long int length = 0;
        //fseek(file, listPos[distance(listPos.begin(),itPos)][0], SEEK_SET);
        fseek(file, listPos[atol(u.c_str())][0], SEEK_SET);
        do{
                fgets( line, LINE_LEN, file );
                length = ftell(file)-1;
                string Read(line);
               // if(length <=listPos[atol(u.c_str())][1])
                        Tmp.push_back(Read);
        }while(length <=listPos[atol(u.c_str())][1]);
	 for(vector<string>::iterator it = Tmp.begin();it != Tmp.end();it++){
	 	if(atol(Find( *it,0).c_str())>=1 ){
		Tmp2[0] = Find( *it,3);
		Tmp2[1] = Find( *it,7);
		//Out.push_back(Tmp2);
		Out.insert(make_pair(Tmp2[0],Tmp2[1]));
		}	
	}

	set< pair<string, string> > b;
	for (multimap<string, string>::iterator i=Out.begin(); i!=Out.end(); i++)
	//for(vector<vector<string> >::iterator i=Out.begin(); i!=Out.end(); i++)
    		b.insert(pair<string, string>((*i).first, (*i).second));
		//b.insert(pair<string, string>(Out[distance(Out.begin(),i)][0],Out[distance(Out.begin(),i)][1]));
	cout<<"********************"<<endl;
	for(set< pair<string, string> >::iterator it = b.begin();it != b.end();it++){
         cout<<it->first<<" "<<it->second<<endl;
	}
	cout<<"********************"<<endl;
}	

void BD::impressed(string& u1,string& u2){
	//vector<string> Tmp_u3;
	vector<vector<string> > Tmp_u3;
	//vector<vector<string> > Tmp_u1;
	//multimap< long int,string > Tmp_u1;
	map< long int, vector<string> > Tmp_u1;
	vector<string> sub_Tmp_u1;
	//vector<vector<string> > Tmp_u2;
	//multimap< long int,string > Tmp_u2;
	map< long int,vector<string> > Tmp_u2;
	vector<string> sub_Tmp_u2;
        vector<string> Tmp2(2);

    //    multimap <string,string > Out;
        /*vector<vector<long int> >::iterator itPos1 = listPos.begin();
        vector<string>::iterator itId1 = listId.begin();
	vector<vector<long int> >::iterator itPos2 = listPos.begin();
        vector<string>::iterator itId2 = listId.begin();
        for(  ;itPos1 != listPos.end(); ++itPos1 ,++itId1){
                if( *itId1 == u1){
		break;}
        }

//	vector<long int>::iterator subitPos = itPos->begin();
        for(  ;itPos2 != listPos.end(); ++itPos2 ,++itId2){
                if( *itId2 == u2){
                break;}
        }*/
        FILE* file;
        file = fopen(Filename.c_str(),"r");
        if (!file)
        {
                fprintf( stderr, "%s", "Could not open file.\n" );
                fclose( file );
        }
        char line[LINE_LEN];
        long int length = 0;
	string same = "H";
        fseek(file, listPos[atol(u1.c_str())][0], SEEK_SET);
        do{
                fgets( line, LINE_LEN, file );
                length = ftell(file)-1;
                string Read(line);
               // if(length <=listPos[atol(u1.c_str())][1]){
			//sub_Tmp_u1.push_back(Find(Read,3));
			if (atol(Find(Read,3).c_str()) == atol(same.c_str())){
			//sub_Tmp_u1.push_back(Read);
			Tmp_u1[atol(same.c_str())].push_back(Read); 

			}
			/*sub_Tmp_u1[0] = Find(Read,3);
			sub_Tmp_u1[1] =	Read;*/
                        //Tmp_u1.push_back(sub_Tmp_u1);
			else if(atol(Find(Read,3).c_str()) != atol(same.c_str()) && same != "H"){
			//Tmp_u1[atol(same.c_str())] = sub_Tmp_u1;	
			Tmp_u1[atol(Find(Read,3).c_str())].push_back(Read);	
			same = Find(Read,3);
			//sub_Tmp_u1.clear();
			//sub_Tmp_u1.push_back(Read);
			}
			else if(atol(Find(Read,3).c_str()) != atol(same.c_str())){
			Tmp_u1[atol(Find(Read,3).c_str())].push_back(Read); 
			//sub_Tmp_u1.push_back(Read);
			same = Find(Read,3);}
		//	}
	/*	if(length - Read.size()-1 <= listPos[distance(listPos.begin(),itPos1)][1]){
		Tmp_u1[atol(same.c_str())] = sub_Tmp_u1;	
		}*/
        }while(length <=listPos[atol(u1.c_str())][1]);

	/*for(multiset< long int,string >::iterator it = Tmp_u1.begin();it!=Tmp_u1.end();it++)
	{coggut<<"The element in User1 :"<<it->second<<endl;}*/
	string same2 = "H";
	//fseek(file, listPos[distance(listPos.begin(),itPos2)][0], SEEK_SET);
        fseek(file, listPos[atol(u2.c_str())][0], SEEK_SET);
        do{
                fgets( line, LINE_LEN, file );
                length = ftell(file)-1;
                string Read(line);
          //      if(length <=listPos[atol(u2.c_str())][1]){
			if (atol(Find(Read,3).c_str()) == atol(same2.c_str())){
			//sub_Tmp_u2.push_back(Read);
			Tmp_u2[atol(same2.c_str())].push_back(Read); 
			}
			/*sub_Tmp_u2[0] = Find(Read,3);
                        sub_Tmp_u2[1] = Read;*/
			//Tmp_u2.push_back(sub_Tmp_u2);}
			else if(atol(Find(Read,3).c_str()) != atol(same2.c_str()) && same2 != "H"){
			//Tmp_u2[atol(same2.c_str())] = sub_Tmp_u2;	
			Tmp_u2[atol(Find(Read,3).c_str())].push_back(Read);	
			same2 = Find(Read,3);
			//sub_Tmp_u2.clear();
			//sub_Tmp_u2.push_back(Read);
			}
			else if(atol(Find(Read,3).c_str()) != atol(same2.c_str())){
			Tmp_u2[atol(Find(Read,3).c_str())].push_back(Read); 
			//sub_Tmp_u2.push_back(Read);
			same2 = Find(Read,3);}
	//		}
		/*if(length - Read.size()-1 <= listPos[distance(listPos.begin(),itPos2)][1]){
		Tmp_u2[atol(same2.c_str())] = sub_Tmp_u2;	
		}*/
        }while(length <=listPos[atol(u1.c_str())][1]);
	map< long int,vector<string> >::iterator it_u1 = Tmp_u1.begin();
	map< long int,vector<string> >::iterator it_u2 = Tmp_u2.begin();
	/*int flag =0;
	for(;it_u1 != Tmp_u1.end();it_u1++){
		if(flag){ 
		Tmp_u3.push_back(Tmp_u2[distance(Tmp_u2.begin(),it_u2)][1]);
		flag = 0;}
		for(;it_u2 != Tmp_u2.end();it_u2++){
		if(atol(Tmp_u1[distance(Tmp_u1.begin(),it_u1)][0].c_str()) == atol(Tmp_u2[distance(Tmp_u2.begin(),it_u2)][0].c_str())) {
			flag = 1;
			string pre = Tmp_u1[distance(Tmp_u1.begin(),it_u1)][0];
			Tmp_u3.push_back(Tmp_u2[distance(Tmp_u2.begin(),it_u2)][1]);
		}}}	*/
	do{
		//if(atol(Tmp_u1[distance(Tmp_u1.begin(),it_u1)][0].c_str()) < atol(Tmp_u2[distance(Tmp_u2.begin(),it_u2)][0].c_str())) it_u1++;
		if(it_u1->first < it_u2->first) it_u1++;
		//else if(atol(Tmp_u1[distance(Tmp_u1.begin(),it_u1)][0].c_str()) > atol(Tmp_u2[distance(Tmp_u2.begin(),it_u2)][0].c_str())) it_u2++;
		else if(it_u1->first > it_u2->first) it_u2++;
		//else if(atol(Tmp_u1[distance(Tmp_u1.begin(),it_u1)][0].c_str()) == atol(Tmp_u2[distance(Tmp_u2.begin(),it_u2)][0].c_str())){
		else if(it_u1->first==it_u2->first){
			/*long int preu1  = it_u1->first;
			long int preu2  = it_u2->first;
			do{	
			if(it_u1->first == preu1){ */
			Tmp_u3.push_back(it_u1->second);
		/*	it_u1 ++;
			}
			else break;}while(it_u1!=Tmp_u1.end());

			do{	
			if(it_u2->first == preu2){*/ 
			Tmp_u3.push_back(it_u2->second);
			/*it_u2++;
			}
			else break;}while(it_u2!=Tmp_u2.end());*/
		/*Tmp_u3.push_back(Tmp_u1[distance(Tmp_u1.begin(),it_u1)][1]);
		Tmp_u3.push_back(Tmp_u2[distance(Tmp_u2.begin(),it_u2)][1]);*/
		it_u1++;it_u2++;
		}
		}while(it_u1 !=Tmp_u1.end()&& it_u2 !=Tmp_u2.end());

	string ss = " ";
	set< pair<long int, string> > b;
	vector<vector<string> >::iterator itOut;// = Tmp_u3.begin();
	vector<string>::iterator itIn;// = itOut->begin();
	for(itOut = Tmp_u3.begin();itOut!=Tmp_u3.end();itOut++){
		for(itIn = itOut->begin();itIn != itOut->end();itIn ++){
		if(atol(Find( *itIn,1).c_str())>=1 ){
                Tmp2[0] = Find( *itIn,3);
		Tmp2[1] = Find(*itIn, 2) + ss +Find(*itIn,4)+ss+Find(*itIn,8)+ss+Find(*itIn,9)+ss+Find(*itIn,10);
                b.insert(pair<long int, string>(atol(Find(*itIn,3).c_str()),Tmp2[1]));	
                }}}	
	
	long int comp;
        cout<<"********************"<<endl;
        for(set< pair<long int, string> >::iterator it = b.begin();it != b.end();it++){
         if(it->first == comp ){
	 cout<<"\t"<<it->second<<endl;
		}
	 else{
	 cout<<it->first<<"\n"<<"\t"<<it->second<<endl;}
	 comp = it->first;
        }
        cout<<"********************"<<endl;
  }		

void BD::profit(string& a,double theta){
	vector<vector<double> > UserId;
	vector<double> sub_UserId(3);
	map <double,double > Out;
	vector<double> sub_out(2);
	double comp = 0.1;
	double clic;
   	double impre;
	double clic_divide_impre;
	for(vector<string>::iterator it = profit_store.begin();it != profit_store.end();it++){
		if(atol(Find(*it,3).c_str())== atol(a.c_str())){
		sub_UserId[0] = atol(Find(*it,11).c_str());
		sub_UserId[1] = atol(Find(*it,0).c_str());
		sub_UserId[2] = atol(Find(*it,1).c_str());
		UserId.push_back(sub_UserId);
	//	UserId.insert(make_pair(Find(*it,11),click_impre));
			}
	}
	for(vector<vector<double> >::iterator it = UserId.begin();it != UserId.end();it++ ){
	if(UserId[distance(UserId.begin(),it)][0] == comp){
	UserId[distance(UserId.begin(),it)][1] += clic;
	UserId[distance(UserId.begin(),it)][2] += impre;
		}
	else if(UserId[distance(UserId.begin(),it)][0] != comp && comp!=0.1 ){ 
	//else if(atol(it->first.c_str()) != atol(comp.c_str()) && comp!="@" ){
		if(clic == 0 && impre == 0)
		clic_divide_impre = 0;
		else	
	 	clic_divide_impre = clic/impre;
		sub_out[0] = comp;
		sub_out[1] = clic_divide_impre;
		//Out[sub_out[0]].push_back(sub_out);
 		Out.insert(make_pair(comp,clic_divide_impre));	
		if(distance(UserId.begin(),it)==UserId.size()-1){
			if(UserId[distance(UserId.begin(),it)][1] == 0 && UserId[distance(UserId.begin(),it)][2]==0) 
			//if(it->second[0] == 0 && it->second[1] == 0)
                	clic_divide_impre = 0;
                	else
			clic_divide_impre = UserId[distance(UserId.begin(),it)][1]/UserId[distance(UserId.begin(),it)][2];
                	//clic_divide_impre = it->second[0]/it->second[1];
                	sub_out[0] = UserId[distance(UserId.begin(),it)][0];
			sub_out[1] = clic_divide_impre;
               	 	//Out.push_back(sub_out);
			Out.insert(make_pair(UserId[distance(UserId.begin(),it)][0],clic_divide_impre));	
			}
		}
	clic = UserId[distance(UserId.begin(),it)][1];
	impre = UserId[distance(UserId.begin(),it)][2];
	comp = UserId[distance(UserId.begin(),it)][0];
		}
	cout<<"********************"<<endl;
	//for(vector<vector<double> >::iterator it = Out.begin(); it != Out.end(); it++ ){
	for(map<double,double >::iterator it = Out.begin(); it != Out.end(); it++ ){
	//if(Out[distance(Out.begin(),it)][1] >= theta){
	if(it->second >= theta){
	//cout<<std::setprecision(0)<<std::fixed<<Out[distance(Out.begin(),it)][0]<<endl;
	cout<<std::setprecision(0)<<std::fixed<< it->first <<endl;
		}
	}
	cout<<"********************"<<endl;
	
	}
int main(int argc,char** argv){
	
   char* File;
   File = argv[1];
   string Filename_(File);

  clock_t start, end;
  string impress,u1,u2;	
  vector<string> a_profit;
  a_profit.assign(22238278,"@");
   
  string ad_id_profit;	
  string theta;
  string get,u,a,q,p,d,prof,click_s,click;
  vector<vector<string> > Clicked,Get,Profit,Impressed;
  vector<string>  Clicked_sub(2),Get_sub(6),Profit_sub(3),Impressed_sub(3);
  
  while(1){
  cin>>click_s;
  if(click_s == "quit") break;
  cin>>click;
  Clicked_sub[0] = click_s;
  Clicked_sub[1] = click;
  Clicked.push_back(Clicked_sub);
  
  cin>>get>>u>>a>>q>>p>>d;
  Get_sub[0] = get;
  Get_sub[1] = u;
  Get_sub[2] = a;
  Get_sub[3] = q;
  Get_sub[4] = p;
  Get_sub[5] = d;
  Get.push_back(Get_sub);
  
  cin>>prof>>ad_id_profit>>theta;
  Profit_sub[0] = prof;
  Profit_sub[1] = ad_id_profit;
  Profit_sub[2] = theta;
  Profit.push_back(Profit_sub);

  cin>>impress>>u1>>u2;
  Impressed_sub[0] = impress;
  Impressed_sub[1] = u1;
  Impressed_sub[2] = u2;
  Impressed.push_back(Impressed_sub);
  }
  //cout<<"Sephiria"<<endl;
  start = clock();
  for(vector<vector<string> >::iterator it = Profit.begin();it != Profit.end();it++){
  	a_profit[atol(Profit[distance(Profit.begin(),it)][1].c_str())] = Profit[distance(Profit.begin(),it)][1];}
  BD Ans(Filename_,a_profit);

  vector<vector<string> >::iterator itCli = Clicked.begin();	  
  vector<vector<string> >::iterator itGet = Get.begin();	  
  vector<vector<string> >::iterator itPro = Profit.begin();	  
  vector<vector<string> >::iterator itImp = Impressed.begin();	  
  for(;itCli != Clicked.end();itCli++,itGet++,itPro++,itImp++){
  	  
  Ans.clicked(Clicked[distance(Clicked.begin(),itCli)][1]);
  Ans.get(Get[distance(Get.begin(),itGet)][1],Get[distance(Get.begin(),itGet)][2],Get[distance(Get.begin(),itGet)][3],Get[distance(Get.begin(),itGet)][4],Get[distance(Get.begin(),itGet)][5]);
  Ans.profit(Profit[distance(Profit.begin(),itPro)][1],atof(theta.c_str()));			
  Ans.impressed(Impressed[distance(Impressed.begin(),itImp)][1],Impressed[distance(Impressed.begin(),itImp)][2]);	
  }
  end = clock();
  cout << "CPU time: " << (float)(end - start)/CLOCKS_PER_SEC << endl;
  return 0;
}
