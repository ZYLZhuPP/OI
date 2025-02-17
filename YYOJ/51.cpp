#include<bits/stdc++.h>
using namespace std;

const int N=2e6+5, MACH=26;
const int MATRIE=405;

int trie[MATRIE][MACH],triesiz,n,m,j,ans,pi,len,vis[N];
bool bo[MATRIE];
string a;

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

inline string reads(){
    string res="";
    char ch=gc();
    for(; !isalpha(ch); ch=gc())
        if(!(ch^EOF)) return res;
    for(; isalpha(ch); ch=gc())
        res.push_back(ch);
    return res;
}

void insert(string st){
    int len=st.length();
    int u=1;
    for(int i=0; i<len; i++){
        int c=st[i]-'a';
        if(!trie[u][c]) trie[u][c]=++triesiz;
        u=trie[u][c];
    }
    bo[u]=1;
}

void find(int pos){
    if(!(vis[pos]^pi)) return;
    vis[pos]=pi;
    ans=max(ans, pos);
    int u=1;
    for(int i=pos; i<len && u; i++){
        int c=a[i]-'a';
        u=trie[u][c];
        if(bo[u]) find(i+1);
    }
}

int main(){
    triesiz=1;
    read(n); read(m);
    for(int i=1; i<=n; i++){
        a=reads();
        insert(a);
    }
    for(pi=1; pi<=m; pi++){
        ans=0;
        a=reads();
        len=a.length();
        find(0);
        printf("%d\n", ans);
    }
    return 0;
}
