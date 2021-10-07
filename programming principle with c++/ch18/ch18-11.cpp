#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<stdexcept>
#include<vector>

using namespace std;

struct element{
  element(int key, int height)
  :key{key}, pointers(height){}
  int key;
  vector<element *> pointers;
};

class skip_list{
  public:
    skip_list()
    :first{new element(0, max_height)}, last{new element(infty,max_height)},height{0}{
      for(int i = 0; i < first->pointers.size();i++){
        first->pointers[i] = last;
      }
    }

    skip_list(element& v)
    :first{&v},last{nullptr},height{(int)v.pointers.size()}{}

    void insert(int k);
    void  remove(int k);
    element* find(int k);
    void print();
    void debug_print();
    int get_height() { return height; }

  private:
    const int max_height = 16;
    const int infty = numeric_limits<int>::max();
    element* first;
    element* last;
    int height;
    int random_height();
};

void skip_list::print(){
  element* p = first;
  cout << "{";
  while(p->key != infty){
    cout << " " << p-> key;
    p = p->pointers[0];
  }
  cout << "} \n";
}

void skip_list::debug_print(){
  for(int i = 0; i<height;i++){
    element* p = first;
    cout << "lvel" << i << "{ ";
    while(p->key != infty){
      if (p->pointers.size() > i)
          cout << ' ' << p->key;
      else
          cout << "   ";
      p = p->pointers[0];
    }
    cout << "} \n";
  }
}


// template<typename Elem>
// struct Link{
//   Link* prev;
//   Link* succ;
//   Elem val;

//   Link(Elem& val = Elem(), Link* p = nullptr, Link* s = nullptr)
//   :val{val},prev{p},succ{s}{}
// };

// template<typename Elem>
// class list{
//   Link<Elem>* first;
//   Link<Elem>* last;
  
//   public:
//     list()
//     :first{new Link<Elem>()},last{first}
//     {}

//     list(Link<Elem>& node)
//     :first{node},last{nullptr},iterator{node}
//     {}

//     class iterator;

//     iterator begin();
//     iterator end();

//     iterator insert(iterator p, const Elem& v);
//     iterator erase(iterator p);

//     void push_back(const Elem& v);
//     void push_front(const Elem& v);
//     void pop_front();
//     void pop_back();

//     Elem& front();
//     Elem& back();
// };

// template<typename Elem>
// class list<Elem>::iterator{
//   Link<Elem>* curr;

//   public:
//     iterator(Link<Elem>* p): curr{p} {}

//     iterator& operator++(){ curr = curr ->succ; return *this;}
//     iterator& operator--(){ curr = curr->prev; return *this;}
//     Elem& operator*() { return curr->val;}

//     bool operator==(const iterator& b) const { return curr == b.curr; }
//     bool operator!=(const iterator& b) const { return curr != b.curr; }

// };

// template<typename Elem> 
// typename list<Elem>::iterator list<Elem>::begin() 
// { 
//     return iterator(first); 
// }

// template<typename Elem>
// typename list<Elem>::iterator list<Elem>::end()
// {
//   return iterator(last);
// }

// template<typename Elem>
// void list<Elem>::push_back(const Elem &v){
//   last =  new Link<Elem>(v,last,nullptr);
// }

// template<typename Elem>
// void list<Elem>::push_front(const Elem &v){
//   first = new Link<Elem>(v,nullptr,first);
// }

// template<typename T>
// void user(list<T>& lst){
//   auto q = find(lst.begin(),lst.end(),T{42});
// }


int main()
try {
    srand(time(0));
    const int test_val = 75;
    while (true) {
        skip_list sl;
        for (int i = 0; i<23; ++i)
            sl.insert(randint(100));
        sl.debug_print();
        cout << "Enter value to remove: ";
        int x;
        cin >> x;
        if (x==-1) return 0;

        element* p = sl.find(x);
        sl.remove(x);
        sl.debug_print();
        cout << "\n";
    }
}
catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
}
catch (...) {
    cerr << "exception\n";
}