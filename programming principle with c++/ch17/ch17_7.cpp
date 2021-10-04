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
  int size = 1;
  int i = 0;
  char* my_array = new char[size];
  *my_array = 0;

  while(cin >> ch && ch!='!'){
    if(size/2 < i){
      my_array = resize(my_array);
    }
    my_array[i] = ch;
    i++;
  }
  my_array[i] = '\0';

  cout << my_array;
}