#include<iostream>
#include<cstdlib>
#include<string>
#include <cmath>
#include<algorithm>
#include<vector>

using namespace std;

char* resize(char * my_array){
  if(my_array == 0) return 0;

  int n = 0;
  for(int i = 0; my_array[i]; i++){
    n++;
  }

  char* new_array = new char[n*2];
  for(int i = 0; i<n;i++){
    new_array[i] = my_array[i];
  }
  delete[] my_array;
  return new_array;
}


int main(){
  char ch;
  string s;
  while(cin >> ch && ch != '!'){
    s.push_back(ch);
  }
}