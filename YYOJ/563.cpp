#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1005;

int n,m,cnt;
int a[N],sum[N];
ll f[11][N][105],ans;

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

int lowbit(int x){return x&-x;}

int main()
{
    read(n); read(m);
    for(int i=0; i<(1<<n); i++){
        if(i&(i<<1) || i&(i>>1)) continue;
        a[++cnt]=i;
        int x=i;
        while(x) sum[cnt]++,x-=lowbit(x);
    }
    for(int i=1; i<=cnt; i++) f[1][i][sum[i]]=1;
    for(int i=2; i<=n; i++)
    for(int j=1; j<=cnt; j++)
    for(int k=1; k<=cnt; k++){
        if(a[j]&a[k] || (a[j]>>1)&a[k] || (a[j]<<1)&a[k]) continue; 
        for(int l=sum[j]+sum[k]; l<=m; l++) f[i][j][l]+=f[i-1][k][l-sum[j]];
    }
    for(int i=1; i<=cnt; i++)
        ans+=f[n][i][m];
    printf("%lld", ans);
}

