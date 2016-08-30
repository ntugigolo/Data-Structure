#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "biginteger_for_binary.h"
using namespace std;
BigInteger::BigInteger(){
	VecS.push_back(0);
	ass=4;
}
BigInteger::BigInteger(const int& Right){
	int size;
	size=log(Right); size/=4;
	VecS.assign(size+1,0);
	for (int i=size;i>=0;i--){
		VecS[i]=Right/pow(10000,i);
	}
}
BigInteger::BigInteger(const std::string& a){
	int length = a.size();
	 ass = length/4;
	int mod;
	if(length%4!=0) {
		this->ass+=1;
		mod = length%4;
	}
	this->VecS.assign(ass,0);
	int j=0;
	for(int i=length;i>=0;i-=4){
		if((i-3)<=0){
			string a_s=a.substr(0,mod);
			int a_n = atoi(a_s.c_str());
	        VecS[j] = a_n;
	        j++;
		}
		else{
		string a_s=a.substr(i-4,4);
		int a_n = atoi(a_s.c_str());
	     VecS[j] = a_n ;
		 j++;
		 }
	}
}
BigInteger::BigInteger(const BigInteger& right){
		VecS=right.VecS;
		ass=right.ass;
  }
BigInteger::~BigInteger(){
}
const BigInteger& BigInteger::Resize(){
  int size = VecS.size();
  for(int i = 0; i < size-1; i++){
    if(VecS[VecS.size()-1] != 0){
	 break;}
    else
      this->VecS.resize(VecS.size()-1);
  }
  return *this;
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
BigInteger& BigInteger::operator-=(const BigInteger& right){
	for(int i = 0; i < VecS.size(); i++){
    if(i < right.VecS.size()){
      if((VecS[i]-right.VecS[i]) < 0){
        VecS[i] += (10000 - right.VecS[i]);
        VecS[i+1] -= 1;
      }
      else
        VecS[i] -= right.VecS[i];
    }
    else
      if(VecS[i]< 0){
        VecS[i] += 10000;
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
  const BigInteger& BigInteger::operator*=(const BigInteger& right){
  	BigInteger left = *this;
	if((right.VecS[right.VecS.size()-1] * left.VecS[left.VecS.size()-1]) / 10000 == 0 )
    	this->VecS.assign(right.VecS.size()+left.VecS.size() - 1, 0);
  	else
    	this->VecS.assign(right.VecS.size()+left.VecS.size(), 0);
  	for(int i = 0; i < left.VecS.size(); i++){
  		for(int j = 0; j < right.VecS.size(); j++){
      		this->VecS[i+j] += right.VecS[j]*left.VecS[i];
      		if(this->VecS[i+j] / 10000 != 0 ){
        		VecS[i+j+1] += VecS[i+j] /10000;
        		VecS[i+j] = VecS[i+j] % 10000;
      		}
    	}
	}
  return *this;
}

BigInteger BigInteger::operator*(const BigInteger& right) {
  BigInteger Left = *this;
  Left *= right;
  return Left;
}
BigInteger& BigInteger::operator*=(const int I){
  BigInteger Right(I);
  *this *= Right;
  return *this;
}

BigInteger& BigInteger::operator/=(int I){
	int R=0;
		for(int i = this->VecS.size()-1; i >= 0; i--){
      	 R = this->VecS[i] + R*10000;
      	 VecS[i] = R/I;
      	 R %= I;
    	}
    	this->Resize();
  return *this;
}
std::ostream& operator<<(std::ostream& output, const BigInteger& A){
	 int ass = A.VecS.size();
	 output<<A.VecS[ass-1]<<",";
	for (int i=ass-2;i>=0;i--){
	  if(A.VecS[i]<1000&&A.VecS[i]>=100){
	  	output<<"0"<<A.VecS[i]<<",";
	  }
	  if(A.VecS[i]<100&&A.VecS[i]>=10){
	  	output<<"00"<<A.VecS[i]<<",";
	  }
	  if(A.VecS[i]<10&&A.VecS[i]>=1){
	  	output<<"000"<<A.VecS[i]<<",";
	  }
	  if(A.VecS[i]==0){
	  	output<<"000"<<A.VecS[i]<<",";
	  }
	  else if(A.VecS[i]>=1000){
	    output<<A.VecS[i]<<",";
	  }
		}
	return output;
	}

 BigInteger& BigInteger::operator=(const BigInteger& right){
	if (this == &right) return *this;
	if (this != &right) {
		VecS=right.VecS;
		ass=right.ass;
	}
	return *this;
  }
bool BigInteger::iseven(){
  	if (this->VecS[0]%2==0)
	  return true;
  	else return false;
  }
bool BigInteger::iszero(){
  	int i = ass-1;
	while(i>=0){
	   if(this->VecS[i]==0)	i--;
		else if(this->VecS[i]!=0){
			return false;
		}
	}
		return true;
  	}

BigInteger gcd_by_binary(const BigInteger& a, BigInteger& b){
  BigInteger n, m;
  BigInteger ans(1);
  if (a < b){
    n = a; m = b;
  }
  else{
    n = b; m = a;
  }
  while(!n.iszero() && !m.iszero()){
    if (n.iseven()){
      if (m.iseven()){
        ans *= 2;
        n /= 2;
        m /= 2;
      }
      else{
        n /= 2;
      }
    }
    else if (m.iseven()){
	  m /= 2;
    }
    if (m<n){
      BigInteger tmp;
      tmp = n; n = m; m = tmp;
    }
    m = m - n;
  }
  return (n * ans);
}

int main(){
  string sa, sb;
  cout<<"Input two big integer :";
  cin >> sa >> sb;
  BigInteger a(sa), b(sb);

  cout <<"GCD:"<< gcd_by_binary(a, b) << endl;
  return 0;
}
