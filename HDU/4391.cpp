#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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

int T, n, m, B, a[N], be[N], bl[350], br[350], tag[350];
unordered_map<int, int> cnt[350];

inline void upd(int l, int r, int x) {
    int o = be[l];
    if (cnt[o].size() == 1) {
        int y = cnt[o].begin()->first;
        if (y == x) return;
        For (i, bl[o], br[o]) a[i] = (l<=i && i<=r)? x: y;
        if (!(cnt[o].begin()->second -= r - l + 1)) cnt[o].clear();
        cnt[o][x] = r - l + 1;
    } else {
        For (i, l, r) {
            auto it = cnt[o].find(a[i]);
            if (it->first == x) { l++; continue; }
            if (!--(it->second)) cnt[o].erase(it);
            a[i] = x;
        }
        cnt[o][x] += r - l + 1;
    }
}

inline void Upd(int l, int r, int x) {
    int L = be[l], R = be[r];
    if (L == R) upd(l, r, x);
    else {
        For (i, L + 1, R - 1) cnt[i].clear(), cnt[i][x] = B;
        upd(l, br[L], x);
        upd(bl[R], r, x);
    }
}

inline int query(int l, int r, int x) {
    int o = be[l];
    if (!cnt[o].count(x)) return 0;
    if (cnt[o].size() == 1) return r - l + 1;
    int res = 0;
    For (i, l, r) res += a[i] == x;
    return res;
}

inline int Query(int l, int r, int x) {
    int L = be[l], R = be[r], res = 0;
    if (L == R) return query(l, r, x);
    else {
        For (i, L + 1, R - 1) res += query(bl[i], br[i], x);
        res += query(l, br[L], x) + query(bl[R], r, x);
    }
    return res;
}

int main() {
    while (~(io >> n >> m)) {
        For (i, 1, n) io >> a[i];
        B = sqrt(n);
        For (i, 1, B) tag[i] = -1, cnt[i].clear();
        For (i, 1, B) bl[i] = br[i - 1] + 1, br[i] = i * B;
        br[B] = n;
        For (i, 1, B) For (j, bl[i], br[i]) be[j] = i, cnt[i][a[j]]++;
        int op, l, r, x;
        while (m--) {
            io >> op >> l >> r >> x; l++; r++;
            if (op == 1) Upd(l, r, x);
            else if (op == 2) printf("%d\n", Query(l, r, x));
        }
    }

    return 0;
}
