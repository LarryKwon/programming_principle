#include<iostream>
#include<sstream>
#include<cmath>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

inline void error(const string& s)
{
	throw runtime_error(s);
}

struct Tracer {
    Tracer() : val(0) { cout << "Def ctor\n"; }
    Tracer(int n) : val(n) { cout << "Arg ctor " << n << "   " << this <<"\n"; }
    Tracer(const Tracer& t) : val(t.val) { cout << "Cpy ctor " << val << "    " << this << "\n"; }
    Tracer& operator=(const Tracer& t)
    {
        val = t.val;
        cout << "Cpy assgn " << val << "    " << this << "\n";;
        return *this;
    }
    ~Tracer() { cout << "Destor " << val << "   " << this << "\n";; }
    int val;
};

//------------------------------------------------------------------------------

template<class T> class counted_ptr {
    T* val;     // the wrapped pointer
    int* cnt;   // reference counter
public:
    counted_ptr(const T& arg);                  // constructor with argument
    counted_ptr(const counted_ptr&);            // copy constructor
    counted_ptr& operator=(const counted_ptr&); // copy assignment

    ~counted_ptr();

    T operator*() const { return *val; }
    T* operator->() const { cout << val << "   "; return val; }

    int count() const { return *cnt; }
};

//------------------------------------------------------------------------------

template<class T> counted_ptr<T>::counted_ptr(const T& arg)
{
    val = new T(arg);
    cnt = new int(1);
    cout << val << '\n';
}

//------------------------------------------------------------------------------

template<class T> counted_ptr<T>::counted_ptr(const counted_ptr& arg)
{
    val = arg.val;
    cnt = arg.cnt;
    ++(*cnt);       // parentheses only for clarity
    cout << val << '\n';
}

//------------------------------------------------------------------------------

template<class T>
counted_ptr<T>& counted_ptr<T>::operator=(const counted_ptr& arg)
{
    if (&arg==this) return *this;
    --(*cnt);
    if (*cnt==0) {
        cout << "delete " << val << '\n';
        delete val;
        delete cnt;
    }
    val = arg.val;
    cnt = arg.cnt;
    ++(*cnt);       // parentheses only for clarity
    return *this;
}

//------------------------------------------------------------------------------

template<class T> counted_ptr<T>::~counted_ptr()
{
    --(*cnt);
    cout << "decrement counts of " << val << '\n';
    if (*cnt == 0) {
        cout << "Destructing counted pointer" << val << '\n';
        delete val;
        delete cnt;
    }
}

//------------------------------------------------------------------------------

// test functions
template<class T> void f3(const counted_ptr<T>& cp2)
{
    counted_ptr<Tracer> cp3(Tracer(0));
    cp3 = cp2;
    cout << "cp3->val: " << cp3->val << "\n";
    cout << "cp3.cnt: " << cp3.count() << "\n";
    cout << "cp2.cnt: " << cp2.count() << "\n";
}

template<class T> void f2(const counted_ptr<T>& cp1)
{
    counted_ptr<T> cp2(cp1);
    cout << "cp2->val: " << cp2->val << "\n";
    cout << "cp2.cnt: " << cp2.count() << "\n";
    f3(cp2);
    cout << "cp2.cnt: " << cp2.count() << "\n";
}

void f1()
{
    Tracer t(99);
    counted_ptr<Tracer> cp1(t);
    cout << "(*cp1).val: " << (*cp1).val << "\n";
    cout << "cp1->val: " << cp1->val << "\n";
    cout << "cp1.cnt: " << cp1.count() << "\n";
    f2(cp1);
    cout << "cp1.cnt: " << cp1.count() << "\n";
}

//------------------------------------------------------------------------------

int main()
try {
    // test counted_ptr with destruction after scope ends
    f1();

    // test counted_ptr as container element
    // vector<counted_ptr<string> > vcp;
    // counted_ptr<string> cp("test");
    // cout << "refcount: " << cp.count() << "\n";
    // for (int i = 0; i<10; ++i) {
    //     vcp.push_back(counted_ptr<string>(cp));
    //     cout << "refcount[" << i << "]: " << vcp[i].count() << "\n";
    // }
    // for (int i = 0; i<10; ++i)
    //     cout << "refcount[" << i << "]: " << vcp[i].count() << "\n";
    // vcp.resize(0,counted_ptr<string>(""));

    // // redirecting counted_ptr
    // counted_ptr<Tracer> cp1(Tracer(5));
    // counted_ptr<Tracer> cp2(cp1);
    // counted_ptr<Tracer> cp3(Tracer(6));
    // counted_ptr<Tracer> cp4(cp3);
    // cout << "cp1 refcount: " << cp1.count() << "\n";
    // cout << "cp3 refcount: " << cp3.count() << "\n";
    // cp3 = cp1;
    // cout << "cp1 refcount: " << cp1.count() << "\n";
    // cout << "cp4 refcount: " << cp4.count() << "\n";
    // cp4 = cp1;  // destroys Tracer(6) object
    // cout << "cp1 refcount: " << cp1.count() << "\n";
}
catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
catch (...) {
    cerr << "exception\n";
}