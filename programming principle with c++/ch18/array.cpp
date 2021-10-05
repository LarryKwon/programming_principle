#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>

using namespace std;

void f(const int arg[], int size){
  int la[10];
  for(int i=0;i<10;i++){
    la[i] = arg[i];
    cout << la[i]<<',';
  }
  cout << '\n';

  int* p = new int[size];
  for(int i = 0; i< size; i++){
    p[i] = arg[i];
    cout << p[i] << ',';
  }
  cout << '\n';
  delete[] p;
}

int factorial(int n){
  if(n==0){
    return 1;
  }
  int sum = 1;
  for(int i = 1; i<=n; i++){
    sum *= i;
  }
  return sum;
}

int main(){
  int ga[10];
  for(int i = 0; i< 10; i ++){
    ga[i] = pow(2,i);
  }
  f(ga,10);
  int aa[10];
  for(int i = 0; i<10; i++){
    aa[i] = factorial(i);
  }
  f(aa,10);
}