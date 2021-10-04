#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>

using namespace std;

class vector{
  int sz;
  double* elem;

  public:
    vector(int s)
      :sz{s},
      elem{new double[s]}{
        for(int i =0; i<s; ++i) elem[i] = 0;
      }

    vector(initializer_list<double>lst)
      :sz{(int)lst.size()},elem{new double[sz]}{
        copy(lst.begin(),lst.end(),elem);
      }

    vector(const vector &);

    vector& operator=(const vector &);

    vector( vector &&);
    vector& operator=(vector &&);
    ~vector(){delete[] elem;}

    double* operator[ ](int n){return &elem[n];}
    double operator[ ](int n) const{return elem[n];}

    int size() const{return sz;}
    double get(int n) const { return elem[n]; }
    void set(int n, double v) { elem[n] = v; }
};

vector::vector(const vector& arg)
:sz{arg.sz},elem{new double[arg.sz]}
{
  copy(arg.elem,arg.elem+arg.sz,elem);
}

vector& vector::operator=(const vector& a){
  double * p = new double[a.sz];
  copy(a.elem, a.elem+a.sz,p);
  delete[] elem;
  elem = p;
  sz = a.sz;
  return *this;
}

vector::vector(vector&& a)
:sz{a.sz},elem{a.elem}{
  a.sz = 0;
  a.elem = nullptr;
}

vector& vector::operator=(vector&& a){
  delete[] elem;
  elem = a.elem;
  sz = a.sz;
  a.elem = nullptr;
  a.sz = 0;
  return *this;
}

// int main(){

//   return 0;
// }