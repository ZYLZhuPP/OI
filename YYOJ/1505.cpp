#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

struct Edge {
	ll u, v, w;
	
	bool operator < (const Edge &x) const{
		return w > x.w;
	}
};

ll n, m, k, u, v, w, sum, fa[N], siz[N];
vector<Edge > q;

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

void init() {
	for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
}

int find(int u) {
	return fa[u]^u? fa[u] = find(fa[u]): u; 
}

void merge(int u, int v) {
	fa[u] = v;
	siz[v] += siz[u];
}

int main()  {
	read(n); read(m); read(k);
	for (int i = 1; i <= m; ++i) {
		read(u); read(v); read(w);
		q.push_back({u, v, w});
	}
	sort(q.begin(), q.end());
	
	init();
	
	for (auto e : q) {
		ll u = e.u, v = e.v, w = e.w;
		int fu = find(u), fv = find(v);
		if (fu ^ fv) {
			sum += siz[fu] * siz[fv];
			if (sum >= k) {
				printf("%lld", w);
				return 0;
			}
			merge(fu, fv);
		}
	}

	return 0;
}

