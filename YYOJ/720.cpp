#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int N=2e6+5;
const ull Mo=1e6+9;

ull n,val[N],x;
int head[Mo],nxt[N],id[N],hashsiz,t,ans,same;

#define gc() getchar()

template<class T>
inline bool read(T &x){
    x=0;
    int f=1;
    char ch=gc();
    for(; !isdigit(ch); ch=gc())
        if(!(ch^'-')) f=-1;
        else if(!(ch^EOF)) return 0;
    for(; isdigit(ch); ch=gc())
        x=(x<<3)+(x<<1)+(ch^48);
    x*=f;
    return 1;
}

void insert(ull x, int _id){
    ull u=x%Mo;
    nxt[++hashsiz]=head[u];
    val[hashsiz]=x;
    id[hashsiz]=_id;
    head[u]=hashsiz;
}

int find(ull x){
    ull u=x%Mo;
    ull v;
    for(int i=head[u]; i, v=val[i]; i=nxt[i])if(v==x) return id[i];
    return 0;
}

int main(){
    read(n);
    for(int i=1; i<=n; i++){
        read(x);
        same=max(same, find(x));
        ans=max(ans, i-same);
        insert(x,i);
    }
    printf("%d", ans);
    return 0;
}
