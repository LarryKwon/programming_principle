#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<limits>
#include<ctime>

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

    ~vector(){delete[] elem;}

    int size() const{return sz;}
    double get(int n) const { return elem[n]; }
    void set(int n, double v) { elem[n] = v; }
};

// int main(){
//   vector v(5);
//   for(int i = 0; i<v.size(); i++){
//     v.set(i,1.1*i);
//     cout << "v[" << i << "]==" << v.get(i) << '\n';
//   }
// }