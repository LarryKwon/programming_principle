#include<iostream>
#include<fstream>
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

inline void error(const string& s, const string& s2)
{
	error(s+s2);
}



using Line = vector<char>;

class Text_iterator {
  list<Line>::iterator ln;
  Line::iterator pos;

  public:
    Text_iterator(list<Line>::iterator ll, Line::iterator pp)
    : ln{ll},pos{pp}{ }

    char& operator*(){ return *pos; }
    Text_iterator& operator++();
    
    bool operator==(const Text_iterator& other) const
    { return ln==other.ln && pos==other.pos; }

    bool operator!=(const Text_iterator& other) const 
    {return !(*this==other); }

    list<Line>::iterator get_line(){ return ln; }
    Line::iterator get_pos() {return pos;}
};

Text_iterator& Text_iterator::operator++(){
  ++pos;
  if(pos==(*ln).end()){
    ln++;
    pos = (*ln).begin();
  }
  return *this;
}

namespace ch20{
  template<typename T, typename Iterator>
  Iterator find(Iterator first, Iterator last, const T& c){
    Iterator p = first;
    while(p!=last){
      if(*p == c){
        return p;
      }
      ++p;
    }
    return p;
  }

  template<typename T, typename Iterator>
  bool match(Iterator first, Iterator last, const T& find_str){
    string::const_iterator si = find_str.begin();
    while(true){
      if(si == find_str.end()){break;}
      if(first==last){return false;}
      if(*first != *si){return false;}
      ++first;
      ++si;
    }
    return true;
  }
}
Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& find_str);

struct Document{
  list<Line> line;
  Document(){line.push_back(Line());}

  Text_iterator begin(){return Text_iterator(line.begin(),(*line.begin()).begin());}
  
  Text_iterator end(){ 
    auto last = line.end();
    --last;  
    return Text_iterator(last,(*last).end());
  }
  
  void find_replace(Text_iterator first, Text_iterator last,
    const string& find_str, const string& repl_str);

  Text_iterator erase(Text_iterator p);  
};

Text_iterator Document::erase(Text_iterator p){
  if(p == end()) return p;
  list<Line>::iterator list_it = p.get_line();
  Line::iterator line_it = p.get_pos();
  line_it = (*list_it).erase(line_it);
  return Text_iterator(list_it, line_it);
}

void print(Document& d);

void print(Document& d, Text_iterator p);


void Document::find_replace(Text_iterator first, Text_iterator last, const string& find_str, const string& repl_str){
  if(find_str == "") return ;
  Text_iterator pos = find_txt(first,last,find_str);
  while (pos!=last) {
    string::const_iterator repl_start = repl_str.begin();
    string::const_iterator find_start = find_str.begin();
    int find_length = find_str.size();
    int repl_length = repl_str.size();
    cout << find_length << repl_length;

    if(find_length >= repl_length){
      while(repl_start != repl_str.end()){
        // if(*repl_start == '\n')
        // if(*find_start == '\n')
        *pos = *repl_start;
        ++repl_start;
        ++find_start;
        ++pos;
      }

      while(find_start != find_str.end()){
        erase(pos);
        ++find_start;
      }
    }
    //case:: 바꾸는게 더 길 수도 -> 추가되는 부분을 추가
    // 바꾸다가 줄이 바뀌면..?
    // -> find에서 줄 바꿈 or 찾은거에서 줄 바꿈
    /*
    if(find_length < repl_length){
      while(find_start != find_str.end()){
        if(*repl_start == '\n')
        if(*find_start == '\n')
        *pos = *repl_start;
        ++repl_start;
        ++find_start;
        ++pos;
      }

        while(repl_start != repl_str.end()){
        if((*repl_start)=='\n'){ }
        erase(pos);
        ++repl_start;
      }
    }
    */
    pos = find_txt(pos,last,find_str);
  }
}

istream& operator>>(istream& is,Document& d){
  for(char ch; is.get(ch);){
    d.line.back().push_back(ch);
    if(ch=='\n'){
      d.line.push_back(Line{});
    }
  }
  if(d.line.back().size()) d.line.push_back(Line{});
  return is;
}

void print(Document& d)
{
  for (Text_iterator p = d.begin(); p!=d.end(); ++p) cout << *p;
}

void print(Document& d, Text_iterator p){
  for(;p!=d.end();++p)cout << *p;
  cout << '\n';
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& find_str){
  if(first == last) return last;
  if(find_str.size()==0) return last;

  int i = 0;
  int size = find_str.size();

  string::const_iterator si = find_str.begin();
  char first_find = find_str[0];

  while(true){
    if(first == last || si == find_str.end()){
      break;
    }
    Text_iterator first_pos = ch20::find(first,last,first_find);
    if(first_pos == last|| ch20::match(first,last,find_str)){
      return first_pos;
    }
    ++first;
  }
  return last;
}

int main()
try {
    string ifname = "chapter20_ex06_in.txt";
    ifstream ifs(ifname.c_str());
    if (!ifs) error("can't open file ",ifname);
    Document my_doc;
    ifs >> my_doc;
    // print(my_doc,my_doc.begin());

    // cout << "Searching for non-existing string 'wrong':\n\n";
    // string f_str = "wrong";
    // Text_iterator p = find_txt(my_doc.begin(),my_doc.end(),f_str);
    // if (p==my_doc.end())
    //     cout << "not found";
    // else
    //     print(my_doc,p);

    // cout << "\n\nSearching for 'Proin\\neget':\n\n";
    // f_str = "Proin\neget";
    // p = find_txt(my_doc.begin(),my_doc.end(),f_str);
    // if (p==my_doc.end())
    //     cout << "not found";
    // else
    //     print(my_doc,p);

    cout << "Replace 'dolor' with 'FR':\n\n";
    string f_str = "dolor";
    string r_str = "FR";
    my_doc.find_replace(my_doc.begin(),my_doc.end(),f_str,r_str);
    print(my_doc,my_doc.begin());

    // cout << "Replace 'est\\nmollis' with 'XYZ\\nABCDEF' (same length, \\n in "
    //     << "same place):\n\n";
    // f_str = "est\nmollis";
    // r_str = "XYZ\nABCDEF";
    // my_doc.find_replace(my_doc.begin(),my_doc.end(),f_str,r_str);
    // print(my_doc,my_doc.begin());

    // cout << "Replace 'Morbi\\ndapibus' with 'MORBI DAPIBUS' (same length, \\n is "
    //     << "removed):\n\n";
    // f_str = "Morbi\ndapibus";
    // r_str = "MORBI DAPIBUS";
    // my_doc.find_replace(my_doc.begin(),my_doc.end(),f_str,r_str);
    // print(my_doc,my_doc.begin());

    // cout << "Replace 'turpis' with 'TU\\nPIS' (same length, \\n is added):\n\n";
    // f_str = "turpis";
    // r_str = "TU\nPIS";
    // my_doc.find_replace(my_doc.begin(),my_doc.end(),f_str,r_str);
    // print(my_doc,my_doc.begin());

    // cout << "Replace 'Proin\\neget' with 'ABC\\nDEF\\nGHI' (different length, "
    //     << "\\n in different places, extra \\n):\n\n";
    // f_str = "Proin\neget";
    // r_str = "ABC\nDEF\nGHI";
    // my_doc.find_replace(my_doc.begin(),my_doc.end(),f_str,r_str);
    // print(my_doc,my_doc.begin());

    // cout << "Replace complete third line plus word before and after with "
    //     << "\\nTHIRDLINE\\n:\n\n";
    // f_str = "massa\nposuere lorem, sed placerat orci tortor quis leo.\nDonec ";
    // r_str = "\nTHIRDLINE\n";
    // my_doc.find_replace(my_doc.begin(),my_doc.end(),f_str,r_str);
    // print(my_doc,my_doc.begin());

    // cout << "Replace 'et' with 'MARATHON' (multiple occurrences):\n\n";
    // f_str = "et";
    // r_str = "MARATHON";
    // my_doc.find_replace(my_doc.begin(),my_doc.end(),f_str,r_str);
    // print(my_doc,my_doc.begin());

    // cout << "Number of characters in this document: "
    //     << char_count(my_doc) << "\n";

    // cout << "Number of words (whitespace-separated) in this document: "
    //     << word_count1(my_doc) << "\n";

    // cout << "Number of words (sequences of alphabetic characters) in this "
    //     << "document: " << word_count2(my_doc) << "\n";

    // cout << "Number of words separated by whitespace or \".!'\" in this "
    //     << "document: " << word_count3(my_doc,".!'") << "\n";
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

