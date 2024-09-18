#include<bits/stdc++.h>
using namespace std;
int main(){
    bitset<10> pd("1001");
    cout<<pd[0]<<endl;
    cout<<pd<<endl;
    cout<<pd.count()<<endl;
    cout<<pd.any()<<endl;
    cout<<pd.none()<<endl;
    pd.set();
    cout<<pd<<endl;
    pd.set(5,0);
    cout<<pd<<endl;
    pd.reset();
    cout<<pd<<endl;
    pd=~pd;
    cout<<pd<<endl;
    unsigned long long p=pd.to_ullong();
    cout<<p<<endl;
    return 0;
}
