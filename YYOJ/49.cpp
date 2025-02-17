#include<bits/stdc++.h>
using namespace std;

const int N=4e5+5, MACH=2;

int T,n,trie[N<<5][MACH],triesiz;
int x,l[N],r[N],a[N],ans;

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

int find(int x){
    int u=0;
    int res=0;
    for(int i=1<<30; i; i>>=1){
        int ch=(x&i)?1:0;
        if(trie[u][!ch]) res|=i, u=trie[u][!ch];
        else u=trie[u][ch];
    }
    return res;
}

void insert(int x){
    int u=0;
    for(int i=1<<30; i; i>>=1){
        int ch=(x&i)?1:0;
        if(!trie[u][ch]) trie[u][ch]=++triesiz;
        u=trie[u][ch];
    }
}

int main(){
    read(n);
    insert(0);
    for(int i=1; i<=n; i++){
        read(a[i]);
        x^=a[i];
        insert(x);
        l[i]=max(l[i-1], find(x));
    }
    memset(trie, 0, sizeof(trie));
    triesiz=0;
    x=0;
    insert(0);
    for(int i=n; i>=1; i--){
        x^=a[i];
        insert(x);
        r[i]=max(r[i+1], find(x));
        if(i^n) ans=max(ans, l[i]+r[i+1]);
    }
    printf("%d", ans);
    return 0;
} 
