#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int M = 1e5 + 5;
const ll INF = LLONG_MAX/3;

struct Node {
	ll v, p;
	
	bool operator < (const Node &x) const{
		return v < x.v;
	}
}a[2*M];

ll n, m, x, c[4*M], v[4*M], ans, p[2*M], s;

#define gc() getchar()

template<class C>
inline bool read(C &x) {
	x=0;
	int f=1;
	char c=gc();
	for(; !isdigit(c); c=gc()) 
		if(!(c^EOF)) return 0;
		else if(!(c^45)) f=-1;
	for(; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48);
	x*=f;
	return 1;
}

int main() {
	read(n); read(m); read(x);
	for (int i = 0; i < 2*m; i++) {
		read(a[i].v);
		a[i].p = i;
	} 
	sort(a, a + 2*m);
	
	ll last = 1;
	for (int i = 0; i < 2*m; i++) {
		if (last < a[i].v) {
			v[++s] = a[i].v-1;
			v[++s] = a[i].v;
		}else if (last == a[i].v)
			v[++s] = a[i].v;
		p[a[i].p] = s;
		last = a[i].v + 1;
	}
	if (a[2*m-1].v < n) v[++s] = n;
	
	ll l = 0, r = m;
	while (l <= r) {
		ll res = 0;
		memset(c, 0, sizeof(c)); 
		ll mid = (l+r) >> 1;
		for (int i = 0; i < mid; i++) {
			c[p[i<<1]]++; c[p[i<<1|1] + 1]--;
		}
		
		ll ok = 0;
		for (int i = 1; i <= s; i++) {
			c[i] += c[i-1];
			v[i] = min(v[i], n);
			if (!c[i]) {
				if (v[i] > ok) {
					if (!x) {
						res = INF;
						break;
					}
					ll ad = (v[i] - ok + x -1) / x;
					res += ad; 
					ok += ad * x;
				}
			} else {
				ok = max(ok, v[i]);
			}
		}
		
		if (res <= mid) {
			ans = mid;
			r = mid - 1;
		} else
			l = mid + 1;
	}
	
	if (!ans) puts("Poor Douer!");
	else printf("%lld", ans);
	
	return 0; 
}

