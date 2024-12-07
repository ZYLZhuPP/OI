#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const int N = 505;
const lf eps = 1e-5;

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
	inline IO& operator >> (double &x) {
		double p(1); x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
		if (!(c ^ 46)) while (isdigit(c = gc())) x += (c ^ 48) * (p /= 10);
		x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

struct V {
    int w; lf o[N];
    bool operator < (const V &a) const { return w < a.w; }
} a[N];

int n, m, o[N], cnt, ans;

int main() {
    io >> n >> m;
    For (i, 1, n) For (j, 1, m) io >> a[i].o[j];
    For (i, 1, n) io >> a[i].w;
    sort(a + 1, a + n + 1);
    For (i, 1, n) {
        For (j, 1, m) if (fabs(a[i].o[j]) > eps) {
            if (!o[j]) {
                o[j] = i, cnt++, ans += a[i].w;
                break;
            } else {
                lf x = a[i].o[j] / a[o[j]].o[j];
                For (k, j, m) a[i].o[k] -= x * a[o[j]].o[k];
            }
        }
    }
    printf("%d %d", cnt, ans);

    return 0;
}
