#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>

using namespace std;

struct Int{
  int number;

  Int()
  :number{0}{}

  Int(int n)
  :number{n}{}

  Int(Int& v)
  :number{v.number}{}

  Int& operator=(const Int& v);
  Int& operator+(const Int& v);
  Int& operator-(const Int& v);
  Int& operator/(const Int& v);
  Int& operator*(const Int& v);
  int get() const { return number; }
};

Int& Int::operator=(const Int& v){
  this->number = v.number;
  return *this; 
}

Int& Int::operator+(const Int& v){
  this->number += v.number;
  return *this;
}

Int& Int::operator-(const Int& v){
  this->number -= v.number;
  return *this;
}

Int& Int::operator/(const Int& v){
  this->number /= v.number;
  return *this;
}
Int& Int::operator*(const Int& v){
  this->number *= v.number;
  return *this;
}

ostream& operator<<(ostream& os, const Int& d)
{
    os << d.get();
    return os;
}

int main()
try {
    Int i1;
    Int i2 = 2;
    Int i3(i2);
    Int i4;
    i4 = i2;
    Int i5 = 6;
    cout << "i1 (default constructed): " << i1 << "\n";
    cout << "i2 (constructed with argument): " << i2 << "\n";
    cout << "i3 (copy constructed from i2): " << i3 << "\n";
    cout << "i4 (copy assigned  from i2): " << i4 << "\n";
    cout << "i5 (constructed with argument): " << i5 << "\n";
    cout << "i2 + i5 = " << i2+i5 << "\n";
    cout << "i5 - i2 = " << i5-i2 << "\n";
    cout << "i2 * i5 = " << i2*i5 << "\n";
    cout << "i5 / i2 = " << i5/i2 << "\n";
}
catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
catch (...) {
    cerr << "exception\n";
}