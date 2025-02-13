#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, B, G, a[N], b[N], tot[N], mx, ans;

int main() {
    io >> n; B = sqrt(n);
    For (i, 1, n) io >> a[i], tot[a[i]]++;
    For (i, 1, n) if (cmax(mx, tot[i])) G = i;
    For (i, 1, n) if (tot[i] > B && i ^ G) {
        int x = 0;
        For (j, 0, 2 * n) b[j] = n;
        b[n] = 0;
        For (j, 1, n) x += (a[j] == G) - (a[j] == i), cmax(ans, j - b[x + n]), cmin(b[x + n], j);
    }
    For (i, 1, B) {
        int l = 0, cnt = 0;
        For (j, 1, n) b[j] = 0;
        For (j, 1, n) {
            if (b[a[j]] == i) do cnt -= b[a[++l]]-- == i; while (a[l] ^ a[j]);
            cnt += ++b[a[j]] == i;
            if (cnt > 1) cmax(ans, j - l);
        }
    }
    printf("%d", ans);

    return 0;
}