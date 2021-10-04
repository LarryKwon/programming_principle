#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<memory>

using namespace std;

namespace vector_template{
  struct out_of_range{};
}

template<typename T, typename A = allocator<T>>
class vector{
  A alloc;
  int sz;
  T* elem;
  int space;

  public:
    explicit vector(int s)
      :sz{s}, elem{new T[s]},space{s}
      {
        for(int i =0; i<s; ++i) elem[i] = 0;
      }

    vector(initializer_list<T>lst)
      :sz{lst.size()},elem{new T[sz]}{
        copy(lst.begin(),lst.end(),elem);
      }
    
    vector():sz{0},elem{nullptr},space{0}{ }

    vector(const vector &);

    vector& operator=(const vector &);

    vector( vector &&);
    vector& operator=(vector &&);
    ~vector(){delete[] elem;}

    T& at(int n);
    const T& at(int n) const;

    T& operator[ ](int n){return &elem[n];}
    const T& operator[ ](int n) const{return elem[n];}

    int size() const{return sz;}
    int capacity() const{return space;}

    void reserve(int newalloc);
    void resize(int newsize,T& def = T());
    void push_back(const T& d);
};

template<typename T,typename A> vector<T,A>::vector(const vector<T,A>& arg)
:sz{arg.sz},elem{new double[arg.sz]}
{
  copy(arg.elem,arg.elem+arg.sz,elem);
}

template<typename T,typename A> vector<T,A>::vector(vector<T,A>&& a)
:sz{a.sz},elem{a.elem}{
  a.sz = 0;
  a.elem = nullptr;
}

template<typename T, typename A> vector<T,A>& vector<T,A>::operator=(const vector<T,A>& a){
  
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

template<typename T, typename A> vector<T,A>& vector<T,A>::operator=(vector<T,A>&& a){
  delete[] elem;
  elem = a.elem;
  sz = a.sz;
  a.elem = nullptr;
  a.sz = 0;
  return *this;
}

template<typename T,typename A> void vector<T,A>::reserve(int newalloc){
  if(newalloc <= space) return;
  T *p = alloc.allocate(newalloc);
  for(int i = 0; i < sz; i++) alloc.construct(&p[i],elem[i]);
  for(int i = 0; i < sz; i++) alloc.destroy(&elem[i]);
  elem = p;
  space = newalloc;
}

template<typename T,typename A> void vector<T,A>::resize(int newsize,T& val){
  reserve(newsize);
  for(int i=sz;i<newsize;++i) alloc.construct(&elem[i],val);
  for(int i=sz;i<newsize;++i) alloc.destroy(&elem[i]);
  sz = newsize;
}

template<typename T,typename A> void vector<T,A>::push_back(const T& val){
  if(space == 0) reserve(8);
  else if(sz == space) reserve(2*space);
  alloc.consruct(&elem[sz],val);
  ++sz;
}

template<typename T,typename A> T& vector<T,A>::at(int n){
  if(n < 0 || sz <= n) throw vector_template:: out_of_range();
  return elem[n];
}



// int main(){

//   return 0;
// }