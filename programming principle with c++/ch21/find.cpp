#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<memory>
#include<list>

using namespace std;

namespace ch21{
template<typename In, typename T>
In find(In first, In last, const T& val){
  while(first!=last && *first!=val) ++ first;
  return first;
}

template<typename In, typename Pred>
In find_if(In first, In last, Pred pred){
  while(first!=last && !(pred(*first)))++first;
  return first;
}

//functor

class Larger_than{
  int v;
  public:
    Larger_than(int vv): v(vv) { }
    bool operator()(int x) const { return x>v; }
};

//lamda
void f(list<double>& v, int x){
  auto p = ch21::find_if(v.begin(),v.end(),[x](double a){return a>x;});
}

template<typename In, typename T>
T accumulate(In first, In last, T init){
  while(first != last){
    init += *first;
    ++first;
  }
  return init;
}

template<typename In, typename In2, typename T, typename BinOp, typename BinOp2>
T inner_product(In first, In last, In2 first2, T init, BinOp p, BinOp2 op2){
  while(first!=last){
    init = op(init,op2(*first, *first2));
    ++first;
    ++first2;
  }
  return init;
}

template<typename In, typename Out>
Out copy(In first, In last, Out res){
  while(first!=last){
    *res = *first;
    ++res;
    ++first;
  }
  return res;
}

template<typename In, typename Out, typename Pred>
Out copy_if(In first, In last, Out res, Pred pred){
  while(first!=last){
    if(pred(*first)) *res++ = *first;
    ++first;
  }
  return res;
}

struct No_case{
  bool operator()(const string& x, const string& y) const{
    for( int i =0; i<x.length();++i){
      if(i==y.length()) return false;
      char xx = tolower(x[i]);
      char yy = tolower(y[i]);
      if(xx<yy) return true;
      if(yy<xx) return false;
    }
    if(x.length() == y.length()) return false;
    return true;
  }
};

}