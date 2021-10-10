#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>

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
struct Link{
  Link* succ;
  Elem val;

  Link(const Elem& val = Elem(), Link* s = nullptr)
  :val{val},succ{s}{}
};

template<typename Elem>
class slist{
  Link<Elem>* first;
  
  public:
    slist()
    :first{nullptr}
    {}

    slist(Link<Elem>& node)
    :first{node},iterator{node}
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

    Elem& front(){return first->val;}
    Elem& back();
};

template<typename Elem>
class slist<Elem>::iterator{

  public:
    Link<Elem>* curr;
    iterator(Link<Elem>* p): curr{p} {}

    iterator& operator++(){ curr = curr ->succ; return *this;}
    // iterator& operator--(){ curr = curr->prev; return *this;}
    Elem& operator*() { return curr->val;}

    bool operator==(const iterator& b) const { return curr == b.curr; }
    bool operator!=(const iterator& b) const { return curr != b.curr; }

};

template<typename Elem> 
typename slist<Elem>::iterator slist<Elem>::begin() 
{ 
    return iterator(first); 
}

template<typename Elem>
typename slist<Elem>::iterator slist<Elem>::end()
{
  return iterator(0);
}

template<typename Elem>
typename slist<Elem>::iterator slist<Elem>::insert(typename slist<Elem>::iterator p, const Elem& v){
  Link<Elem>* tmp = p.curr;
  iterator prev = begin();
  while(prev.curr->succ != p.curr){
    ++prev;
  }
  Link<Elem>* new_node = new Link<Elem>(v,p.curr);
  prev.curr->succ = new_node;
  return iterator(new_node);
}

template<typename Elem>
typename slist<Elem>::iterator slist<Elem>::erase(typename slist<Elem>::iterator p){
  iterator next = begin();
  while(next != p){
    ++next;
  }
  ++next;
  p.curr->succ = p.curr->succ->succ;
  next.curr->succ = nullptr;
  delete next.curr;
  return p;
}

template<typename Elem>
void slist<Elem>::push_back(const Elem &v){
  iterator p = begin();
  while((p.curr->succ)){
    ++p;
  }
  p.curr->succ = new Link<Elem>(v);
}

template<typename Elem>
void slist<Elem>::push_front(const Elem &v){
  first = new Link<Elem>(v,first);
}

template<typename Elem>
void slist<Elem>::pop_front(){
  auto second = first->succ;
  delete first;
  first = second;
}

template<typename Elem>
void slist<Elem>::pop_back(){
  iterator p = begin();
  if(p==end()) return;
  if(!(p.curr->succ)) {
    pop_front();
    return ;
  }
  while((p.curr->succ->succ)){
    ++p;
  }
  erase(p);
}

template<typename Elem>
Elem& slist<Elem>::back(){
  iterator p = begin();
  while((p.curr->succ)){
    ++p;
  }
  return *p;
}

template<typename T>
void user(slist<T>& lst){
  auto q = find(lst.begin(),lst.end(),T{42});
}

template<class Iterator>
Iterator high(Iterator first, Iterator last)
{
    Iterator high = first;
    for (Iterator p = first; p!=last; ++p)
        if (*high<*p) high = p;
    return high;
}

template<class Elem>
void print(slist<Elem>& lst)
{
    typename slist<Elem>::iterator p = lst.begin();
    while (p != lst.end()) {
        cout << *p << ' ';
        ++p;
    }
    cout << "\n";
}

int main()
try {
    slist<int> lst;
    int x;
    while (cin >> x) lst.push_front(x);
    slist<int>::iterator p = high(lst.begin(),lst.end());
    cout << "The highest value was " << *p << "\n";

    print(lst);

    p = lst.begin();
    for (int i = 0; i<2; ++i)
        ++p;
    cout << "\np points at " << *p << "\n";
    p = lst.insert(p,99);
    p = lst.insert(p,100);
    cout << "List after inserting two elements: ";
    print(lst);

    p = lst.erase(p);
    cout << "List after erasing element after p: ";
    print(lst);

    cout << "Last element: " << lst.back() << "\n";

    cout << "Popping the two first elements: ";
    lst.pop_front();
    lst.pop_front();
    print(lst);

    cout << "Adding 33 and 44 to end: ";
    lst.push_back(33);
    lst.push_back(44);
    print(lst);

    cout << "Popping back twice: ";
    lst.pop_back();
    lst.pop_back();
    print(lst);

    cout << "Popping until nothing left: ";
    while (lst.begin()!=lst.end()) {
        lst.pop_back();
        print(lst);
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