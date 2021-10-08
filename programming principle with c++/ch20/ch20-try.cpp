#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<vector>
#include<list>

using namespace std;

template<class T, int N>
struct array {
    typedef T value_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef unsigned int size_type;

    T elems[N];

    iterator begin() { return elems; }
    const_iterator begin() const { return elems; }
    iterator end() { return elems+N; }
    const_iterator end() const { return elems+N; }

    size_type size() const { return N; }

    T& operator[](int n) { return elems[n]; }
    const T& operator[](int n) const { return elems[n]; }

    T* data() { return elems; }
    const T* data() const { return elems; }
};

template<class Iter>
void print(Iter f, Iter e, const string& s)
{
    cout << s << ": { ";
    while (f!=e) {
        cout << *f << ' ';
        ++f;
    }
    cout << "}\n";
}

template<typename Iter1, typename Iter2>
Iter2 cpy(Iter1 f1, Iter1 e1, Iter2 f2){
  while(f1!=e1){
    *f2 = *f1;
    ++f1;
    ++f2;
  }
  return f2;
}

int main(){
  array<int,10> a_array{0,1,2,3,4,5,6,7,8,9};
  // for(int i = 0; i<10; i++){
  //   a_array[i] = i;
  // }
  print(a_array.begin(),a_array.end(),"a_array");

  vector<int> a_vec{0,1,2,3,4,5,6,7,8,9};
  print(a_vec.begin(),a_vec.end(),"a_vec");
  list<int> a_list{0,1,2,3,4,5,6,7,8,9};
  print(a_list.begin(),a_list.end(),"a_list");

  array<int,10> a_array_copy(a_array);
  print(a_array_copy.begin(),a_array_copy.end(),"a_array_copy");
  
  vector<int> a_vec_copy(a_vec);
  print(a_vec_copy.begin(),a_vec_copy.end(),"a_vec_copy");
  
  list<int> a_list_copy(a_list);
  print(a_list_copy.begin(),a_list_copy.end(),"a_list_copy");

  for(array<int,10>::iterator p = a_array.begin(); p!=a_array.end();p++){
    *p +=2;
  }
  print(a_array.begin(),a_array.end(),"a_array +2");
  
  for(auto& p:a_vec){
    p += 3;
  }
  print(a_vec.begin(),a_vec.end(),"a_vec +3");

  for(auto& p:a_list){
    p+= 5;
  }
  print(a_list.begin(),a_list.end(),"a_list +3");

  cpy(a_array.begin(),a_array.end(),a_vec.begin());
  print(a_array.begin(),a_array.end(),"copy a_array onto a_vec: a_array");
  print(a_vec.begin(),a_vec.end(),"copy a_array onto a_vec: a_vec");

  cpy(a_list.begin(),a_list.end(),a_array.begin());
  print(a_list.begin(),a_list.end(),"copy a_list onto a_array: a_list");
  print(a_array.begin(),a_array.end(),"copy a_list onto a_array: a_array");

  auto item = find(a_vec.begin(),a_vec.end(),3);
  if(item != a_vec.end()){
    cout << "pos: " << item - a_vec.begin();
  }
}