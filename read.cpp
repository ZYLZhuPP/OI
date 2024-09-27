#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
typedef long long ll;

const int N=7510;

int n,P,P2,T[N][N],mk[N],dp[N];
ll qpow(ll x,ll k) {
	ll res=1;
	for(;k;k>>=1,x=x*x%P) if(k&1) res=res*x%P;
	return res;
}
int Calc(int x){
	int m=n/x,s=P2-1;
	//s = 1ll * s * T[m * x + 1][n] % P2;
	rep(i,1,m) {
		s=1ll*s*T[(i-1)*x+1][i*x-1]%P2;
		dp[i]=P2-s;
		s=1ll*s*(i * x - 1)%P2;
	}
	int ans=0;
	rep(i,1,m) ans=(ans+1ll*dp[i]*T[i*x+1][n])%P2;
    s = 1ll * s * T[m * x + 1][n] % P2;
    s = (s + T[1][n]) % P2;
    cerr << s << " " << ans << endl;
	return ans;
}

int main(){
	scanf("%d%d",&n,&P),P2=P-1;
	rep(i,2,n) if(!mk[i]) {
		for(int j=i;j<=n;j+=i) mk[j]=1;
		for(int j=i;j<=n;j*=i) mk[j]=i;
	}
	rep(i,1,n+1){
		T[i][i-1]=1;
		rep(j,i,n) T[i][j]=1ll*T[i][j-1]*j%P2;
	}
	int ans=1;
	rep(i,2,n) if(mk[i]>1) ans=ans*qpow(mk[i],Calc(i))%P;
	printf("%d\n",ans);
}