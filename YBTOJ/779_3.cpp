#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, _N = 355;

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

int n, T, a[N], B, m, O, ans;
int bl[_N], br[_N], be[N], cnt[_N][N], f[_N][_N], sum[N];

void init() {
    B = sqrt(n);
    m = n / B; if (m * B < n) m++;
    For (i, 1, m) bl[i] = br[i - 1] + 1, br[i] = i * B;
    br[m] = n;
    For (i, 1, m) For (j, bl[i], br[i]) be[j] = i;
    For (i, 1, m) {
        For (j, 0, O) cnt[i][j] = cnt[i - 1][j];
        For (j, bl[i], br[i]) cnt[i][a[j]]++;
    }
    For (i, 1, m) {
        int res = 0;
        For (j, i, m) {
            For (k, bl[j], br[j]) {
                int x = a[k];
                sum[x]++;
                int s = sum[x];
                if (!(s & 1)) res++;
                else if (s > 1) res--;
            }
            f[i][j] = res;
        }
        For (j, 0, O) sum[j] = 0;
    }
}

int query(int l, int r) {
    int L = be[l], R = be[r];
    int res = 0;
    if (L + 1 > R - 1) {
        For (i, l, r) {
            int x = a[i];
            sum[x]++;
            int s = sum[x];
            if (!(s & 1)) res++;
            else if (s > 1) res--;
        }
        For (i, l, r) sum[a[i]]--;
    } else {
        res = f[L + 1][R - 1];
        For (i, l, br[L]) {
            int x = a[i];
            sum[x]++;
            int s = cnt[R - 1][x] - cnt[L][x] + sum[x];
            if (!(s & 1)) res++;
            else if (s > 1) res--;
        }
        For (i, bl[R], r) {
            int x = a[i];
            sum[x]++;
            int s = cnt[R - 1][x] - cnt[L][x] + sum[x];
            if (!(s & 1)) res++;
            else if (s > 1) res--;
        }
        For (i, l, br[L]) sum[a[i]]--;
        For (i, bl[R], r) sum[a[i]]--;
    }
    return res;
}

int main() {
    io >> n >> O >> T;
    For (i, 1, n) io >> a[i];
    init();
    while (T--) {
        int l, r;
        io >> l >> r;
        l = (l + ans) % n + 1; r = (r + ans) % n + 1;
        if (l > r) swap(l, r);
        printf("%d\n", ans = query(l, r));
    }

    return 0;
}
