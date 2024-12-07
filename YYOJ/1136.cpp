#include<bits/stdc++.h>
using namespace std;

template<class C> inline bool chkmin(C &x, const C &y) { return x>=y? x=y, 1: 0; }

typedef long long ll;

const int N = 105, Key = 4e5 + 5;
const ll INF = LLONG_MAX;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) if(!(c^45)) f=-1;
		for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

struct XX{
	ll val, key, p;
	bool operator < (const XX &x) const{ return val < x.val; }
}a[N];

ll n, o, s[N], b[Key], f[N][N][N];

int main() {
	io >> n >> o;
	for (int i = 1; i <= n; i++) io >> a[i].val;
	for (int i = 1; i <= n; i++) io >> a[i].key, b[a[i].key]++;
	for (int i = 1; i <= n; i++) io >> a[i].p;
	for (int i = 1; i <= Key; i++) b[i] += b[i-1];
	for (int i = 1; i <= n; i++) a[i].key = b[a[i].key];
	sort(a+1, a+n+1);
	for (int i = 1; i <= n; i++) s[i] = s[i-1] + a[i].p; 
	
	for (int l = 0; l < n; l++)
		for (int i = 1; i+l <= n; i++) {
			int j = i + l;
			for (int k = 1; k <= n; k++) {
				f[i][j][k] = INF;
				for (int r = i; r <= j; r++) {
					if (a[r].key >= k) chkmin(f[i][j][k], f[i][r-1][a[r].key] + f[r+1][j][a[r].key] + (s[j]-s[i-1]));
					chkmin(f[i][j][k], f[i][r-1][k] + f[r+1][j][k] + o + (s[j]-s[i-1]));
				}
			}
		}
		
	printf("%lld", f[1][n][1]);
	return 0;
}
