#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<vector>

using namespace std;

template<typename T> void f(vector<T>& v1, vector<T>& v2){
  if(v1.size() > v2.size()){
   return ; 
  }

  for(int i = 0; i<v1.size();i++){
    v1[i] += v2[i];
  }
}

template<typename T, typename U>
typename common_type<T,U>::type ff(vector<T>& vt,vector<U>& vu ){
  typename common_type<T,U>::type sum = 0;
  
  for(int i = 0; i<vt.size();i++){
    sum += vt[i] * vu[i];
  }
  return sum;
}

template<class T> ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "{";
    for (int i = 0; i<v.size()-1; ++i)
        os << ' ' << v[i] << ',';
    os << ' ' << v[v.size()-1] << " }";
    return os;
}

int main()
try {
    vector<int> v1;
    for (int i = 0; i<10; ++i)
        v1.push_back(i);
    cout << "v1: " << v1 << "\n";
    vector<double> v2;
    for (int i = 0; i<8; ++i)
        v2.push_back(i*1.6);
    cout << "f(v1,v2): " << ff(v1,v2) << "\n";
}
catch (exception& e) {
    cerr << "Exception: " << e.what() << "\n";
}
catch (...) {
    cerr << "Exception\n";
}
