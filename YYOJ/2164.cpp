#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

struct IO {
	char c; int f;
	#define gc() getchar()
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () {	return ~c; } 
} io;

int n, m, t[N], x[N], a1[N], a2[N], b1[N], b2[N], n1, n2, id[N], ans, f[N];

namespace BIT {
	int o[N];
	#define lowbit(x) ((x) & -(x))
	inline void upd(int x, int v) { for (; x <= m; x += lowbit(x)) o[x] = max(o[x], v);	}
	inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r = max(r, o[x]); return r; }
}
using namespace BIT;

bool cmp(const int &a, const int &b) { return b1[a] < b1[b]; }

int main() {
	io >> n >> m;
	For (i, 1, m) io >> t[i];
	For (i, 1, m) io >> x[i];
	For (i, 1, m) a1[i] = b1[i] = t[i] + x[i], a2[i] = b2[i] = t[i] - x[i];
	sort(a1 + 1, a1 + m + 1); n1 = unique(a1 + 1, a1 + m + 1) - a1 - 1;
	sort(a2 + 1, a2 + m + 1); n2 = unique(a2 + 1, a2 + m + 1) - a2 - 1;
	For (i, 1, m) b1[i] = lower_bound(a1 + 1, a1 + n1 + 1, b1[i]) - a1, b2[i] = lower_bound(a2 + 1, a2 + n2 + 1, b2[i]) - a2, b2[i] = n2 + 1 - b2[i], id[i] = i;
	sort(id + 1, id + m + 1, cmp);
	int l = 1, r = 1;
	while (l <= m) {
		while (r <= m && b1[id[r]] == b1[id[l]]) r++;
		For (i, l, r - 1) {
			int u = id[i];
			f[u] = query(b2[u] - 1) + 1;
			ans = max(ans, f[u]);
		}
		For (i, l, r - 1) upd(b2[id[i]], f[id[i]]);
		l = r;
	}
	printf("%d", ans); 
	
	return 0;
} 
