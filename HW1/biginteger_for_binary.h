
#ifndef BIGINTEGER_FOR_BINARY
#define BIGINTEGER_FOR_BINARY
#include <iostream>
#include <vector>

class BigInteger{
public:
  BigInteger();
  BigInteger(const int&);
  BigInteger(const std::string&);
  BigInteger(const BigInteger&);
  ~BigInteger();
 
  const BigInteger& Resize();	
  bool operator<(const BigInteger&) const;
  const BigInteger operator-(const BigInteger&) const;
  const BigInteger operator*(const BigInteger&) const;
const BigInteger& operator*=(const BigInteger&); 
   BigInteger operator<<(const BigInteger&) ;
  BigInteger operator*(const BigInteger& );
  BigInteger& operator*=(const int);
  BigInteger& operator/=(int);
  BigInteger& operator=(const BigInteger&);
  BigInteger& operator-=(const BigInteger&);
  bool iseven();
  bool iszero();


  friend std::ostream& operator<<(std::ostream&, const BigInteger&);

private:
	std::vector<int> VecS; 
	int ass;

};


#endif
