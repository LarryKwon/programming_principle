#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>

using namespace std;

template<typename T, int N> struct array{
  T elem[N];

  T& operator[ ] (int n);
  const T& operator[ ](int n) const;
  T* data(){return elem;}
  const T* data() const {return elem;}

  int size() const{return N;}
};

template<class T, int N> void fill(array<T,N>& b, const T& val){
  for(int i = 0; i<N; i++) b[i] = val;
}

template<typename C> void printout(const C& c){
  for(int i = 0; i<c.size();++i) cout << c[i] << '\n';
}

int main(){
  array<int,256> gb;
  array<double,6> ad = {0.0,1.1,2.2,3.3,4.4,5.5};
  const int max = 1024;

}