#include<iostream>
#include<cstdlib>
#include<string>
#include <cmath>
#include<algorithm>
#include<vector>

using namespace std;

void print_array10(ostream& os, int* a){
  for(int i = 0; i<10; i++){
    os << a[i]<<'\n';
  }
}

void print_array(ostream& os, int* a, int n){
  for(int i=0; i<n; i++){
    os << a[i] << '\n';
  }
}

// int main(){
//   int size = 20;
//   int init= 100;
//   int* a = new int[size];
//   for(int i = 0; i< size; i++){
//     a[i] = init;
//     init ++;
//   }
//   print_array10(cout, a);
//   delete[] a;
// }

template<typename T>
void print_vector(ostream& os, vector<T>v){
  for(auto p:v){
    cout << p << '\n';
  }
}

// int main(){
//   vector<int> v;
//   int size = 20;
//   int init = 100;
//   for(int i = 0;i<size;i++){
//     v.push_back(init);
//     init++;
//   }

//   print_vector(cout, v);
// }

//part2
// int main(){

//   int* p1 = new int(7);
//   cout << p1 <<' ' << *p1 << '\n';
//   int* p2 = new int[7];
//   for(int i = 0; i<7;i++){
//     p2[i] = pow(2,i);
//   }
//   print_array(cout, p2, 7);

//   int* p3 = p2;
//   p2 = p1;
//   p2 = p3;
//   cout << p2 << '\n';
//   delete[] p2;
//   delete p1;

// }
