#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int n, s, pri[N], psz, vis[N], cnt[N], res[N], B, ans = 1, flag;

inline int getA(int x) {
    printf("A %d\n", x); fflush(stdout);
    io >> x; return x;
}

inline int getB(int x) {
    printf("B %d\n", x); fflush(stdout);
    io >> x; return x;
}

int main() {
    io >> n; s = n;
    For (i, 2, n) if (!vis[i]) {
        pri[++psz] = i; cnt[psz] = 1; s--;
        For (j, i, n / i) if (!vis[i * j]) s--, vis[i * j] = 1, cnt[psz]++;
        res[psz] = s;
    }
    B = sqrt(psz);
    int l = 0, r = 0;
    For (i, 1, B) {
        l = r + 1, r = i * B; if (i == B) r = psz;
        For (j, l, r) {
            int x = pri[j];
            if (getB(x) ^ cnt[j]) {
                ans *= x;
                for (int y = x; y <= n / x; y *= x) if (getA(x * y)) ans *= x; else break;
            }
        }
        if (!flag && getA(1) ^ res[r]) For (j, l, r) {
            int x = pri[j];
            if (getA(x)) {
                ans *= x;
                for (int y = x; y <= n / x; y *= x) if (getA(x * y)) ans *= x; else break;
                flag = 1;
                break;
            }
        }
    }
    printf("C %d", ans);

    return 0;
}
