#include<bits/stdc++.h>
using namespace std;

struct A{
    int val;
    A *nxt;
}x;

int main(){
    A *a=&x;
    a->nxt=nullptr;
    cout<<a->nxt->val;
    return 0;
}
