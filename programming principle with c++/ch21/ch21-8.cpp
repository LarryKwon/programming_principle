#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<memory>
#include<vector>
#include<list>
#include<map>
#include<iomanip>
#include<numeric>

using namespace std;

struct Range_error : out_of_range {	// enhanced vector range error reporting
	int index;
	Range_error(int i) :out_of_range("Range error: "+to_string(i)), index(i) { }
};


inline void error(const string& s)
{
	throw runtime_error(s);
}

inline void error(const string& s, const string& s2)
{
	error(s+s2);
}

struct Frequent{
  bool operator()(const pair<string,int>& a, const pair<string,int>& b){
    if(a.second < b.second) return true;
    else{
      if(a.second == b.second){
        if(a.first < b.first) return true;
        else return false;
      }
      else{
        return false;
      }
    }
  }
};

int main(){
  map<string,int> words;

    const string ifname = "chapter21_ex08_in.txt";
    ifstream ifs(ifname.c_str());
    if (!ifs) error("couldn't open ",ifname);
    string s;
    while (ifs>>s) ++words[s];


  vector<pair<int, string>> vec;
  for(const auto&p: words){
    vec.push_back(make_pair(p.second,p.first));
  }
  sort(vec.begin(),vec.end());
  for(const auto& p: vec)
    cout << p.first << ": "<< p.second << '\n';
}