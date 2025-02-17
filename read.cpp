#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,mod=998244353;
int n,k,cnt,p[N],mu[N],vis[N],fac[N],inv[N],a[N],b[N],ans;
int qpow(int x,int n){
    int ans=1;
    for(;n;n>>=1,x=1ll*x*x%mod)
        if(n&1) ans=1ll*ans*x%mod;
    return ans;
}
int S2(int n,int k){
    int sum=0;
    k=min(n,k);
    for(int i=0;i<=k;i++) b[i]=((i?b[i-1]:0)+1ll*qpow(i,n)*inv[i]%mod)%mod;
    for(int i=0;i<=k;i++) sum=(sum+1ll*a[i]*b[k-i]%mod)%mod;
    return sum;
} 
signed main(){
    scanf("%d%d",&n,&k);
    if(n==1||k==1) puts("1"),exit(0);
    mu[1]=fac[0]=inv[0]=inv[1]=1;
    for(int i=2;i<=n;i++) inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
    for(int i=2;i<=n;i++){
        if(!vis[i]) p[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt&&i*p[j]<=n;j++){
            vis[i*p[j]]=1;
            if(i%p[j]==0) break;
            mu[i*p[j]]=-mu[i];
        }
    }
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%mod,inv[i]=1ll*inv[i-1]*inv[i]%mod;
    for(int i=0;i<=n;i++) a[i]=1ll*(i&1?mod-1:1)*inv[i]%mod;
    for(int i=1;i<=n;i++)
        if(mu[i]) ans=(ans+1ll*S2(n/i+(n%i!=0),k)*mu[i])%mod;
    for(int i=0;i<=n;i++) ans-=mu[i];
    printf("%d\n",(ans+mod)%mod);
    return 0;
}