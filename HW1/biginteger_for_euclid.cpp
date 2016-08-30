#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "biginteger_for_euclid.h"
using namespace std;
BigInteger::BigInteger(){
	VecS.push_back(0); 
	int ass;
}
BigInteger::BigInteger(const int& Right){
	int size;
	size=log(Right); size/=3;
	VecS.assign(size+1,0);
	for (int i=size;i>=0;i--){
		VecS[i]=Right/pow(1000,i);
	}		
}

BigInteger::BigInteger(const std::string& a){
	int length = a.size();
	 ass = length/3;
	int mod;
	if(length%3!=0) {
		ass+=1;
		mod = length%3;
	}
	VecS.assign(ass,0);
	int j=0;
	for(int i=length;i>=0;i-=3){
		if((i-2)<=0){
			string a_s=a.substr(0,mod);
			int a_n = atoi(a_s.c_str());	
	        VecS[j] = a_n;
	        j++;
	        if (j==(ass)) break; 
		}
		else{
		string a_s=a.substr(i-3,3);
		int a_n = atoi(a_s.c_str());
	     VecS[j] = a_n ;
		 j++;
		 if (j==(ass)) break;
		 } 
	}
}

BigInteger::BigInteger(const BigInteger& right){
		this->VecS=right.VecS;
		this->ass=right.ass;
  }
BigInteger::~BigInteger(){	
}
const BigInteger& BigInteger::operator*=(const BigInteger& right){
  BigInteger left = *this;
  if((right.VecS[right.VecS.size()-1] * left.VecS[left.VecS.size()-1]) / 1000 == 0 )
    this->VecS.assign(right.VecS.size()+left.VecS.size() - 1, 0);
  else
    this->VecS.assign(right.VecS.size()+left.VecS.size(), 0);
  for(int i = 0; i < left.VecS.size(); i++){
    for(int j = 0; j < right.VecS.size(); j++){
      this->VecS[i+j] += right.VecS[j]*left.VecS[i];
      if(this->VecS[i+j] / 1000 != 0 ){
        VecS[i+j+1] += VecS[i+j] /1000;
        VecS[i+j] = VecS[i+j] % 1000;
      }
    }  
	}
  return *this;
}
const BigInteger& BigInteger::Resize(){
 int buf = VecS.size();
  for(int i = 0; i < buf-1; i++){
    if(VecS[VecS.size()-1] != 0)
      break;
    else
      this->VecS.resize(VecS.size()-1);
  }
  return *this;
}
bool BigInteger::operator<=(const BigInteger& right) const{
return (*this < right || *this == right);
}
bool BigInteger::operator<(const BigInteger& right) const{
  if(VecS.size() > right.VecS.size())
    return false;
  if(VecS.size() < right.VecS.size())
    return true;
  if(VecS.size() == right.VecS.size()){
     for(int i = 0; i < VecS.size(); i++){
        if(VecS[VecS.size()-1-i] < right.VecS[VecS.size()-1-i]){
          return true;
        }
        if(VecS[VecS.size()-1-i] > right.VecS[VecS.size()-1-i]){
          return false;
        }
     }
  }
  return false;
}

bool BigInteger::operator==(const BigInteger& right)const{
   if(right.VecS.size() != VecS.size())
    return false;
  for(int i = 0; i < VecS.size(); i++){
    if(right.VecS[i] != VecS[i])
      return false;
  }
  return true;
}

bool BigInteger::operator==(const int& right) const{
  BigInteger Right(right);
  return (*this == Right);
}
bool BigInteger::iseven()const{
  	if (VecS[0]%2==0)
	  return true;
  	else return false;
  }
  BigInteger& BigInteger::operator/=(int I){
  int R=0;
  for(int i = this->VecS.size()-1; i >= 0; i--){
    R = this->VecS[i] + R*1000;
    VecS[i] = R/I;
    R %= I;
  }
  this->Resize();
  return *this;
}
BigInteger& BigInteger::operator-=(const BigInteger& right){
  for(int i = 0; i < VecS.size(); i++){
    if(i < right.VecS.size()){
      if((VecS[i]-right.VecS[i]) < 0){
        VecS[i] += (1000 - right.VecS[i]);
        VecS[i+1] -= 1;
      }
      else{
        VecS[i] -= right.VecS[i];}
    }
    else
      if(VecS[i]< 0){
        VecS[i] += 1000;
        VecS[i+1] -= 1;
      }
  }
  this->Resize();
  return *this;
}
const BigInteger BigInteger::operator-(const BigInteger& right) const{
  BigInteger Left = *this;
  Left -= right;
  return Left;
}  
const BigInteger BigInteger::operator%(const BigInteger& right)const{
/*	if(right == 2){
    if(iseven())
      return 0;
    else
      return 1;
  }*/
  BigInteger Right(right);
  BigInteger left(*this);
  if(left < Right)
    return left;
int sizeR,sizeL;
for(sizeR=right.VecS.size()-1;sizeR>=0;sizeR--){
	if(VecS[sizeR]!=0) break;
	}
for(sizeL=VecS.size()-1;sizeL>=0;sizeL--){
	if(VecS[sizeL]!=0) break;
	}	
string Add = "1";
for(int i = 0; i < 3*(sizeL-sizeR); i++){
  	Add.push_back(0);	
  }
BigInteger power(Add);
  Right *= power;
  for(int i = 0; i < 3; i++){
    if(Right <= left){
      break;
    }
    else Right /= 10;
  }
while( right <= Right){
    while(!(left < Right)){
    left -= Right;
	}
    if(left < right){
      break;}
    Right /= 10;
  }
  left.Resize();
  return left;
}

std::ostream& operator<<(std::ostream& output, const BigInteger& A){
	 int ass = A.VecS.size();
	 output<<A.VecS[ass-1]<<"";
	for (int i=ass-2;i>=0;i--){
	  if(A.VecS[i]<1000&&A.VecS[i]>=100){
	  	output<<A.VecS[i]<<"";
	  }
	  if(A.VecS[i]<100&&A.VecS[i]>=10){
	  	output<<"0"<<A.VecS[i]<<"";
	  }
	  if(A.VecS[i]<10&&A.VecS[i]>=1){
	  	output<<"00"<<A.VecS[i]<<"";
	  }
	  if(A.VecS[i]==0){
	  	output<<"00"<<A.VecS[i]<<"";
	  }
		}
	return output;
	}

 BigInteger& BigInteger::operator=(const BigInteger& right){
	if (this == &right) return *this;
	if (this != &right) {
		this->VecS=right.VecS;
		this->ass=right.ass;
	}
	return *this;
  }
bool BigInteger::iszero()const{
	for(vector<int>::const_iterator it = this->VecS.begin(); it != this->VecS.end(); ++it)
		if(*it != 0)
			return false;
	return true;
  	}
  	
