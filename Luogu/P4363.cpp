#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 15, S = 1 << 20;
inline void cmax(int &x, const int &y) { y>x? x=y: 0; }

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

int n, m, a[N][N], b[N][N], f[S];
bool is[S];

int main() {
    io >> n >> m;
    For (i, 1, n) For (j, 1, m) io >> a[i][j];
    For (i, 1, n) For (j, 1, m) io >> b[i][j];
    memset(f, 224, sizeof f);
    f[(1 << n) - 1] = 0; is[(1 << n) - 1] = n * m & 1;
    For (s, (1 << n) - 1, ((1 << n) - 1) << m) if (__builtin_popcount(s) == n) {
        int x = n + 1, y = 0, lst = 0;
        rFor (i, n + m - 1, 0) {
            int c = s >> i & 1;
            if (c) x--; else y++;
            if (lst && !c) {
                int s_ = s ^ (3 << i);
                is[s] = !is[s_];
                cmax(f[s], (is[s_]? a[x][y]: b[x][y]) - f[s_]);
            }
            lst = c;
        }
    }
    printf("%d", f[((1 << n) - 1) << m]);

    return 0;
}
