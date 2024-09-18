#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;

struct Len{
    int l,r;
    bool operator <(const Len X){
        return l<X.l;
    }
}g[N];

int n,len,pos,L,R,ans;
char f;

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

void init(){
    L=R=-INT_MAX/2;
}

int main(){
    read(n);
    init();
    for(int i=1; i<=n; i++){
        read(len); cin>>f;
        if(f=='L'){
            g[i].r=pos;
            g[i].l=pos-=len;
        }else{
            g[i].l=pos;
            g[i].r=pos+=len;
        }
    }
    sort(g+1, g+n+1);
    for(int i=1; i<=n; i++){
        int l=g[i].l, r=g[i].r;
        if(l<R){
            l=max(l, L);
            if(R<r) swap(r, R);
            if(l<r) ans+=r-l;
            L=max(l, r);
        }else{
            L=l; R=r;
        }
    }
    printf("%d", ans);
    return 0;
}
