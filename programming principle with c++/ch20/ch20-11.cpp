#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<vector>
#include<list>
#include<cmath>
#include <experimental/random>

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

template<class Iter>
void print_ctr(Iter first, Iter last)
{
    cout << "{";
    while (first != last) {
        cout << " " << *first;
        ++first;
    }
    cout << " }\n";
}

template<typename T, typename U>
void copy_list_to_vec(vector<T>& vec, list<U>& list){
  print_ctr(vec.begin(),vec.end());
  print_ctr(list.begin(),list.end());

  auto list_start = list.begin();
  auto vec_start = vec.begin();

  
  while(vec_start != vec.end()){
    *vec_start = (T) *list_start;
    ++list_start;
    ++vec_start;
  }
  while(list_start != list.end()){
    vec.push_back((T)*list_start);
    ++list_start;
  }
}

int main(){
    list<int> li;
    vector<double> vec;
    for (int i = 0; i<10; ++i)
      li.push_back(experimental::randint(0,99));
    copy_list_to_vec(vec,li);
    print_ctr(vec.begin(),vec.end());
}