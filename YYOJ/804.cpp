#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e5+5;

bool notpri[N];
ll mipri[N],pri[N],prisiz,n;
int ans=1;

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

void init_pri(ll n){
    for(ll i=2; i<n; i++){
        if(!notpri[i]) pri[++prisiz]=mipri[i]=i;
        for(int j=1; j<=prisiz; j++){
            ll p=pri[j];
            if(p*i>=n || p>mipri[i]) break;
            notpri[i*p]=1;
            mipri[i*p]=mipri[i];
        }
    }
}

int main(){
    read(n);
    init_pri(n+2);
    for(int i=2; i<=n+1; i++)if(notpri[i]){
        ans=2;
        break;
    }
    printf("%d\n", ans);
    for(int i=2; i<=n+1; i++)if(notpri[i]) printf("2 "); else printf("1 ");
    return 0;
}
