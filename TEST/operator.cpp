#include<bits/stdc++.h>
using namespace std;

struct A{
    int x;
    bool operator <(const A X) const {
        return x<X.x;
    }
}a,b;

int main(){
    a.x=1; b.x=2;
    cout<<(a<b);
    return 0;
}
