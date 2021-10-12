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
#include <experimental/random>
#include<set>

using namespace std;

inline int randint(int max) { return rand()%max; }

inline int randint(int min, int max) { return randint(max-min)+min; }

inline double sqrt(int x) { return sqrt(double(x)); }	// to match C++0x

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


//------------------------------------------------------------------------------

struct Fruit {
    string name;
    int count;
    double unit_price;
    Fruit(string n, int c, double up = 0.0)
        :name(n), count(c), unit_price(up) { }
};

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Fruit* f)
{
    os << setw(7) << left << f->name;
    os << f->count << '\t' << f->unit_price;
    return os;
}

//------------------------------------------------------------------------------

struct Fruit_comparison {
    bool operator()(const Fruit* a, const Fruit* b) const
    {
        return a->name < b->name;
    }
};

//------------------------------------------------------------------------------

int main()
try {
    set<Fruit*,Fruit_comparison> inventory;
    inventory.insert(new Fruit("Quince",5));    // test default parameter
    inventory.insert(new Fruit("Apple",200,0.37));
    inventory.insert(new Fruit("Orange",150,0.45));
    inventory.insert(new Fruit("Grape",13,0.99));
    inventory.insert(new Fruit("Kiwi",512,1.15));
    inventory.insert(new Fruit("Plum",750,2.33));

    typedef set<Fruit*,Fruit_comparison>::const_iterator Si;
    for (Si p = inventory.begin(); p!=inventory.end(); ++p) cout << *p << '\n';

    // Clean up
    for (Si p = inventory.begin(); p!=inventory.end(); ++p) delete *p;
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
