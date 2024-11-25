#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e5 + 5;

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

int n, q, b[N], B, be[N], bl[320], br[320], now[N], nxt[N], lst[320];
ull a[N], mp[N], s[N], x[N], tag[320];
ll ans[N], his[N], S[320];
vector<array<int, 2 > > qs[N];

inline ull rd() {
    static ull x = 1145141;
    return x ^= x << 13, x ^= x >> 7, x ^= x << 17;
}

template<int S>
struct Map {
    vector<pair<ull, int > > mp[S]; int stk[S], top;
    inline void add(const ull &x) {
        int y = x & (S - 1);
        for (auto &[X, v] : mp[y]) if (X == x) return void(v++);
        if (mp[y].empty()) stk[++top] = y;
        mp[y].pb({x, 1});
    }
    inline int query(const ull &x) {
        for (auto &[X, v] : mp[x & (S - 1)]) if (X == x) return v;
        return 0;
    }
    inline void clear() {
        while (top) vector<pair<ull, int > >().swap(mp[stk[top--]]);
    }
};
Map<1 << 10 > cnt[320];
Map<1 << 18 > tmp;

int main() {
    io >> n >> q;
    For (i, 1, n) io >> a[i], b[i] = a[i];
    sort(b + 1, b + n + 1); B = unique(b + 1, b + n + 1) - b - 1;
    For (i, 1, B) mp[i] = rd(), now[i] = n + 1;
    rFor (i, n, 1) a[i] = lower_bound(b + 1, b + B + 1, a[i]) - b, nxt[i] = now[a[i]], now[a[i]] = i;
    For (i, 1, n) a[i] = mp[a[i]], s[i] = s[i - 1] ^ a[i];

    B = sqrt(n);
    For (i, 1, B) bl[i] = br[i - 1] + 1, br[i] = i * B;
    br[B] = n; For (i, 1, B) For (j, bl[i], br[i]) be[j] = i;

    int l, r;
    For (i, 1, q) io >> l >> r, qs[l].pb({r, i}), ans[i] = 1ll * (r - l + 1) * (r - l + 2) >> 1;
    rFor (i, n, 1) {
        x[i] = s[i];
        int L = be[i];
        For (j, i, br[L]) {
            if (j < nxt[i]) x[j] ^= a[i];
            his[j] += x[j] == s[i - 1], S[L] += x[j] == s[i - 1];
        }
        For (j, L + 1, B) {
            if (br[j] < nxt[i]) tag[j] ^= a[i], S[j] += cnt[j].query(tag[j] ^ s[i - 1]);
            else if (bl[j] >= nxt[i]) S[j] += cnt[j].query(tag[j] ^ s[i - 1]);
            else {
                ull t = 0;
                rFor (k, lst[j] - 1, i + 1) {
                    if (br[j] < nxt[k]) t ^= a[k];
                    tmp.add(t ^ s[k - 1]);
                }
                lst[j] = i, cnt[j].clear();
                For (k, bl[j], br[j]) {
                    his[k] += tmp.query(x[k]), x[k] ^= tag[j];
                    if (k < nxt[i]) x[k] ^= a[i];
                    cnt[j].add(x[k]), his[k] += x[k] == s[i - 1], S[j] += x[k] == s[i - 1];
                }
                tag[j] = 0, tmp.clear();
            }
        }

        for (auto &[r, id] : qs[i]) {
            int R = be[r];
            if (L == R) For (j, i, r) ans[id] -= his[j];
            else {
                For (j, L, R - 1) ans[id] -= S[j];
                if (lst[R] ^ i) {
                    ull t = 0;
                    rFor (k, lst[R] - 1, i) {
                        if (br[R] < nxt[k]) t ^= a[k];
                        tmp.add(t ^ s[k - 1]);
                    }
                    lst[R] = i, cnt[R].clear();
                    For (k, bl[R], br[R]) his[k] += tmp.query(x[k]), x[k] ^= tag[R], cnt[R].add(x[k]);
                    tag[R] = 0, tmp.clear();
                }
                For (j, bl[R], r) ans[id] -= his[j];
            }
        }

        if (i == bl[L]) {
            lst[L] = i;
            For (j, bl[L], br[L]) cnt[L].add(x[j]);
        }
    }

    For (i, 1, q) printf("%lld\n", ans[i]);

    return 0;
}
