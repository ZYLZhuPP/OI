#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
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

const int B = 500;
int n, Q, rt[N], fa[N], a[N], be[N], tot, pt[N], pre[N], op[N], x[N], y[N];
ll s[N], ans;
vector<int > pos[N];

inline int find(int x) {
    if (rt[x]) return rt[x];
    if (fa[x] == x) return rt[x] = x;
    return rt[x] = find(fa[x]);
}

inline int Find(int x) {
    x = rt[x];
    if (fa[x] == x) return x;
    if (pre[x]) return pre[x];
    return pre[x] = Find(fa[x]);
}

int main() {
    io >> n >> Q;
    For (i, 1, n) io >> a[i], fa[i] = i;
    while (Q > 0) {
        int q = min(Q, B); Q -= B;
        For (i, 1, tot) pos[i].resize(0);
        tot = 0; For (i, 1, n) be[i] = rt[i] = s[i] = 0;
        For (i, 1, q) {
            io >> op[i] >> x[i] >> y[i];
            if (op[i] ^ 3) be[x[i]] = 1;
        }
        For (i, 1, n) if (be[i]) rt[i] = pt[be[i] = ++tot] = i;
        For (i, 1, n) {
            int r = find(i); be[i] = be[r];
            if (be[i]) pos[be[i]].pb(i);
            else s[i] = a[r];
            s[i] += s[i - 1];
        }
        For (i, 1, q) {
            if (op[i] == 1) a[x[i]] = y[i], fa[x[i]] = x[i];
            else if (op[i] == 2) fa[x[i]] = y[i];
            else {
                ans = s[y[i]] - s[x[i] - 1];
                For (j, 1, tot) pre[pt[j]] = 0;
                For (j, 1, tot) {
                    int r = Find(pt[j]);
                    ans += 1ll * a[r] * (upper_bound(pos[j].begin(), pos[j].end(), y[i]) - lower_bound(pos[j].begin(), pos[j].end(), x[i]));
                }
                printf("%lld\n", ans);
            }
        }
    }

    return 0;
}
