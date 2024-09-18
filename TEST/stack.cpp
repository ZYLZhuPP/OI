#include<bits/stdc++.h>
using namespace std;
int main(){
    stack<int> sta={0};
    for(int i=1; i<=5; i++) sta.push(i);
    cout<<sta.size();

    while(!sta.empty()) cout<<sta.top()<<endl, sta.pop();

    return 0;
}
