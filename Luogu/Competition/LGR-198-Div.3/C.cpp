#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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
	inline bool operator ~ () { return ~c; }
} io;

int n, m, x[N], t[N], mx1, mx2, mx3, id11, id12, id21, id22;
set<array<int, 3 > > se;

int main() {
    mx1 = mx2 = mx3 = -1;
    io >> n >> m;
    For (i, 1, n) {
        io >> x[i] >> t[i];
        se.insert({t[i], x[i], i});
    }
    int lt = -1, lx = 0, lid = 0;
    for (auto &[t, x, id] : se) {
        if (~lt) {
            int y = abs(x - lx) / abs(t - lt);
            if (y > mx1) mx3 = mx2, mx2 = mx1, mx1 = y, id21 = id11, id22 = id12, id11 = id, id12 = lid;
            else if (y > mx2) mx3 = mx2, mx2 = y, id21 = id, id22 = lid;
            else if (y > mx3) mx3 = y;
        }
        lt = t, lx = x, lid = id;
    }

            
    while (m--) {
        int a, b;
        io >> a >> b;
        int y = -1;
        if (a > 1 && a < n) y = abs(x[a - 1] - x[a + 1]) / abs(t[a - 1] - t[a + 1]);
        se.erase({t[a], x[a], a});
        auto it = se.upper_bound({b, x[a], 0});
        if (it != se.begin()) {
            auto u = prev(it);
            y = max(y, abs(x[a] - (*u)[1]) / abs(b - (*u)[0]));
        }
        if (it != se.end()) {
            y = max(y, abs(x[a] - (*it)[1]) / abs(b - (*it)[0]));
        }
        if (id11 != a && id12 != a) y = max(y, mx1);
        if (id21 != a && id22 != a) y = max(y, mx2);
        y = max(y, mx3);
        printf("%d\n", y);
        se.insert({t[a], x[a], a});
    }

    return 0;
}
