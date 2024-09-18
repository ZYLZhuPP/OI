#include<bits/stdc++.h>
#define int long long
#define up(i,l,r) for(int i=l; i<=r; ++i)
#define dn(i,r,l) for(int i=r; i>=l; --i)
#define pb push_back

using namespace std;

const int N=5005, P=998244353;

int n, cnt1[N], cnt2[N], siz[N], f[N][N], Ans, g[N], mul[N], inv[N];
char opt[N]; vector<int> to[N];

void solve(int x,int fad) {
	f[x][0]=1, ++siz[x];
	if(opt[x]=='1') ++cnt1[x]; else ++cnt2[x];
	for(int y:to[x]) if(y!=fad) {
		solve(y,x);
		up(i,0,siz[x]) up(j,0,siz[y]) (g[i+j]+=f[x][i]*f[y][j]%P)%=P;
		up(i,0,siz[x]+siz[y]) f[x][i]=g[i], g[i]=0;
		cnt1[x]+=cnt1[y], cnt2[x]+=cnt2[y], siz[x]+=siz[y];
	}
	if(opt[x]=='1') dn(i,siz[x],1) if(cnt2[x]-i+1>0) (f[x][i]+=f[x][i-1]*(cnt2[x]-i+1)%P)%=P;
	if(opt[x]=='0') dn(i,siz[x],1) if(cnt1[x]-i+1>0) (f[x][i]+=f[x][i-1]*(cnt1[x]-i+1)%P)%=P;
}

int C(int n,int m) {
	if(n<m||m<0) return 0;
	return mul[n]*inv[m]%P*inv[n-m]%P;
}

signed main() {
//	freopen("s.in","r",stdin);
//	freopen("s.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	mul[0]=inv[0]=inv[1]=1;
	up(i,1,5000) mul[i]=mul[i-1]*i%P;
	up(i,2,5000) inv[i]=inv[P%i]*(P-P/i)%P;
	up(i,2,5000) inv[i]=inv[i-1]*inv[i]%P;
	cin >> n >> (opt+1);
	up(i,2,n) {
		int u, v; cin >> u >> v;
		to[u].pb(v), to[v].pb(u);
	}
	solve(1,0);
	up(k,0,n/2) {
		Ans=0;
		up(i,k,n/2) {
			int val=f[1][i]*C(i,k)%P*mul[n/2-i]%P;
			if((i-k)%2==0) Ans=(Ans+val)%P; else Ans=(Ans-val)%P; 
		}
		cout << (Ans%P+P)%P << '\n';
	}
	return 0;
}
