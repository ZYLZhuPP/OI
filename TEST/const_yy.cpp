#include<bits/stdc++.h>
using namespace std;
int main(){
    int x=1, y=2;
    int *a=&x, *b=&y;
    int * &c=a;
    &c=b;
    cout<<(*c)<<endl;
    return 0;
}
