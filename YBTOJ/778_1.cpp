#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, M = 1e6 + 5;

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
	inline bool operator ~ () const { return ~c; }
} io;

int n, m, a[N], ans;
vector<int > b[M];

int main() {
    io >> n >> m;
    For (i, 1, n) {
        io >> a[i];
        b[a[i]].pb(i);
        if (a[i] ^ a[i - 1]) ans++;
    }
    int op, x, y;
    while (m--) {
        io >> op;
        if (op == 1) {
            io >> x >> y;
            if (x == y) continue;
            if (b[x].size() > b[y].size()) swap(b[x], b[y]);
            if (!b[y].size()) continue;
            int co = a[b[y].back()];
            for (auto &o : b[x]) ans -= (a[o - 1] == co) + (a[o + 1] == co);
            for (auto &o : b[x]) a[o] = co, b[y].pb(o);
            b[x].resize(0);
        } else if (op == 2) {
            printf("%d\n", ans);
        }
    }

    return 0;
}
