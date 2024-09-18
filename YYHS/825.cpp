#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
template<class C> inline bool ckmax(C &x, const C &y) { return x<y? x=y, 1: 0; }
const int N = 1e4 + 205;

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
	inline bool operator ~ () {return ~c;}
} io;

int T, n, m, w, a[N], s[N], f[N], g[N], q[N], l, r, ans;

int main() {
    io >> T;
    while (T--) {
        io >> n >> m >> w;
        memset(a, 0, sizeof(a));
        For (i, 1, n) io >> a[i + w - 1];
        n += 2 * (w - 1);
        For (i, 1, n) s[i] = s[i - 1] + a[i];
        memset(f, 224, sizeof(f));

        ans = f[0] = 0;
        For (j, 1, m) {
            swap(f, g); memset(f, 224, sizeof(f));
            int ma = f[0];
            l = 1, r = 0;
            For (i, 1, n) {
                if (i >= w) ckmax(ma, g[i - w]), f[i] = ma + s[i] - s[i - w];

                while (l <= r && q[l] <= i - w) l++;
                if (l <= r) ckmax(f[i], g[q[l]] + s[i] - s[q[l]]);

                while (l <= r && g[i] - s[i] >= g[q[r]] - s[q[r]]) r--;
                q[++r] = i;
                
                ckmax(ans, f[i]);
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}

