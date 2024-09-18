#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n,ans=-1,cnt,ma=-1;
ll pri[13]={0,2,3,5,7,11,13,17,19,23,29,31,37};

void dfs(ll now, int pr, int mr, ll cnt){
    if(now>n) return;
    if(cnt>ma || (cnt==ma && now<ans)) ans=now, ma=cnt;
    ll ne=now*pri[pr];
    for(int i=1; i<=mr && ne<=n; i++){
        dfs(ne, pr+1, i, cnt*(i+1));
        ne*=pri[pr];
    }
}

int main(){
    cin>>n;
    dfs(1,1,30,1);
    printf("%lld", ans);
    return 0;
}
