#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<vector>
#include<list>

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

template<typename iterator>
iterator biggest_element(iterator first, iterator last){
  iterator high = first;
  while(first!=last){
    if(*high < *last) first = high;
    ++first;
  }
  return high;
}

int main()
try {
    vector<string> vs;
    string s;
    cout << "Enter a few words, Ctrl-Z to end: ";
    while (cin>>s)
        vs.push_back(s);

    vector<string>::iterator last = biggest_element(vs.begin(),vs.end());
    if (last!=vs.end())
        cout << "The lexicographically last string in the vector is \""
            << *last << "\".\n";
    else
        cout << "Something went wrong.\n";
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