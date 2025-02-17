#include<bits/stdc++.h>
using namespace std;

const int T=1e6+5;
const int INF=INT_MAX/2;

int n,t,l,r,f[T];
vector<int > R[T];

#define gc() getchar()

template<class T>
inline bool read(T &x){
    x=0;
    int f=1;
    char ch=gc();
    for(; !isdigit(ch); ch=gc())
        if(!(ch^'-')) f=-1;
        else if(!(ch^EOF)) return 0;
    for(; isdigit(ch); ch=gc()) x=(x<<3)+(x<<1)+(ch^48);
    x*=f;
    return 1; 
}

void init(){
    for(int i=1; i<=t; i++) f[i]=INF;
}

int main(){
    read(n); read(t);
    init();
    for(int i=1; i<=n; i++){
        read(l); read(r);
        R[l].push_back(r);
    }
    for(int i=1; i<=t; i++){
        for(int j=0; j<(int)R[i].size(); j++){
            r=R[i][j];
            for(int k=i; k<=r; k++) f[k]=min(f[k], f[i-1]+1);
        }
    }
    if(f[t]==INF) puts("-1");
    else printf("%d", f[t]);
    return 0;
}
