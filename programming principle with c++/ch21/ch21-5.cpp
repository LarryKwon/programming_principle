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
In my_find(In first, In last, const T& val){
  while(first!=last){
    if(*first == val){
      return first;
    }
    ++first;
  }
  if(*first==val) return first;
  return first;
}

template<typename In, typename T>
int my_count(In first, In last, const T& val){
  int cnt = 0;
  while(first!=last){
    if(*first == val){
      cnt++;
    }
    ++first;
  }
  if(*first==val) cnt++;
  return cnt;
}

int main()
try {
    vector<int> vi;
    for (int i = 0; i<10; ++i)
        vi.push_back(randint(10));

    typedef vector<int>::iterator vi_it;

    cout << "vi:\n";
    for (vi_it it = vi.begin(); it<vi.end(); ++it)
        cout << *it << '\n';

    cout << "Enter int to search for and count (-1 to quit): ";
    int n;
    while (cin>>n) {
        if (n==-1) break;
        vi_it it = my_find(vi.begin(),vi.end()-1,n);
        int count = my_count(vi.begin(),vi.end()-1,n);
        if (it==vi.begin() && *it!=n) cout << n << " is not in vi. Next int: ";
        else cout << n << " is at index " << it-vi.begin()
            << " (occurs " << count << " time" << (count==1 ? "" : "s")
            << "). Next int: ";
    }
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