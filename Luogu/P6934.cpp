#include<bits/stdc++.h>
using namespace std;

template<class C> inline bool chkmin(C &x, const C &y) { return x>=y? x=y, 1: 0; }

typedef long long ll;

const int N = 307;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) f|=-!(c^45); 
		for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

struct XX {
	ll v, n;
	bool operator < (const XX& x) const {
		return v < x.v;
	}
};
ll f[N][N], cost[N][N], n, k;

int main() {
	io >> n >> k;
	vector<XX> a(n);
	for (auto &i : a) io >> i.v >> i.n;
	sort(a.begin(), a.end());
	
	memset(cost, 0x3f, sizeof cost);
	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;
	for (int i = 0; i < 256; i++) 
		for (int j = 0; j < n; j++) {
			ll sum = 0; cost[j][j] = 0;
			for (int x = j; x < n; x++) {
				sum += (a[x].v - i) * (a[x].v - i) * a[x].n;
				chkmin(cost[j][x], sum);
			}
		}
	
	for (int i = 0; i < n; i++) {
		f[1][i] = cost[0][i];
		for (int j = 2; j <= k; ++j) {
			for (int x = 0; x < i; ++x) 
				chkmin(f[j][i], f[j - 1][x] + cost[x + 1][i]);
		}
	}
	
	printf("%lld", f[k][n - 1]);
	return 0;
}
