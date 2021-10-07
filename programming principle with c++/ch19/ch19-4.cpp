//ch17_11,12,13
#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<limits>
#include<ctime>

using namespace std;

struct God{
  string name;
  string mythology;
  string vehicle;
  string weapon;

  God(const God&);
  God(string name, string mythology, string vehicle, string weapon);
  God();
};

ostream& operator<<(ostream& os, const God& god){
   os << '['<< god.name << ", " << god.mythology << ", " << god.vehicle << ", " << god.weapon << ']'<<'\n';
    return os;
}

God::God(const God& god)
:name{god.name},mythology{god.mythology},vehicle{god.vehicle},weapon{god.weapon}
{}

God::God(){}

God::God(string name, string mythology, string vehicle, string weapon)
:name{name}, mythology{mythology},vehicle{vehicle}, weapon{weapon}{}



template<typename T>
struct Link{
  T val;

  // Link(const God& v, Link* p = nullptr, Link* s = nullptr)
  //   : god{v},prev{p},succ{s}{}
  
  Link(string n, string m, string v, string w, Link*p = nullptr, Link* s = nullptr)
  :val{T(n,m,v,w)},prev{p},succ{s}{}

  Link(T& val, Link* p = nullptr, Link* s = nullptr)
  :val{val},prev{p},succ{s}{} 

  Link<T>* insert(Link<T>* n);
  Link<T>* add(Link<T>* n);
  Link<T>* erase();
  Link<T>* find(const string& s);
  const Link<T>* find(const string& s) const;
  Link<T>* advance(int n) const;
  // Link* advance(int n);
  Link<T>* add_ordered(Link<T>* n);

  Link<T>* next() const { return succ; }
  Link<T>* previous() const { return prev; }

  private:
    Link<T>* prev;
    Link<T>* succ;
};

//지정된 요소 앞에 삽입
template<typename T>
Link<T>* Link<T>::insert( Link<T>* n){

  if(n==nullptr) return this;
  if(this==nullptr) return n;
  n->succ = this;
  if(this->prev) this->prev->succ = n;
  n->prev = this->prev;
  this->prev = n;
  return n;
}

//add 지정된 요소 뒤에 삽입
template<typename T>
Link<T>* Link<T>::add( Link<T>* n){
  if(n==nullptr) return this;
  if(this == nullptr) return n;
  n->prev = this;
  if(this->succ) this->succ->prev = n;
  n->succ = this->succ;
  this->succ = n;
  return n;
}

template<typename T>
Link<T>* Link<T>::erase(){
  if(this==nullptr) return nullptr;
  if(this->succ) this->succ->prev = this->prev;
  if(this->prev) this->prev->succ = this->succ;

  return this->succ;
}

template<typename T>
Link<T>* Link<T>::find(const string& s){
  Link* p = this;
  while(p){
    if(p->val.name == s) return p;
    p = p -> succ;
  }
  return nullptr;
}

template<typename T>
Link<T>* Link<T>::advance(int n) const{
  Link* p = (Link*)this;
  if(p==nullptr) return nullptr;
  if(0<n){
    while(n--){
      if(p->next() == nullptr) return nullptr;
      p = p->next();
    }
  }
  else if(n<0){
    while(n++){
      if(p->previous() == nullptr) return nullptr;
      p = p->previous();
    }
  }
  return p;
}

template<typename T>
Link<T>* Link<T>::add_ordered(Link<T>* n){
  if(n==0) return this;
  if(n==this) return this;
  if(this == 0){
    n->prev = 0;
    n->succ = 0;
    return n;
  }
  Link<T> * p = this;
  if(this->val.name > n->val.name){
    Link* r = insert(n);
    return r;
  }

  while(p->val.name <= n->val.name ){
    if(p->succ == 0){
      p->add(n);
      return this;
    }
    p = p->succ;
  }
  p->insert(n);
  return this;
}

template<typename T>
void print_all(Link<T>* p){
  cout << "{ ";
  while(p){
    cout << p->val;
    if(p=p->next()) cout << ", ";
  }
  cout << " }";
}

template<typename T>
Link<T>* extract(Link<T>* n, string s){
  Link<T>* p = n->find(s);
  if(p){
    if(p==n && p->next()) n = p->next();
    else n = 0;
    p->erase();
    return p;
  }
  return 0;
}


int main(){
 try {
    Link<God>* all_gods = new Link<God>("Thor","Norse","Pinzgauer","Hammer");
    all_gods = all_gods->insert(new Link<God>("Odin","Norse","Eight-legged horse",""));
    all_gods = all_gods->insert(new Link<God>("Zeus","Greek","","Lightning"));
    all_gods = all_gods->insert(new Link<God>("Freia","Norse","F-transport","F-weapon"));
    all_gods = all_gods->insert(new Link<God>("Hera","Greek","H-transport","Spear"));
    all_gods = all_gods->insert(new Link<God>("Athena","Greek","A-transport","A-weapon"));
    all_gods = all_gods->insert(new Link<God>("Mars","Roman","M-transport","M-weapon"));
    all_gods = all_gods->insert(new Link<God>("Poseidon","Greek","Seahorse","Trident"));
    all_gods = all_gods->insert(new Link<God>("Ares","Greek","A-transport","A-weapon"));
    all_gods = all_gods->insert(new Link<God>("Vesuvius","Roman","V-transport","Volcano"));
    all_gods = all_gods->insert(new Link<God>("Bacchus","Roman","Stretcher","Wine goblet"));

    print_all(all_gods);

    Link<God>* norse_gods = 0;
    norse_gods = norse_gods->add_ordered(extract(all_gods,"Odin"));
    norse_gods = norse_gods->add_ordered(extract(all_gods,"Thor"));
    norse_gods = norse_gods->add_ordered(extract(all_gods,"Freia"));

    Link<God>* greek_gods = 0;
    greek_gods = greek_gods->add_ordered(extract(all_gods,"Hera"));
    greek_gods = greek_gods->add_ordered(extract(all_gods,"Athena"));
    greek_gods = greek_gods->add_ordered(extract(all_gods,"Poseidon"));
    greek_gods = greek_gods->add_ordered(extract(all_gods,"Zeus"));
    greek_gods = greek_gods->add_ordered(extract(all_gods,"Ares"));

    Link<God>* roman_gods = 0;
    roman_gods = roman_gods->add_ordered(extract(all_gods,"Mars"));
    roman_gods = roman_gods->add_ordered(extract(all_gods,"Vesuvius"));
    roman_gods = roman_gods->add_ordered(extract(all_gods,"Bacchus"));

    // // could delete all_gods here, but that leads to a mess

    cout << "\n\nNorse gods:\n";
    print_all(norse_gods);
    cout << "\n\nGreek gods:\n";
    print_all(greek_gods);
    cout << "\n\nRoman gods:\n";
    print_all(roman_gods);
    cout << "\n";

    // could delete god lists here, but a) not sure if that works and
    // b) program ends here
}
catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
}