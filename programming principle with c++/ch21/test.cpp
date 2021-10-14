#include<iostream>

using namespace std;

struct Custom{
  public:
    int age;

    Custom()
    :age(0){}

    Custom(int a)
    :age(a){cout << "Custom constructor\n";}

    Custom(const Custom& arg)
    :age(arg.age) { cout << "Custom Copy constructor\n";}
};

class Test{
  public:
    string n;
    int cnt;
    Custom custm;

    // Test(const string& name, const int& count, const Custom& custom)
    // :n(name),cnt(count),custm(custom){ cout << "const reference constructor\n"; }

    Test(string name, int count, Custom custom)
    :n(name),cnt(count),custm(custom){ cout << "literal constructor"; }
};




int main(){
  string name = "kim hero";
  Custom custom = Custom(25);
  cout << "\n";
  Test t = Test(name,1,custom);
  name = "kim babo";
  cout << t.n;
}