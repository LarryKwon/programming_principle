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

    explicit pvector(int s)
    :elems(vector<Elem*>(s)){}
    
    pvector()
    :elems(){}

    pvector(const pvector& arg)
    :elems(arg.elems){}

    pvector& operator=(const pvector& arg){ elems = arg.elems; }
    ~pvector();

    iterator begin() { return elems.begin();}
    const_iterator begin() const { return elems.begin();}
    iterator end() { return elems.end();}
    const_iterator end() const{return elems.end();}

    Elem* operator[ ](size_type n){return elems[n];}
    const Elem* operator[ ](size_type n) const {return elems[n];}

    int size() const{return elems.size();}
    int capacity() const{return elems.capacity();}

    void push_back( Elem* d){elems.push_back(d);}

};
template<typename Elem>
pvector<Elem>::~pvector(){
  for(auto p:elems){
    cout <<"delete elem" << p <<'\n';
    delete p;
  }
}

template<typename Elem>
class ovector:public pvector<Elem>{
  public:
  using size_type = typename pvector<Elem>::size_type;
  Elem&  operator[](size_type n){return *(pvector<Elem>::operator[](n));}
  Elem& operator*(size_type n){return *(pvector<Elem>::operator*(n));}
};

template<typename Elem>
class ownership_vector{
  vector<Elem*> elems;
  vector<Elem*> owns;
  ownership_vector(const ownership_vector& arg);
  ownership_vector& operator=(const ownership_vector& arg);

  public:
    using size_type = unsigned long;

    ownership_vector(Elem& d){push_back(d);}
    ownership_vector(Elem* d){push_back(d);}

    ~ownership_vector();
    
    Elem* operator[ ](size_type n){return elems[n];}
    const Elem* operator[ ](size_type n) const {return elems[n];}

    int size() const{return elems.size();}
    int capacity() const{return elems.capacity();}

    void push_back(Elem* d){elems.push_back(d);owns.push_back(d);}
    void push_back(Elem& d){elems.push_back(&d);}
};

template<typename Elem>
ownership_vector<Elem>::~ownership_vector(){
  for(size_type i = 0; i<owns.size();i++){
    cout << "delete" << owns[i] << "\n";
    delete owns[i];
  }
}

void f1()
{
    pvector<int> pv;
    for (int i = 0; i<10; ++i) {
        pv.push_back(new int(i));
    }
    for (pvector<int>::size_type i = 0; i<pv.size(); ++i)
        cout << *pv[i] << "\n"; // test [] - requires dereference
}
void f2()
{
    ovector<double> ov;
    for (int i = 0; i<10; ++i)
        ov.push_back(new double(i*1.1));
    for (ovector<double>::size_type i = 0; i<ov.size(); ++i)
        cout << ov[i] << "\n";  // test [] - no dereference required

    ovector<double>::iterator it = ov.begin();
    while (it!=ov.end()) {
        cout << *it << ' '; // test * - no second dereference required
        ++it;
    }
    cout << "\n";
}

// test ownership_vector
void f3(int i1, int i2, int i3)
{
    ownership_vector<int> osv(i1);
    // fill with pointers and references in turn
    osv.push_back(new int(2));
    osv.push_back(i2);
    osv.push_back(new int(4));
    osv.push_back(i3);
    osv.push_back(new int(6));

    for (int i = 0; i<osv.size(); ++i)
        cout << *osv[i] << "\n";
    // dtor called here: should destroy 2, 4 and 6
}

int main()
try {
    f1();
    cout << "\n\n";
    f2();
    cout << "\n\n";
    f3(1,3,5);
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