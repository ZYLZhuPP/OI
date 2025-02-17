#include<bits/stdc++.h>
using namespace std;

const int N=5e4+5;

int n,m,L,l,r,ans,d[N];

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
    int last=0, res=0, end=n;
    while(end>0 && L-d[end]<k){
        end--; res++;
    }
    for(int i=1; i<=end; i++){
        if(d[i]-d[last]<k){
            res++;
        }else{
            last=i;
        }
    }
    return res<=m;
}

int main(){
    read(L); read(n); read(m);
    for(int i=1; i<=n; i++){
        read(d[i]);
    }
    l=0; r=L;
    while(l<=r){
        int mid=(l+r)>>1;
        if(ok(mid)){
            ans=mid; l=mid+1;
        }else r=mid-1;
    }
    printf("%d", ans);
    return 0;
}
