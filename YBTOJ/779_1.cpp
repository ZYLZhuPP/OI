#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e4 + 5, _N = 205;

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

int n, T, a[N], b[N], O, B, m, ans;
int bl[_N], br[_N], be[N], cnt[_N][N], f[_N][_N], sum[N];

void init() {
    B = sqrt(n);
    m = n / B; if (m * B < n) m++;
    For (i, 1, m) bl[i] = br[i - 1] + 1, br[i] = i * B;
    br[m] = n;
    For (i, 1, m) For (j, bl[i], br[i]) be[j] = i;
    For (i, 1, m) {
        For (j, 1, O) cnt[i][j] = cnt[i - 1][j];
        For (j, bl[i], br[i]) cnt[i][a[j]]++;
    }
    For (i, 1, m) {
        int mx = 0, id = -1;
        For (j, i, m) {
            For (k, bl[j], br[j]) {
                int x = a[k], s = cnt[j][x] - cnt[i - 1][x];
                if (s > mx) mx = s, id = x;
                else if (s == mx && x < id) id = x;
            }
            f[i][j] = id;
        }
    }
}

int query(int l, int r) {
    int L = be[l], R = be[r];
    int mx = 0, id = -1;
    if (L + 1 > R - 1) {
        For (i, l, r) {
            int x = a[i];
            sum[x]++;
            if (sum[x] > mx) mx = sum[x], id = x;
            else if (sum[x] == mx && x < id) id = x;
        }
        For (i, l, r) sum[a[i]]--;
    } else {
        id = f[L + 1][R - 1];
        mx = cnt[R - 1][id] - cnt[L][id];
        For (i, l, br[L]) {
            int x = a[i];
            sum[x]++;
            int s = cnt[R - 1][x] - cnt[L][x] + sum[x];
            if (s > mx) mx = s, id = x;
            else if (s == mx && x < id) id = x;
        }
        For (i, bl[R], r) {
            int x = a[i];
            sum[x]++;
            int s = cnt[R - 1][x] - cnt[L][x] + sum[x];
            if (s > mx) mx = s, id = x;
            else if (s == mx && x < id) id = x;
        }
        For (i, l, br[L]) sum[a[i]]--;
        For (i, bl[R], r) sum[a[i]]--;
    }
    return id;
}

int main() {
    io >> n >> T;
    For (i, 1, n) io >> a[i], b[i] = a[i];
    sort(b + 1, b + n + 1); O = unique(b + 1, b + n + 1) - b - 1;
    For (i, 1, n) a[i] = lower_bound(b + 1, b + O + 1, a[i]) - b;
    init();
    while (T--) {
        int l, r;
        io >> l >> r;
        l = (l + ans - 1) % n + 1; r = (r + ans - 1) % n + 1;
        if (l > r) swap(l, r);
        printf("%d\n", ans = b[query(l, r)]);
    }

    return 0;
}
