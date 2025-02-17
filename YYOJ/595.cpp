#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=15;

int T,d,n,ans,siz[N],s;
string st;

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

int dfs(int k, ll now){
    if(k>n) return (now%d)==0;
    int res=0;
    for(int i=0; i<=9; i++)if(siz[i]){
        siz[i]--;
        res+=dfs(k+1, (now<<3)+(now<<1)+i);
        siz[i]++;
    }
    return res;
}

int main(){
    read(T);
    while(T--){
        memset(siz, 0, sizeof(siz));
        cin>>st; read(d);
        n=st.size();
        for(int i=0; i<n; i++){
            s=st[i]^48;
            siz[s]++;
        }
        ans=dfs(1, 0);
        printf("%d\n", ans);
    }
    return 0;
}
