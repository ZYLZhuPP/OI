#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 2e5 + 5, inf = 1e9;
template<class C > inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    bool operator ~ () const { return ~c; }
} io;

int T, n, m, ans;
vector<array<int, 3 > > es[N];

inline void add(int u, int v, int l, int r) {
    es[u].pb({-l, r, v});
}

int main() {
    io >> T;
    while (T--) {
        ans = inf;
        io >> n >> m;
        For (i, 1, m) {
            int u, v, l, r;
            io >> u >> v >> l >> r; r--;
            int x = l & 1, y = r & 1;
            add(u, v + n, l + x, r - y); add(v + n, u, l + !x, r - !y);
            add(v, u + n, l + x, r - y); add(u + n, v, l + !x, r - !y);
        }
        For (i, 1, 2 * n) sort(es[i].begin(), es[i].end());
        priority_queue<array<int, 3> > q;
        q.push({0, 0, 1});
        while (!q.empty()) {
            auto [l, r, u] = q.top(); l = -l; q.pop();
            if (u == n || u == n + n) { ans = l; break; }
            while (!es[u].empty() && -es[u].back()[0] <= r) {
                auto [L, R, v] = es[u].back(); L = -L; es[u].pop_back();
                if (R >= l) cmax(L, l), L++, R++, q.push({-L, R, v});
            }
        }
        printf("%d\n", ans<inf? ans: -1);
        For (i, 1, 2 * n) es[i].clear();
    }

    return 0;
}
