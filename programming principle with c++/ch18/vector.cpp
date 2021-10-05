#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

void f(vector<int>& gv){
  vector<int> lv (gv.size());
  lv = gv;
  for(auto p:lv){
    cout << p << ',';
  }
  cout << '\n';

  vector<int>lv2(gv);

  for(auto p:lv2){
    cout << p << ',';
  }
  cout << '\n';
}

int main(){
  vector<int> gv(10);
  for(int i = 0; i<gv.size(); i++){
    gv[i] = pow(2,i);
  }
  f(gv);
}