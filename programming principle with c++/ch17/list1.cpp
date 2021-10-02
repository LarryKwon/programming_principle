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

struct Link{
  string value;

  Link(const string& v, Link* p = nullptr, Link* s = nullptr)
    : value{v}, prev{p},succ{s}{ }

  Link* insert(Link* n);
  Link* add(Link* n);
  Link* erase();
  Link* find(const string& s);
  const Link* find(const string& s) const;
  Link* advance(int n) const;
  // Link* advance(int n);

  Link* next() const { return succ; }
  Link* previous() const { return prev; }

  private:
    Link* prev;
    Link* succ;
};

//지정된 요소 앞에 삽입
Link* Link::insert( Link* n){

  if(n==nullptr) return this;
  if(this==nullptr) return n;
  n->succ = this;
  if(this->prev) this->prev->succ = n;
  n->prev = this->prev;
  this->prev = n;
  return n;
}

//add 지정된 요소 뒤에 삽입
Link* Link::add( Link* n){
  return n;
}

Link* Link::erase(){
  if(this==nullptr) return nullptr;
  if(this->succ) this->succ->prev = this->prev;
  if(this->prev) this->prev->succ = this->succ;

  return this->succ;
}

Link* Link::find(const string& s){
  Link* p = this;
  while(p){
    if(p->value == s) return p;
    p = p -> succ;
  }
  return nullptr;
}

Link* Link::advance(int n) const{
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



void print_all(Link* p){
  cout << "{ ";
  while(p){
    cout << p->value;
    if(p=p->next()) cout << ", ";
  }
  cout << " }";
}

int main(){
  Link* norse_gods = new Link{"Thor"};
  norse_gods = norse_gods -> insert(new Link{"Odin"});
  norse_gods = norse_gods -> insert(new Link{"Zeus"});
  norse_gods = norse_gods -> insert(new Link{"Freia"});

  Link* greek_gods = new Link{"Hera"};
  greek_gods = greek_gods -> insert(new Link{"Athena"});
  greek_gods = greek_gods -> insert(new Link{"Mars"});
  greek_gods = greek_gods -> insert(new Link{"Poseidon"});

  Link* p1 = greek_gods -> find("Mars");
  if(p1) p1->value = "Ares";

  Link* p2 = norse_gods -> find("Zeus");

  if(p2){
    if(p2==norse_gods) norse_gods = p2->next();
    p2 -> erase();
    greek_gods = greek_gods->insert(p2);
  }

  print_all(norse_gods);
  print_all(greek_gods);

  return 0;
}