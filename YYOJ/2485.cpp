#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll INF = 1e18;
const int N = 3e5 + 5;

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

int n, D, a[N], q[N], b[N], pre[N][2], del[N];
char s[N];

inline bool ok(int K) {
    For (i, 1, K) b[q[i]] = 2;
    For (i, K + 1, n) b[q[i]] = 0;
    int shown = 0, decoded = K, rest = 0;
    ll cur = 0, nxt_decode = INF;
    auto Del = [&](int u) {
        if (!u || b[u] ^ 3 || decoded < del[u]) return 0;
        b[u] = 4; rest++; return 1;
    };
    while (shown < n) {
        ll nxt_show = 1ll * shown * D;
        if (nxt_decode <= nxt_show) {
            cur = nxt_decode;
            nxt_decode = INF;
            int u = q[++decoded];
            b[u] = 2; Del(pre[u][0]); Del(pre[u][1]);
        } else {
            cur = nxt_show;
            int u = ++shown;
            if (b[shown] ^ 2) return 0;
            b[u] = 3; Del(u);
        }
        if (nxt_decode == INF && rest && decoded < n) {
            int u = q[decoded + 1];
            b[u] = 1; rest--; nxt_decode = cur + a[u];
        }
    }
    return 1;
}

int main() {
    io >> n >> D;
    scanf("%s", s + 1);
    For (i, 1, n) io >> a[i];
    q[1] = 1;
    for (int l = 1, r = 1; l <= n; l = r) {
        while (s[++r] == 'B');
        q[l + 1] = r;
        if (s[r] == 'P') pre[r][0] = l;
        For (i, l + 1, r - 1) q[i + 1] = i, pre[i][0] = l, pre[i][1] = r;
        if (r - l > 1 || s[r] == 'P') del[l] = r;
    }
    int l = 1, r = n, ans = n;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (ok(m)) ans = m, r = m - 1;
        else l = m + 1;
    }
    printf("%d", ans);

    return 0;
}
