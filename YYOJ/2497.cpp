#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

namespace BIT {
    struct Node {
        int s, c;
        Node operator + (const Node &a) const { return {mo(s+a.s), mo(c+a.c)}; }
        Node operator - (const Node &a) const { return {mo(s-a.s), mo(c-a.c)}; }
    } o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, Node d) { for (; x < N; x += lowbit(x)) o[x] = o[x] + d; }
    inline Node query(int x) { Node r = {0, 0}; for (; x; x -= lowbit(x)) r = r + o[x]; return r; }
}
using namespace BIT;

int n, K, Ans, a[N], s[N], b[N], B, w[N], ans[N];
vector<int > pos[N];
vector<array<int, 2 > > op[N];

inline Node Query(int x) { return query(upper_bound(b + 1, b + B + 1, x) - b - 1); }

int main() {
    io >> n >> K; Ans = Mo - 1ll * n * (n + 1) / 2 % Mo;
    For (i, 1, n) io >> a[i], s[i] = (s[i - 1] + a[i]) % K, b[i] = s[i];
    b[n + 1] = 0;
    sort(b + 1, b + n + 2); B = unique(b + 1, b + n + 2) - b - 1;
    For (i, 0, n) s[i] = lower_bound(b + 1, b + B + 1, s[i]) - b, pos[s[i]].pb(i);
    For (i, 1, B) {
        int n = pos[i].size();
        add(Ans, 1ll * n * (n - 1) / 2 % Mo);
        For (j, 0, n - 1) if (j) {
            int l = pos[i][j - 1], r = pos[i][j];
            op[r + 1].pb({l, -1}); op[l + 1].pb({l, 1});
            w[l] = ml(j, n - j);
        }
    }
    rFor (i, n, 0) {
        upd(s[i], {b[s[i]], 1});
        for (auto &[id, k] : op[i]) {
            int x = b[s[id]], res = 0;
            if (x + K / 2 < K) {
                int y = x + K / 2;
                Node v1 = Query(x - 1);
                add(res, mo(ml(v1.c, x) - v1.s));
                Node v2 = Query(y) - v1;
                add(res, mo(v2.s - ml(v2.c, x)));
                Node v3 = query(B) - v1 - v2;
                add(res, mo(ml(v3.c, x + K) - v3.s));
            } else {
                int y = x + K / 2 - K;
                Node v1 = Query(y);
                add(res, mo(ml(v1.c, K - x) + v1.s));
                Node v2 = Query(x - 1) - v1;
                add(res, mo(ml(v2.c, x) - v2.s));
                Node v3 = query(B) - v1 - v2;
                add(res, mo(v3.s - ml(v3.c, x)));
           }
           add(ans[id], k * res);
        }
    }
    For (i, 0, n) add(Ans, ml(ans[i], w[i]));
    printf("%d", Ans);

    return 0;
}
