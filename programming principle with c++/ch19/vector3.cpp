#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>

using namespace std;

class vector{
  int sz;
  double* elem;
  int space;

  public:
    explicit vector(int s)
      :sz{s}, elem{new double[s]},space{s}
      {
        for(int i =0; i<s; ++i) elem[i] = 0;
      }

    vector(initializer_list<double>lst)
      :sz{lst.size()},elem{new double[sz]}{
        copy(lst.begin(),lst.end(),elem);
      }
    
    vector():sz{0},elem{nullptr},space{0}{ }

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

    void reserve(int newalloc);
    int capacity() const{return space;}
    void resize(int newsize);
    void push_back(double d);
};

vector::vector(const vector& arg)
:sz{arg.sz},elem{new double[arg.sz]}
{
  copy(arg.elem,arg.elem+arg.sz,elem);
}

vector& vector::operator=(const vector& a){
  
  if(this == &a) return *this;
  if(a.sz <= space){
    for(int i=0; i<a.sz;++i) elem[i] = a.elem[i];
    sz = a.sz;
    return *this;
  }
  
  double * p = new double[a.sz];
  for(int i = 0; i<a.sz; ++i) p[i] = a.elem[i];
  delete[] elem;
  space = sz = a.sz;
  elem = p;
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

void vector::reserve(int newalloc){
  if(newalloc <= space) return;
  double *p = new double[newalloc];
  for(int i = 0; i < sz; i++){
    p[i] = elem[i];
  }
  delete elem;
  elem = p;
  space = newalloc;
}

void vector::resize(int newsize){
  reserve(newsize);
  for(int i=sz;i<newsize;++i) elem[i] = 0;
  sz = newsize;
}

void vector::push_back(double d){
  if(space == 0) reserve(8);
  else if(sz == space) reserve(2*space);
  elem[sz] = d;
  ++sz;
}



int main(){

  return 0;
}