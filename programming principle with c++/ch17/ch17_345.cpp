#include<iostream>
#include<cstdlib>
#include<string>
#include <cmath>
#include<algorithm>
#include<vector>

using namespace std;

void to_lower(char*s){
  char* p = s;
  while(*p != 0){
    *p = tolower(*p);
    p++;
  }
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

//17.3
// int main(){
//   string s = "Hello, World!";
//   to_lower(&s[0]);
//   cout << s;
// }

// //17.4
// int main(){
//   string s = "Hello, World!!!!!!!!!!1";
//   char * p = strdup(&s[0]);
//   cout << p;
// }

//17.5
int main(){
  string s = "Hello,world!!!";
  string p = "world";
  char* pos = findx(&s[0],&p[0]);
  cout << pos;
}