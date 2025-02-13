#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5, _N = 1e3 + 5;

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

int n, m, Q, B, a[N], b[N];
int bl[_N], br[_N], be[N], ad[_N];

void upd(int x) {
    For (i, bl[x], br[x]) b[i] = a[i];
    sort(b + bl[x], b + br[x] + 1);
}

void init() {
    B = sqrt(n);
    m = n / B; if (m * B < n) m++;
    For (i, 1, m) bl[i] = br[i - 1] + 1, br[i] = i * B;
    br[m] = n;
    For (i, 1, m) For (j, bl[i], br[i]) be[j] = i;
    For (i, 1, m) upd(i);
}

void add(int l, int r, int v) {
    int L = be[l], R = be[r];
    if (L == R) {
        For (i, l, r) a[i] += v;
        upd(L);
    } else {
        For (i, L + 1, R - 1) ad[i] += v;
        For (i, l, br[L]) a[i] += v;
        For (i, bl[R], r) a[i] += v;
        upd(L); upd(R);
    }
}

int get(int x, int v) {
    v -= ad[x];
    int l = bl[x], r = br[x], res = 0;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (b[m] >= v) res = br[x] - m + 1, r = m - 1;
        else l = m + 1;
    }
    return res;
}

int query(int l, int r, int v) {
    int L = be[l], R = be[r], res = 0;
    if (L == R) {
        For (i, l, r) if (a[i] + ad[L] >= v) res++;
    } else {
        For (i, L + 1, R - 1) res += get(i, v);
        For (i, l, br[L]) if (a[i] + ad[L] >= v) res++;
        For (i, bl[R], r) if (a[i] + ad[R] >= v) res++;
    }
    return res;
}

int main() {
    io >> n >> Q;
    For (i, 1, n) io >> a[i];
    init();
    char op[3];
    int l, r, v;
    while (Q--) {
        scanf("%s", op);
        io >> l >> r >> v;
        if (op[0] == 'M') add(l, r, v);
        else printf("%d\n", query(l, r, v));
    }

    return 0;
}
