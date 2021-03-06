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
int my_count(In first, In last, T& init){
  int count = 0;
  while(first!=last){
    if(*first == init){
      count ++;
    }
    ++first;
  }
  return count;
}

int main()
try {
    vector<int> vi;
    for (int i = 0; i<50; ++i)
        vi.push_back(randint(50));
    cout << "vi:\n";
    for (vector<int>::iterator p = vi.begin(); p!=vi.end(); ++p)
        cout << *p << '\n';
    cout << "Enter value for which you want to know the count, -1 to exit: ";
    int val;
    while (cin>>val) {
        if (val==-1) break;
        int ctr = my_count(vi.begin(),vi.end(),val);
        cout << val << " is " << ctr << " time" << (ctr!=1 ? "s " : " ")
            << "in vi.\nNext value: ";
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