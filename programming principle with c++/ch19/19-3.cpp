#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<vector>

using namespace std;

template<typename T,typename U>
struct Pair{
  T key;
  U val;

  Pair(T key, U val)
  :key{key},val{val}{}
};

class Symbol_table {
  vector< Pair<string,double> > var_table;
  public:
    double get(string s);                   // return the value of the Variable named s
    void set(string s, double d);           // set the Variable named s to d
    bool is_declared(string var);           // is var already in var_table?
    double declare(string var, double val); // add (var,val) to var_table
    void print();                           // print table
};

double Symbol_table::get(string s){
  auto val = find_if(var_table.begin(),var_table.end(), [s](Pair<string,double> pair)
  ->double {if(pair.key == s) return pair.val;});

  return val->val;
}

void Symbol_table::set(string s, double d){
  auto val = find_if(var_table.begin(),var_table.end(), [s](Pair<string,double> pair)
  ->double {if(pair.key == s) return pair.val;});

  if(val != var_table.end()){
    val -> val = d;
  }
}

bool Symbol_table::is_declared(string var){
    auto val = find_if(var_table.begin(),var_table.end(), [var](Pair<string,double> pair)
  ->double {if(pair.key == var) return pair.val;});

  if(val != var_table.end()){
    return true;
  }
  return false;
}

double Symbol_table::declare(string var,double val){
  Pair<string,double> p = {var,val};
  var_table.push_back(p);
  return val;
}

void Symbol_table::print(){
  cout << '[';
  for(int i = 0; i<var_table.size();i++){
    cout << '{' << var_table[i].key << ',' << var_table[i].val << "}";
    if(i == var_table.size()-1){
      cout << "]\n";
    } 
    else cout << ',';
  }
}

int main()
try {
    Symbol_table st;
    st.declare("Pi",3.14);
    st.declare("e",2.72);
    st.print();
    cout << "Pi is " << st.get("Pi") << "\n";
    if (st.is_declared("Pi"))
        cout << "Pi is declared\n";
    else
        cout << "Pi is not declared\n";
    if (st.is_declared("nd"))
        cout << "nd is declared\n";
    else
        cout << "nd is not declared\n";
    st.set("Pi",4.14);
    cout << "Pi is now " << st.get("Pi") << "\n";

    // provoke errors
//    cout << st.get("nd") << "\n";
//    st.set("nd",99);
//    st.declare("Pi",99);
}
catch (exception& e) {
    cerr << "Exception: " << e.what() << "\n";
}
catch (...) {
    cerr << "Exception\n";
}