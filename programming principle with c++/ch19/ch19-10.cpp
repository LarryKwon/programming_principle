#include<iostream>
#include<sstream>
#include<cmath>
#include<string>
#include<algorithm>

using namespace std;

inline void error(const string& s)
{
	throw runtime_error(s);
}

template<typename T>
class auto_pntr{
  T* ptr;
  
  public:
    auto_pntr(T* v)
    :ptr{v}{}

    auto_pntr(T v)
    :ptr{&v}{}

    ~auto_pntr(){
      delete ptr;
    }

    T* operator->()const;
    T operator*()const;
    T* release();
};

template<typename T>
T* auto_pntr<T>::operator->() const{
  return ptr;
}

template<typename T>
T auto_pntr<T>::operator*() const{
  return *ptr;
}

template<typename T>
T* auto_pntr<T>::release() {
  T* result = ptr;
  ptr = nullptr;
  return result;
}


struct Tracer {
    Tracer() { cout << "Tracer()\n"; }
    Tracer(int n) : val(n) { cout << "Tracer(int n)\n"; }
    ~Tracer() { cout << "~Tracer()\n"; }
    int val;
};

Tracer* f()
{
    Tracer* p1 = new Tracer();          // destructor never called
    auto_pntr<Tracer> p2(new Tracer()); // destructor called when out of scope
    auto_pntr<Tracer> p3(new Tracer(5)); // released from auto_pntr
    return p3.release();
}

//------------------------------------------------------------------------------

// shows how auto_pntr destroys its object when an exception is thrown
void f2()
{
    // Tracer* p1 = new Tracer();
    auto_pntr<Tracer> p2(new Tracer());
    error("Exception!");    // calls destructor of p2
    // delete p1;              // never gets called
}

//------------------------------------------------------------------------------

int main()
try {
    Tracer* p = f();
    cout << "Dereference: " << (*p).val << "\n";
    cout << "Pointer access: " << p->val << "\n";
    delete p;

    f2();
}
catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
catch (...) {
    cerr << "exception\n";
}