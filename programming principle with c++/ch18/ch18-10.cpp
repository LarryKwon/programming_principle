#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

istream& read_word(istream& is, string& buffer) {
    is >> buffer;
    return is;
}

bool is_palindrome(const string& s){
  string s_reverse = s; 
  reverse(s_reverse.begin(),s_reverse.end());
  if(s_reverse == s){
    return true;
  }else{
    return false;
  }
}

bool is_palindrome(const char s[], int n){
  char s_reverse[n];
  int first = 0;
  int last = n;
  for(int i = first;i<last;i++){
    s_reverse[i] = s[last - i -1];
  }
  for(int i = 0; i<n;i++){
    if(s_reverse[i]!=s[i]) return false;
  }
  return true;

}

bool is_palindrome(const char* first, const char* last){
  int length = 0;
  char* p = (char*)first;
  while(*p!=0){
    length += 1;
    p++;
  }
  char* reverse = new char[length];
  for(int i = 0; i< length;i++){
    reverse[i] = first[length - i -1];
  }
  for(int i = 0; i< length; i++){
    if(first[i]!=reverse[i]) return false;
  }
  return true;
}

int main(){
  const int max = 128;
  for(string s; read_word(cin,s);){
    int length = s.length();
    cout << s << " is";
    if(!is_palindrome(&s[0],&s[length-1])) cout << " not";
    cout << " a palindrome\n";
  }
}