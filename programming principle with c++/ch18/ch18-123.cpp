#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

int strlen(const char* s){
  char* p = (char*)s;
  int len = 0;
  while(*p!=0){
    len += 1;
    p++;
  }
  return len;
}

char* strdup(const char* s){
  char* p = (char*)s;
  int size =0;
  for(int i = 0; *p!=0; i++){
    size++;
    p++;
  }

  char* a = new char[size];

  for(int i = 0; i<size; i++){
    a[i] = s[i];
  }
  return a;
}

char* findx(const char* s, const char* x){
  char* xx = (char *)x;
  char* ss = (char *)s;
  char* start = nullptr;

  for(int i = 0; *ss!='\0';i++){
    if(*xx == '\0'){
      return start;
    }

    if(*xx==*ss){
      if(xx==x){
        start = ss;
      }
      xx++;
    }
    else{
      xx = (char*)x;
    }
    ss++;
  }
  return start;
}

int strcmp(const char* s1, const char* s2){
  int len_s1 = strlen(s1);
  int len_s2 = strlen(s2);

  char* p1 = (char*) s1;
  char* p2 = (char*) s2;

  int len = len_s1 > len_s2 ? len_s2:len_s1;
  for(int i = 0; i<len; i++){
    if(*p1 > *p2){
      return 1;
    }
    else if(*p1 < *p2){
      return -1;
    }
    else{
      p1++;
      p2++;
    }
  }
  int result = 0;
  if(len_s1 == len_s2){
    return result;
  }
  result = len_s1>len_s2 ? 1:-1;
  return result;
}

string cat_dot(const string& s1, const string& s2){
  return s1 + '.' + s2;
}

int main(){
  cout << cat_dot("Niels","Bohr");
}