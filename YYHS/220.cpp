#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF=LLONG_MAX/3;
const int N=1e5+5;

ll n,L,a[N],s[N],ans;

#define gc() getchar()

template<class T>
inline bool read(T &x){
    x=0;
    bool f(0); 
    char ch(gc());
    for(; !isdigit(ch); f|=!(ch^45), ch=gc()) if(!(ch^EOF)) return 0;
    for(; isdigit(ch); ch=gc()) x=(x<<3)+(x<<1)+(ch^48);
    if(f) x=-x;
    return 1;
}

int main(){
    read(n); read(L);
    ll r=0;
    for(int i=1; i<=n; i++) read(a[i]), a[i]*=1000, r=max(r, a[i]);
    ll l=0;
    while(l<=r){
        ll mid=(l+r)>>1;
        for(int i=1; i<=n; i++) s[i]=s[i-1]+a[i]-mid;
        ll mi=INF, res=-INF;
        for(int i=1; i<=n; i++){
            if(i>=L) mi=min(mi, s[i-L]);
            res=max(res, s[i]-mi);
        }
        if(res>=0) ans=mid, l=mid+1;
        else r=mid-1;
    }
    printf("%lld", ans);
    return 0;
}

