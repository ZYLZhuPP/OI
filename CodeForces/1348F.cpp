#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

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
	inline bool operator ~ () const { return ~c; }
} io;

int n, l[N], r[N], a[N], pos[N], f[N][20];
vector<array<int, 2 > > qs[N];
priority_queue<array<int, 2 > > q;

inline int lmin(int x, int y) { return l[pos[x]]<l[pos[y]]? x: y; }

inline int query(int i, int x) {
    int r = 0;
    while (x) {
        int k = __builtin_ctz(x);
        r = lmin(r? r: f[i][k], f[i][k]);
        i += 1 << k; x ^= 1 << k;
    }
    return r;
}

inline void out() {
    For (i, 1, n) a[pos[i]] = i;
    For (i, 1, n) printf("%d ", a[i]);
    puts("");
}

int main() {
    io >> n;
    For (i, 1, n) io >> l[i] >> r[i], qs[l[i]].pb({r[i], i});
    For (i, 1, n) {
        for (auto &[r, id] : qs[i]) q.push({-r, id});
        pos[i] = q.top()[1]; q.pop();
    }
    For (i, 1, n) f[i][0] = i + 1;
    For (j, 1, 19) For (i, 1, n - (1 << j)) f[i][j] = lmin(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    For (i, 1, n) if (r[pos[i]] > i) {
        int x = query(i, r[pos[i]] - i);
        if (l[pos[x]] <= i) {
            puts("NO");
            out(); swap(pos[i], pos[x]); out();
            return 0;
        }
    }
    puts("YES"); out();

    return 0;
}
