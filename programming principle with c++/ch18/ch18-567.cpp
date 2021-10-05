#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

// string cat_dot(const string& s1, const string& s2){
//   return s1 + '.' + s2;
// }

// string cat_dot(const string& s1, const string& s2, const string& delimiter){
//   return s1 + delimiter + s2;
// }

int strlen(const char* s){
  char* p = (char*)s;
  int len = 0;
  while(*p!=0){
    len += 1;
    p++;
  }
  return len;
}

char* cat_dot(const char* s1, const char* s2, const char* delimiter){
  // cout << s1;
  // cout << s2;
  // cout << delimiter;


  int len_s1 = strlen(s1);
  int len_s2 = strlen(s2);
  int len_delimiter = strlen(delimiter);

  // cout << len_s1 << len_s2 << len_delimiter;

  char* p1 = (char*) s1;
  char* p_del = (char*) delimiter;
  char* p2 = (char*) s2;

  char* new_str = new char[len_s1 + len_s2 + len_delimiter + 1];
  
  for(int i = 0; p1[i] != 0; i++){
    new_str[i] = p1[i];
  }
  // cout << new_str;
  
  int j = 0;
  for(int i = len_s1; p_del[j] !=0; i++){
    new_str[i] = p_del[j];
    j++;
  }

  // cout << new_str;

  int k = 0;
  for(int i = len_s1 + len_delimiter; p2[k]!=0; i++){
    new_str[i] = p2[k];
    k++;
  }
  new_str[len_s1+len_s2+len_delimiter] = 0;

  // cout << new_str;
  return new_str;
}


int main(){
  const char* s1 = "Niels";
  const char* s2 = "Bohr";
  const char* delimiter = ".....";
  cout << cat_dot(s1,s2,delimiter);
}