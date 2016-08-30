#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <ctime>
#include <time.h>
#include <map>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;

#define MAX_FEATURE (1024+1)

#ifndef TREE_H
#define TREE_H

class tree{
  public:
    tree();
    tree(char*, const double);
    void output();
    void decisionTree();
    void decisionTree(std::vector< std::vector<double> >& input, const int go = 0);
    bool continu(const std::vector< std::vector<double> >& input);
  private:
    double eps;
    std::vector<std::vector<double> > variables;
    std::vector<std::string> store;
};

#endif


tree::tree(){}

tree::tree( char* Filename, const double eps){
 
  int total = 0;
  double* features = new double[MAX_FEATURE];
  std::ifstream fin(Filename, ios::in);
  string istring;
  vector<double> label;
  size_t max = 0;
  size_t max_pre = 0;
  while (std::getline(fin, istring)) {
    total++;
    char *cstring, *tmp;
    memset(features, 0, sizeof(double) * MAX_FEATURE);
    cstring = new char[istring.size() + 1];
    strncpy(cstring, istring.c_str(), istring.size()+1);
    tmp =  strtok(cstring, ": ");
    label.push_back(atoi(tmp));
    tmp = strtok(NULL, ": ");
    size_t size = 0;
    while(tmp != NULL) {
      int id = atoi(tmp);
      tmp = strtok(NULL, ": ");
      features[id-1] = atof(tmp);
      size = id;
      tmp = strtok(NULL, ": ");
    }
     max_pre = size;	
    if(max_pre > max)
     max = max_pre;
    
    vector<double> sub;
    sub.assign(features, features+size);
    variables.push_back(sub);
    delete[] cstring;
  }
  size_t subsize = 0;
  for(size_t i = 0; i < variables.size(); i++){
    subsize = variables[i].size();
    if(subsize != max){
      for(size_t j = 0; j < max-subsize; j++)
        variables[i].push_back(0);
    }
    variables[i].push_back(label[i]);
  }
}

bool tree::continu(const vector< vector<double> >& input){
  for(int i = 0; i < input.size()-1; i++){
    vector<double> first = input[i];
    vector<double> second = input[i+1];
    first.pop_back();
    second.pop_back();
    if(first != second)
      return true;
  }
  return false;
}


struct myclass{
  friend void swap(vector<double>& v1, vector<double>& v2){
    vector<double> tmp = v1;
    v1 = v2;
    v2 = tmp;
  }
  size_t pos;
  bool operator()(vector<double>& v1, vector<double>& v2){ return v1[pos] > v2[pos]; };
}myclass;

void tree::decisionTree(){
  decisionTree(variables);
  output();
}

void tree::decisionTree(vector< vector<double> >& input, const int go){
  if(go == 1)
    store.push_back("Left");
  else if(go == 2)
    store.push_back("Right");
  double Y = 0;
  double N = 0;
  for(int i = 0; i < input.size(); i++){
    if(input[i].back() == 1)
      Y++;
    else
      N++;
  }
  double confusion = 1.0-pow(Y/(Y+N),2)-pow(N/(Y+N),2);
 
  if( confusion <= eps || !(continu(input))){
    if(Y > N)
      store.push_back("Y");
    else
      store.push_back("N");
  }
  else{
    vector<double> minsinfo(3);  
    vector< vector<double> > Store_list;
    for(int i = 0; i < input[0].size()-1; i++){
      double min = 2;
      double total_con = 2;
      double YLeft = 0;
      double NLeft = 0;
      minsinfo[0] = min;
      minsinfo[1] = -1;
      minsinfo[2] = -1;
      sort(input.begin(), input.end(), myclass = {i} );
      for(int j = 0; j < input.size(); j++){
        if(input[j].back() == 1)
          YLeft++;
        else
          NLeft++;
        while( j != input.size()-1 && input[j][i] == input[j+1][i]){
          j++;
          if(input[j].back() == 1)
            YLeft++;
          else
            NLeft++;
        }
        if(j != input.size()-1){
		
   total_con = ( ( YLeft + NLeft) / (YLeft +NLeft + (Y - YLeft) + (N - NLeft))) * ( 1.0-pow(YLeft/(YLeft+NLeft),2)-pow(NLeft/(YLeft+NLeft),2) ) + (((Y - YLeft) + (N - NLeft) )/(YLeft + NLeft +(Y - YLeft) + (N - NLeft))) * ( 1.0-pow( (Y - YLeft) / ( (Y - YLeft)+ (N - NLeft)),2)-pow( (N - NLeft) /( (Y - YLeft) + (N - NLeft)),2));
          if(total_con < min){
            min = total_con;
            minsinfo[0] = min;
            minsinfo[1] = j;  //
            minsinfo[2] = (input[j][i]+input[j+1][i]) / 2.0; 
          }
        }
      }
      Store_list.push_back(minsinfo);
    }
    double conf_low = 1;
    size_t headcol = 0;
    for(int k = 0; k < Store_list.size(); k++){
      if(Store_list[k][0] < conf_low){
        conf_low = Store_list[k][0];
        headcol = k;
      }
    }
    sort(input.begin(), input.end(), myclass = {headcol} );
    char buf[512];
    string buffer;
    sprintf(buf, "%ld", headcol);
    buffer.assign(buf);
    store.push_back(buffer);
    sprintf(buf, "%f", Store_list[headcol][2]);
    buffer.assign(buf);
    store.push_back(buffer);

    vector< vector<double> > Left(input.begin(), input.begin()+Store_list[headcol][1]+1);
    decisionTree(Left, 1);
    vector< vector<double> > right(input.begin()+Store_list[headcol][1]+1, input.end());
    decisionTree(right, 2);
    store.push_back("Z");
  }
}

void tree::output(){
  FILE *fout = fopen("tree_pred_func.cpp", "w");
  fprintf(fout, "int tree_predict(double *attr){\n");
  for(int i = 0; i < store.size(); i++){
    if(store[i] == "Left"){
	
      size_t pos = atol(store[i-2].c_str());
      fprintf(fout, "if(attr[%ld] > %s ){ \n", pos+1, store[i-1].c_str());
    }
    else if(store[i] == "Right"){
      fprintf(fout, "}else{ \n");
    }
    else if(store[i] == "Y"){
      fprintf(fout, "return 1; \n");
    }
    else if(store[i] == "N"){
      fprintf(fout, "return -1; \n");
    }
    else if(store[i] == "Z"){
      fprintf(fout, "}\n");
    }
  }
  fprintf(fout, "}\n");
  store.clear();
  fclose(fout);
}


int main(int argc, char** argv){

  double eps = atof(argv[2]);
  tree Run(argv[1], eps);
  Run.decisionTree();
  return 0;
}
