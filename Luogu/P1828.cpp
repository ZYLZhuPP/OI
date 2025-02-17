#include<bits/stdc++.h>
using namespace std;

const int N=805;
const int INF=INT_MAX/3;

int n,p,m,u,v,w,ans,sum,d[N][N],cnt[N];

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
    ans=INF;
    memset(d, 31, sizeof(d));
    for(int i=1; i<=p; i++) d[i][i]=0;
}

int main(){
    read(n); read(p); read(m);
    init();
    for(int i=1; i<=n; i++){
        read(u); cnt[u]++;
    }
    for(int i=1; i<=m; i++){
        read(u); read(v); read(w);
        d[u][v]=d[v][u]=min(d[u][v], w);
    }
    for(int k=1; k<=p; k++){
        for(int i=1;i<=p; i++){
            for(int j=1; j<i; j++) if(d[i][k]+d[k][j]<d[i][j]){
                d[i][j]=d[j][i]=d[i][k]+d[k][j];
            }
        }
    }
    for(int i=1; i<=p; i++){
        sum=0;
        for(int j=1; j<=p; j++) sum+=d[i][j]*cnt[j];
        ans=min(ans, sum);
    }
    printf("%d", ans);
    return 0;
}
