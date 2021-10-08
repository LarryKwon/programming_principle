#include<iostream>
#include<sstream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<vector>
#include<list>

using namespace std;

struct Range_error : out_of_range {	// enhanced vector range error reporting
	int index;
	Range_error(int i) :out_of_range("Range error: "+to_string(i)), index(i) { }
};


inline void error(const string& s)
{
	throw runtime_error(s);
}

double* get_from_jack(int* count){
  vector<double> temp;
  double d;
  string command;
  getline(cin,command);
  istringstream ss{command};

  while(ss>>d){
    if(ss.fail()){
      return nullptr;
    }
    cout << d << " ";
    temp.push_back(d);
  }

  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  
  *count = temp.size();
  double* val = new double[*count];
  for(int i=0; i<temp.size();i++){
    val[i] = temp[i];
    // cout << val[i] << '\n';
  }

  return val;
}

vector<double>* get_from_jill(){
  double d;
  vector<double>* val = new vector<double>;
  
  string command;
  getline(cin,command);
  istringstream ss{command};
  
  while(ss >> d){
    if(ss.fail()){
      return nullptr;     
    }
    (*val).push_back(d);
  }

  cin.clear(ios_base::failbit);
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  return val;
}

template<typename iterator>
iterator high(iterator first, iterator last){
  if(first == last) error("No highest value in empty sequence");
  iterator high = first;
  for(iterator p = first;p!=last;p++){
    if(*p > *high) high = p;
  }
  return high;
}

void fct()
{
    int jack_count = 0;
    double* jack_data = get_from_jack(&jack_count);
    vector<double>* jill_data = get_from_jill();

    double* jack_high = high(jack_data,jack_data+jack_count);
    vector<double>& v = *jill_data;
    double* jill_high = high(&v[0],&v[0]+v.size());
    cout << "Jill's high " << *jill_high << "; Jack's high " << *jack_high;

    delete[] jack_data;
    delete jill_data;
}

int main()
try {
    fct();
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


