#include<iostream>
#include<cstdlib>
#include<string>
#include <cmath>
#include<algorithm>
#include<vector>

using namespace std;

int main(){
    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    cout << "Addresses on stack:\n" << &i1 << "\n" << &i2 << "\n" << &i3 << "\n";
    int stack_diff = &i2 - &i1;
    if (stack_diff>0) cout << "Stack grows up\n";
    else cout << "Stack grows down\n";

    // determine heap growth direction
    int* ip1 = new int(0);
    int* ip2 = new int(0);
    int* ip3 = new int(0);
    cout << "Addresses on heap:\n" << ip1 << "\n" << ip2 << "\n" << ip3 << "\n";
    int heap_diff = ip2 - ip1;
    if (heap_diff>0) cout << "Heap grows up\n";
    else cout << "heap grows down\n";

}