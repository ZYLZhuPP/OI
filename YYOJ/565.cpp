#include<bits/stdc++.h>
using namespace std;

const int N=7;
const int NN=1e4+5;
const int N_3=729;
const int Mo=1e6;

int n,m,STA,k,ksta,kok,stasiz,x;
int p3[N],f[NN][N_3],ans,ok[N_3];

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

void init(){
    p3[0]=1;
    for(int i=1; i<=m; i++) p3[i]=p3[i-1]*3;
}

bool dif(int x, int y, int z){
    while(z--){
        if((x%3)==(y%3)) return 0;
        x/=3; y/=3;
    }
    return 1;
}

bool pd(int x){
    int y=x/3;
    return dif(x, y, m-1);
}

int main(){
    read(n); read(m);
    init();
    STA=p3[m];
    read(k);
    for(int i=0; i<m; i++) read(x), x--, (ksta*=3)+=x;
    for(int sta=0; sta<STA; sta++) if(pd(sta)) ok[++stasiz]=sta, kok+=(ksta==sta)*stasiz;
    if(k!=1) for(int i=1; i<=stasiz; i++) f[1][i]=1;
    else f[1][kok]=1;
    for(int i=2; i<=n; i++){
        for(int l=1; l<=stasiz; l++){
            for(int r=1; r<=stasiz; r++)if(dif(ok[l],ok[r],m))
                (f[i][r]+=f[i-1][l])%=Mo;
        }
        if(k==i) ksta=f[i][kok], memset(f[i], 0, sizeof(f[i])), f[i][kok]=ksta;
    }
    for(int i=1; i<=stasiz; i++) (ans+=f[n][i])%=Mo;
    printf("%d", ans);
    return 0;
}
