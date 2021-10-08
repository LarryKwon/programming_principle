#include<iostream>
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


template<typename T>
ostream& operator<<(ostream& os, vector<T> vec){
  auto p = vec.begin();
  while(p!=vec.end()){
    cout << *p << "  ";
    p++;
  }

  return os;
}
template<typename T>
istream& operator>>(istream& is, vector<T>& vec){
  T val;
  string command;
  getline(cin,command);
  istringstream ss{command};

  while(ss>>val){
    if(ss.fail()) break;
    vec.push_back(val);
  }

  return is;
}


int main()
try {
    vector<double> vd;
    vector<int> vi;
    vector<string> vs;
    cout << "Enter vector of doubles: ";
    cin >> vd;
    cout << "Enter vector of integers: ";
    cin >> vi;
    cout << "Enter vector of strings: ";
    cin >> vs;


    cout << vd << "\n" << vi << "\n" << vs << "\n";
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
