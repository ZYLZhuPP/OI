#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;

int n,m,ans,a[N];

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

bool ok(int k){
    int last=a[1], res=1;
    for(int i=2; i<=n; i++){
        if(a[i]-last>=k) last=a[i], res++;
    }
    return res>=m;
}

int main(){
    read(n); read(m);
    for(int i=1; i<=n; i++) read(a[i]);
    sort(a+1, a+n+1);
    int l=1, r=a[n];
    while(l<=r){
        int mid=(l+r)>>1;
        if(ok(mid)) ans=mid, l=mid+1;
        else r=mid-1;
    }
    printf("%d", ans);
    return 0;
}
