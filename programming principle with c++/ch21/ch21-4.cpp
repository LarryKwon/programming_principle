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
#include <experimental/random>

using namespace std;

inline int randint(int max) { return rand()%max; }

inline int randint(int min, int max) { return randint(max-min)+min; }

inline double sqrt(int x) { return sqrt(double(x)); }	// to match C++0x

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

template<typename In, typename T>
int my_count(In first, In last, T& val){
  int count = 0;
  while(first!=last){
    if(*first == val){
      count ++;
    }
    ++first;
  }
  return count;
}


template<typename In, typename Pred>
int my_count_if(In first, In last, Pred pred){
  int count = 0;
  while(first!=last){
    if(pred(*first)){
      count ++;
    }
    ++first;
  }
  return count;
}

template<typename T>
struct Less_than{
  T val;
  Less_than(const T& val)
  :val(val){}
  bool operator()(const T& arg){
    return arg < val;
  }
};

template<typename T>
struct Greater_than{
  T val;
  Greater_than(const T& val)
  :val(val){}
  bool operator()(const T& arg){
    return arg > val;
  }
};

bool odd(int val){
  if(val %2 == 0) return false;
  return true;
}


int main()
try {
    vector<int> vi;
    for (int i = 0; i<10; ++i)
        vi.push_back(randint(10));
    cout << "vi:\n";
    for (vector<int>::iterator p = vi.begin(); p!=vi.end(); ++p)
        cout << *p << '\n';

    // Test Less_than function object
    cout << "Enter value for less than count, -1 to exit: ";
    int val;
    while (cin>>val) {
        if (val==-1) break;
        int ctr = my_count_if(vi.begin(),vi.end(),Less_than<int>(val));
        cout << "There " << (ctr==1 ? "is " : "are ") << ctr << " value"
            << (ctr==1 ? " " : "s ") << "less than " << val << " in vi.\n"
            << "Next value: ";
    }

    // Test Greater_than function object
    cout << "Enter value for greater than count, -1 to exit: ";
    while (cin>>val) {
        if (val==-1) break;
        int ctr = my_count_if(vi.begin(),vi.end(),Greater_than<int>(val));
        cout << "There " << (ctr==1 ? "is " : "are ") << ctr << " value"
            << (ctr==1 ? " " : "s ") << "greater than " << val << " in vi.\n"
            << "Next value: ";
    }

    // Test odd() function
    int ctr = my_count_if(vi.begin(),vi.end(),odd);
    cout << "There are " << ctr << " odd values in vi.\n";
}
catch (Range_error& re) {
    cerr << "bad index: " << re.index << "\n";
}
catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
catch (...) {
    cerr << "exception\n";
}
