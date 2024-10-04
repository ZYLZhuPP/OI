#include<bits/stdc++.h>
using namespace std;

int main() {
    bitset<10 > a("1001");
    cout << a[0] << endl;
    cout << a << endl;
    cout << a.count() << endl;
    cout << a.any() << endl;
    cout << a.none() << endl;
    a.set(); cout << a << endl;
    a.set(5, 0); cout << a << endl;
    a.reset(); cout << a << endl;
    a = ~a; cout << a << endl;
    cout << a.to_ullong() << endl;
    a = 4; cout << a._Find_first() << endl;
    a >>= 5; cout << a << endl;

    return 0;
}
