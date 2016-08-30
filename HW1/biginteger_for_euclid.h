#include <iostream>
#include <list>
#include <cstring>
#include <vector>

#ifndef BIGINTEGER_FOR_EUCLID
#define BIGINTEGER_FOR_EUCLID
using namespace std;
class BigInteger{
public:
  BigInteger();
  BigInteger(const int&);
  BigInteger(const std::string&);
  BigInteger(const BigInteger&);
  ~BigInteger();
  
  const BigInteger& Resize();
  bool operator<(const BigInteger&) const;
  bool operator<=(const BigInteger&) const;
  BigInteger& operator/=(int);
  const BigInteger operator-(const BigInteger&) const;
  const BigInteger& operator*=(const BigInteger&);
  const BigInteger operator%(const BigInteger&)const;
  BigInteger& operator=(const BigInteger&);
  BigInteger& operator-=(const BigInteger&);
  bool operator==(const BigInteger&)const;
  bool operator==(const int&) const;
  bool iszero()const;
  bool iseven()const;

  friend std::ostream& operator<<(std::ostream&, const BigInteger&);
  
private:
	std::vector<int> VecS; 
	int ass;
	void eraseZero();

};


#endif
