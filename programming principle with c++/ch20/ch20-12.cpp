#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<vector>
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


template<class Iterator>
Iterator high(Iterator first, Iterator last)
{
    Iterator high = first;
    for (Iterator p = first; p!=last; ++p)
        if (*high<*p) high = p;
    return high;
}

template<typename Elem>
struct Link{
  Link* prev;
  Link* succ;
  Elem val;

  Link(Elem& val = Elem(), Link* p = nullptr, Link* s = nullptr)
  :val{val},prev{p},succ{s}{}
};

template<typename Elem>
class list{
  Link<Elem>* first;
  Link<Elem>* last;
  
  public:
    list()
    :first{new Link<Elem>()},last{first}
    {}

    list(Link<Elem>& node)
    :first{node},last{nullptr},iterator{node}
    {}

    class iterator;

    iterator begin();
    iterator end();

    iterator insert(iterator p, const Elem& v);
    iterator erase(iterator p);

    void push_back(const Elem& v);
    void push_front(const Elem& v);
    void pop_front();
    void pop_back();

    Elem& front();
    Elem& back();
};

template<typename Elem>
class list<Elem>::iterator{
  Link<Elem>* curr;

  public:
    iterator(Link<Elem>* p): curr{p} {}

    iterator& operator++(){ curr = curr ->succ; return *this;}
    iterator& operator--(){ curr = curr->prev; return *this;}
    Elem& operator*() { return curr->val;}

    bool operator==(const iterator& b) const { return curr == b.curr; }
    bool operator!=(const iterator& b) const { return curr != b.curr; }

};

template<typename Elem> 
typename list<Elem>::iterator list<Elem>::begin() 
{ 
    return iterator(first); 
}

template<typename Elem>
typename list<Elem>::iterator list<Elem>::end()
{
  return iterator(last);
}

template<typename Elem>
void list<Elem>::push_back(const Elem &v){
  last =  new Link<Elem>(v,last,nullptr);
}

template<typename Elem>
void list<Elem>::push_front(const Elem &v){
  first = new Link<Elem>(v,nullptr,first);
}

template<typename T>
void user(list<T>& lst){
  auto q = find(lst.begin(),lst.end(),T{42});
}
int main()
try {
    list<int> lst;
    int x;
    while (cin >> x) lst.push_front(x);
    list<int>::iterator p = high(lst.begin(),lst.end());
    cout << "The highest value was " << *p << "\n";
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