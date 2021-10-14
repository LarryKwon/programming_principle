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
#include<set>
#include<iomanip>
#include<numeric>

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

struct Day{
  explicit Day(int d): day(d){}
  int day;
};

ostream& operator<<(ostream& os, const Day& day){
  os << day.day;
  return os;
}

struct Month{
  explicit Month(int m): month(m){}
  int month;
};

ostream& operator<<(ostream& os, const Month& month){
  os << month.month;
  return os;
}

struct Year{
  explicit Year(int y): year(y){}
  int year;
};

ostream& operator<<(ostream& os, const Year& year){
  os << year.year;
  return os;
}

class Date{
  Day d;
  Month m;
  Year y;

  public:

  Date()
  :d(1),m(1),y(1){}

  // Date(int day, int month, int year)
  // :d(day),m(month),y(year){}

  Date(const int& day, const int& month,const int& year)
  :d(day),m(month),y(year){}

  Date(const Day& day, const Month& month, const Year& year)
  :d(day),m(month),y(year){}

  Day day()const{return d;}
  Month month()const{return m;}
  Year year()const{return y;}
};

istream& operator >> (istream& is, Date& date){
  int d;
  int m;
  int y;
  char ch1;
  char ch2;
  is >> d >> ch1 >> m >> ch2 >> y;
  if(ch1 != '.' || ch2 !='.'){
    is.clear(ios_base::failbit);
    return is;
  }
  date = Date(d,m,y);
  return is;
}

ostream& operator << (ostream& os, const Date& date){
  os << date.day() << '.' << date.month()<< '.' << date.year();
  return os;
}

class Purchase{
  string n;
  double up;
  int cnt;

  public:

  Purchase()
  :n(""),up(0),cnt(0){}

  Purchase(const string& name, const double& unit_price,const int& count)
  :n(name),up(unit_price),cnt(count){}

  string name()const {return n;}
  double unit_price()const {return up;}
  int count()const {return cnt;}
};

ostream& operator << (ostream& os, const Purchase& purchase){
  os << purchase.name()<< " | " << purchase.unit_price() << " | " << purchase.count();
  return os;
}

istream& operator >> (istream& is, Purchase& purchase){
  string name ;
  getline(is,name,'|');
  if(!is || name.size()==0) return is;
  name.pop_back();
  char ch2;
  double unit_price;
  int count;
  is >> unit_price >> ch2 >> count;
  if(!is) return is;
  if(ch2 != '|'){
    is.clear(ios_base::failbit);
    return is;
  }
  purchase = Purchase(name,unit_price,count);
  return is;
}

class Order{
  string n;
  string add;
  Date d;
  vector<Purchase> p;

  public:
    Order()
    :n(""),add(""),d(Date()),p(){}

    Order(const string& name,const string& address,const Date& date, const vector<Purchase>& purchase)
    :n(name),add(address),d(date),p(purchase){}

    string name() const {return n;}
    string address() const {return add;}
    Date date() const{return d;}
    vector<Purchase> purchases() const{return p;}
    Purchase purchase(int i) const {return p[i];}
    int n_purchases() const { return p.size(); }
};

ostream& operator <<(ostream& os, const Order& order){
  os << order.name() << '\n' << order.address()<< '\n' << order.date() << '\n';
  for(int i = 0; i<order.n_purchases();i++){
    os << order.purchase(i) << '\n';
  }
  return os;
}

istream& operator>>(istream& is, Order& order){
  string name;
  string add;
  Date date;
  vector<Purchase> purchases;
  char ch1;
  while(is >> ch1){
    if(ch1 != '\n'){
      is.unget();
      break;
    }
  }

  getline(is,name);
  if(!is)return is;

  getline(is,add);
  if(!is) return is;

  is >> date;
  if(!is) error("can't read Date");
  is.ignore();
  string line;
  while(getline(is,line) && line!=""){
    Purchase purchase;
    istringstream iss{line};
    iss>>purchase;
    purchases.push_back(purchase);
  }
  order = Order(name,add,date,purchases);
  return is;
}

template<class T>
struct Sort_by_name {
    bool operator()(const T& a, const T& b) const
    {
        return a.name() < b.name();
    }
};

// to sort any type that has a getter address() for which < is defined
template<class T>
struct Sort_by_address {
    bool operator()(const T& a, const T& b) const
    {
        return a.address() < b.address();
    }
};

template<class T>
void read_orders_from_file(T& t,const string& fname){
  ifstream ifs(fname.c_str());
  if(!ifs) error("can't open file");
  Order o;
  while (ifs>>o) {
      t.push_back(o);
  }
}

template<class Iter>
void write_orders_to_file(Iter first, Iter last, const string& fname){
  ofstream ofs(fname.c_str());
  if(!ofs) error("can't open file");
  while(first!=last){
    ofs << *first<<'\n';
    ++first;
  }
}


int main()
try {
    // read first file
    const string ifname1 = "chapter21_ex09_in1.txt";
    vector<Order> vo;
    read_orders_from_file(vo,ifname1);

    // sort by customer name and print first file to cout
    sort(vo.begin(),vo.end(),Sort_by_name<Order>());
    for (int i = 0; i<vo.size(); ++i)
        cout << vo[i] << '\n';

    // print to file
    const string ofname1 = "chapter21_ex09_out1.txt";
    write_orders_to_file(vo.begin(),vo.end(),ofname1);

    // read second file
    const string ifname2 = "chapter21_ex09_in2.txt";
    list<Order> lo;
    read_orders_from_file(lo,ifname2);

    // sort by customer address and print second file out
    cout << "---------------------------------\n\n";
    lo.sort(Sort_by_address<Order>());
    typedef list<Order>::iterator Liter;
    for (Liter it = lo.begin(); it!=lo.end(); ++it)
        cout << *it << '\n';

    // print to file
    const string ofname2 = "chapter21_ex09_out2.txt";
    write_orders_to_file(lo.begin(),lo.end(),ofname2);

    // merge into third file, sort list by customer name first
    lo.sort(Sort_by_name<Order>());
    vector<Order> vo_merge(vo.size()+lo.size());
    merge(vo.begin(),vo.end(),lo.begin(),lo.end(),vo_merge.begin(),
        Sort_by_name<Order>());
    const string ofname3 = "chapter21_ex09_out3.txt";
    write_orders_to_file(vo_merge.begin(),vo_merge.end(),ofname3);

    // Exercise 10: total value of purchases; also eliminating duplicates
    set<Order,Sort_by_name<Order>> so;
    typedef vector<Order>::iterator Viter;
    for (Viter it = vo_merge.begin(); it!=vo_merge.end(); ++it)
        so.insert(*it);

    // Print to demonstrate how duplicates were eliminated; also calculate
    // total value of Purchases
    cout << "---------------------------------\n\n";
    double val_t = 0;
    for (set<Order>::iterator it = so.begin(); it != so.end(); ++it) {
        cout << *it << '\n';
        for (int i = 0; i<(*it).n_purchases(); ++i)
            val_t += (*it).purchase(i).count() * (*it).purchase(i).unit_price();
        cout << "Running total so far: " << val_t << "\n\n";
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