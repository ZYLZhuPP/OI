#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;
template<class C> inline void clear(C &a) {C().swap(a);}

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~() {return ~c;}
} io;

int T, n, m, ans;
vector<int > to[N];

int main() {
	io >> T;
	while (T--) {
		ans = 0;
		io >> n >> m;
		For (i, 1, n) clear(to[i]);
		For (i, 1, m) {
			int u, v;
			io >> u >> v;
			to[u].push_back(v);
			to[v].push_back(u);
		}
		For (i, 1, n) ans = max(ans, (int)to[i].size());
		if (ans == 2) {
			For (i, 1, n) if (to[i].size() == 2) {
				int u = to[i][0], v = to[i][1];
				for (auto &w : to[u]) if (w == v) ans = 3;
			}
		}
		
		printf("%d\n", ans);
	}
	
	return 0;
}
