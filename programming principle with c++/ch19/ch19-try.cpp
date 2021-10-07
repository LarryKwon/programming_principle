#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<vector>

using namespace std;

template<typename T> struct  S{
  public:
    S()
    :val{new T()}{}

    S(T t)
    :val{t}{}

    S(T& t)
    :val{t}{}

    T& get();
    T& get() const;
    void set(const T& t);
    T& operator=(const T& d);

  private:
    T val;
};

template<typename T> T& S<T>::get(){return val;}
template<typename T> T& S<T>::get() const {return val;}
template<typename T> void S<T>::set(const T& t){val = t;}
template<typename T>

istream& operator>>(istream& is, S<T>& s){
  T v;
  is >> v;
  if(!is) return is;
  s = v;
  return is;
}

template<typename T> void read_val(T& v){
  cin >> v;
}

template<typename T> T& S<T>::operator=(const T& d){
  val = d;
  return val;
}

template<typename T>
ostream& operator<<(ostream& os, const S<T>& s){
    os << s.val;
}

template<typename T> istream& operator >>(istream& is, vector<T>& v){
  char ch1,ch2;
 
  vector<T> vec_temp;
  T vv;

  is >> ch1;
  if(!is) return is;
  if(ch1 !='{'){
    is.clear(ios_base::failbit);
  }
  while(cin >> vv >> ch2 && ch2 == ','){
    vec_temp.push_back(vv);
  }
  if(ch2 != '}'){
    is.clear(ios_base::failbit);
    return is;
  }
  vec_temp.push_back(vv);
  v = vec_temp;
  return is;
}

template<typename T>ostream& operator << (ostream& os, vector<T>& v){
  os << "{ ";
  for (int i = 0; i<v.size(); ++i) {
      os << v[i];
      if (i<v.size()-1) os << ',';
      os << ' ';
  }
  os << "}";
  return os;
}



int main(){
  S<int> s_int {4};
  S<char>s_char{'a'};
  S<double> s_double{3.0};
  S<string> s_string{"hello"};
  S<vector<int>> s_vector{vector<int>(4)};

  cout << s_int.get() << '\n';
  cout << s_char.get() << '\n';
  cout << s_double.get() << '\n';
  cout << s_string.get() << '\n';
  for(auto p:s_vector.get()){
    cout << p << '\n';
  }

    // cout << "\ns_int: ";
    // read_val(s_int);
    // cout << "s_char: ";
    // read_val(s_char);
    // cout << "s_dbl: ";
    // read_val(s_double);
    // cout << "s_strg: ";
    // read_val(s_string);
    // cout << "\ns_int: " << s_int.get() << "\n";
    // cout << "s_char: " << s_char.get() << "\n";
    // cout << "s_dbl: " << s_double.get() << "\n";
    // cout << "s_strg: " << s_string.get() << "\n\n";
    
    
    cout << "\ns_v_int: ";
    read_val(s_vector);
    cout << "\ns_v_int: " << s_vector.get() << "\n";
}
