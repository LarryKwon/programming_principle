#include<cstdlib>
#include<string>
#include<algorithm>
#include<memory>

using namespace std;

namespace vector_raii{
  struct out_of_range{};
}

template<typename T, typename A= allocator<T>>
struct vector_base{
  A alloc;
  int sz;
  int space;
  T* elem;

  vector_base(const A& a, int n)
    : alloc{a},elem{alloc.allocate(n)},sz{n},space{n}{ }
  ~vector_base() { alloc.deallocate(elem,space);}
};

template<typename T, typename A = allocator<T>>
class vector : private vector_base<T,A>{
  public:
    explicit vector(int s)
      : vector_base<T,A>::sz{s}, vector_base<T,A>::elem{new T[s]},vector_base<T,A>::space{s}
      {
        for(int i =0; i<s; ++i) vector_base<T,A>::elem[i] = 0;
      }

    vector(initializer_list<T>lst)
      :vector_base<T,A>::sz{lst.size()},vector_base<T,A>::elem{new T[vector_base<T,A>::sz]}{
        copy(lst.begin(),lst.end(),vector_base<T,A>::elem);
      }
    
    vector():vector_base<T,A>::sz{0},vector_base<T,A>::elem{nullptr},vector_base<T,A>::space{0}{ }

    vector(const vector &);

    vector& operator=(const vector &);

    vector( vector &&);
    vector& operator=(vector &&);
    ~vector(){delete[] vector_base<T,A>::elem;}

    T& at(int n);
    const T& at(int n) const;

    T& operator[ ](int n){return & vector_base<T,A>::elem[n];}
    const T& operator[ ](int n) const{return vector_base<T,A>::elem[n];}

    int size() const{return vector_base<T,A>::sz;}
    int capacity() const{return vector_base<T,A>::space;}

    void reserve(int newalloc);
    void resize(int newsize,T& def = T());
    void push_back(const T& d);
};

template<typename T,typename A> vector<T,A>::vector(const vector<T,A>& arg)
:vector_base<T,A>::sz{arg.sz},vector_base<T,A>::elem{new double[arg.sz]}
{
  copy(arg.elem,arg.elem+arg.sz,this->elem);
}

template<typename T,typename A> vector<T,A>::vector(vector<T,A>&& a)
:vector_base<T,A>::sz{a.sz},vector_base<T,A>::elem{a.elem}{
  a.sz = 0;
  a.elem = nullptr;
}

template<typename T, typename A> vector<T,A>& vector<T,A>::operator=(const vector<T,A>& a){
  
  if(this == &a) return *this;
  if(a.sz <= this->space){
    for(int i=0; i<a.sz;++i) this->elem[i] = a.elem[i];
    this->sz = a.sz;
    return *this;
  }
  
  double * p = new double[a.sz];
  for(int i = 0; i<a.sz; ++i) p[i] = a.elem[i];
  delete[] this->elem;
  this->space = this->sz = a.sz;
  this->elem = p;
  return *this;
}

template<typename T, typename A> vector<T,A>& vector<T,A>::operator=(vector<T,A>&& a){
  delete[] this->elem;
  this->elem = a.elem;
  this->sz = a.sz;
  a.elem = nullptr;
  a.sz = 0;
  return *this;
}

template<typename T,typename A> void vector<T,A>::reserve(int newalloc){
  if(newalloc <= this->space) return;
  T *p = this->alloc.allocate(newalloc);
  for(int i = 0; i < this->sz; i++) this->alloc.construct(&p[i],this->elem[i]);
  for(int i = 0; i < this->sz; i++) this->alloc.destroy(&this->elem[i]);
  this->elem = p;
  this->space = newalloc;
}

template<typename T,typename A> void vector<T,A>::resize(int newsize,T& val){
  reserve(newsize);
  for(int i=this->sz;i<newsize;++i) this->alloc.construct(&this->elem[i],val);
  for(int i=this->sz;i<newsize;++i) this->alloc.destroy(&this->elem[i]);
  this->sz = newsize;
}

template<typename T,typename A> void vector<T,A>::push_back(const T& val){
  if(this->space == 0) reserve(8);
  else if(this->sz == this->space) reserve(2*this->space);
  this->alloc.consruct(&this->elem[this->sz],val);
  ++this->sz;
}

template<typename T,typename A> T& vector<T,A>::at(int n){
  if(n < 0 || this->sz <= n) throw vector_raii::out_of_range();
  return this->elem[n];
}



int main(){

  return 0;
}