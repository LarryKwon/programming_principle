#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

istream& read_word(istream& is, char* buffer, int max) {
    is.width(max);
    is >> buffer;
    return is;
}

bool is_palindrome(const string& s){
  return true;
}

bool is_palindrome(const char s[], int n){
  return true;
}

bool is_palindrome(const char* first, const char* last){
  return true;
}

int main(){
  const int max = 128;
  for(char s[max]; read_word(cin,s,max);){
    cout << s << " is";
    if(!is_palindrome(s)) cout << " not";
    cout << " a palindrome\n";
  }
}