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

template<typename iter>
void print(iter first, iter last)
{
    while (first!=last) {
        cout << *first << '\n';
        ++first;
    }
}



template<typename In,typename T>
bool my_binary_search(In first, In last, const T& val){
  if(first == last) return false;
  In middle = first + (last-first)/2;
  if(*middle == val) return true;
  if(*middle < val && (middle+1)!=last) return my_binary_search(middle,last,val);
  if(*middle > val) return my_binary_search(first,middle,val);
  return false;
}

template<typename In>
In middle(In first, In last){
  if(first == last) error("first == last in middle");
  int dist = 0;
  In p = first;
  while(p!=last){
    ++p;
    dist ++;
  }
  advance(first,dist/2);
  return first;
}

template<typename In, typename T>
bool my_binary_bid_search(In first, In last, const T& val)
{
  if(first == last) return false;
  In mid = middle(first,last);
  if(*mid == val) return true;
  In last_one = last;
  --last_one;
  if(*mid < val && mid!=last_one) return my_binary_bid_search(mid,last,val);
  if(*mid > val) return my_binary_bid_search(first,mid,val);
}


int main()
try {
    // test for vector
    vector<int> vi;
    for (int i = 0; i<20; ++i)
        vi.push_back(2*i);
    cout << "Vector:\n";
    print(vi.begin(),vi.end());

    cout << "Enter int to find (-1 to exit): ";
    int i;
    while (cin>>i && i!=-1) {
        cout << i << " is "
            << (my_binary_search(vi.begin(),vi.end(),i) ? "" : "not ")
            << "in vi. Next int: ";
    }

    // test for list
    list<int> li(20);
    copy(vi.begin(),vi.end(),li.begin());
    cout << "\nList:\n";
    print(li.begin(),li.end());

    cout << "Enter int to find (-1 to exit): ";
    while (cin>>i && i!=-1) {
        cout << i << " is "
            << (my_binary_bid_search(li.begin(),li.end(),i) ? "" : "not ")
            << "in li. Next int: ";
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