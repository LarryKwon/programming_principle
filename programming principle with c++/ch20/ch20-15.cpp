#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<memory>
#include<vector>

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

template<typename Elem>
class pvector{
  vector<Elem*> elems;

  public:
    using size_type = unsigned long;
    using iterator = typename vector<Elem*>::iterator;
    using const_iterator = typename vector<Elem*>::const_iterator;

    explicit pvector(int s);
    pvector();
    pvector(const pvector &);
    pvector& operator=(const pvector &);
    ~pvector();

    iterator begin() { return elems.begin();}
    const_iterator begin() const { return elems.begin();}
    iterator end() { return elems.end();}
    const_iterator end() const{return elems.end();}

    Elem* operator[ ](size_type n){return elems[n];}
    const Elem* operator[ ](size_type n) const {return elems[n];}

    int size() const{return elems.size();}
    int capacity() const{return elems.capacity();}

    void push_back(const Elem* d);


    iterator insert(iterator p, const Elem* val);
    iterator erase(iterator p);
};

void f1()
{
    pvector<int> pv;
    for (int i = 0; i<10; ++i) {
        pv.push_back(new int(i));
    }
    for (pvector<int>::size_type i = 0; i<pv.size(); ++i)
        cout << *pv[i] << "\n"; // test [] - requires dereference
}