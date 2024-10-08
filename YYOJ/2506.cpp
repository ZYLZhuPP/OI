#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 10;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, a[N], dis[N], f[N][8], g[8][8], sta[N], cnt[8][256], Ans;
char s[N];
ll Cnt;
vector<array<int, 2 > > es[N];

inline void upd(int d, int c) {
    if (cmax(Ans, d)) Cnt = c;
    else if (d == Ans) Cnt += c;
}

int main() {
    io >> n;
    scanf("%s", s + 1);
    For (i, 1, n) {
        a[i] = s[i] ^ 48;
        if (i > 1) es[i - 1].pb({i, 1}), es[i].pb({i - 1, 1});
        es[n + a[i] + 1].pb({i, 0}); es[i].pb({n + a[i] + 1, 1});
    }
    For (i, 0, 7) {
        memset(dis, 31, sizeof dis);
        dis[n + i + 1] = 0;
        deque<int > q; q.pb(n + i + 1);
        while (!q.empty()) {
            int u = q.front(); q.pop_front();
            for (auto &[v, w] : es[u]) if (cmin(dis[v], dis[u] + w)) w? q.pb(v): q.push_front(v);
        }
        For (j, 1, n) f[j][i] = dis[j];
        For (j, 0, 7) if (i ^ j) g[i][j] = dis[n + j + 1] - 1;
    }
    For (i, 1, n) {
        For (j, 0, 7) sta[i] |= (f[i][j] - g[a[i]][j]) << j;
        cnt[a[i]][sta[i]]++;
    }
    For (i, 1, n) {
        int l = max(1, i - 15), r = min(n, i + 15);
        For (j, l, r) {
            int d = abs(i - j); cnt[a[j]][sta[j]]--;
            For (k, 0, 7) cmin(d, f[i][k] + f[j][k] + 1);
            upd(d, 1);
        }
        For (j, 0, 7) For (s, 0, 255) if (cnt[j][s]) {
            int d = 1e9;
            For (k, 0, 7) cmin(d, f[i][k] + g[j][k] + (s >> k & 1) + 1);
            upd(d, cnt[j][s]);
        }
        For (j, l, r) cnt[a[j]][sta[j]]++;
    }
    printf("%d %lld", Ans, Cnt >> 1);

    return 0;
}
