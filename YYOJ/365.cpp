#include<bits/stdc++.h>
using namespace std;

long long n,m,x,ans;

int main(){
    cin>>n>>m>>x;
    for(int i=0; i<m; i++) ans+=(i*n+x)/m;
    printf("%lld", ans);
    return 0;
}
