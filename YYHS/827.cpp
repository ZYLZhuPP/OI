#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e4 + 5;

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

int n, m, A, B, T, q[N], l, r;
ll x[N], s[N], c, g[N], f0[N], f1[N];
ll ans;
int clas, last, lst;

bool better(int x, int y, int i) { return f0[x] - s[x] * g[i] <= f0[y] - s[y] * g[i]; }

int main() {
    io >> T;
    while (T--) {
        c = s[0] = 0;
        io >> m >> n >> A >> B;
        For (i, 1, m) io >> x[i], c += x[i];
        c /= m;
        For (i, 1, m) x[i] = (x[i] - c) * (x[i] - c), s[i] = s[i - 1] + x[i];
        For (i, 1, n) io >> g[i];

        memset(f1, 31, sizeof(f1)); f1[0] = 0; ans = f1[m];
        For (i, 1, n) {
            l = 1, r = 0;
            swap(f0, f1); memset(f1, 31, sizeof(f1));
            For (j, A * i, m) {
                while (l <= r && better(j - A, q[r], i)) r--;
                q[++r] = j - A;
                while (l <= r && q[l] < j - B) l++;
                f1[j] = f0[q[l]] + (s[j] - s[q[l]]) * g[i];
                if (j == m) lst = j - q[l];
            }

            if (f1[m] <= ans) {
                ans = f1[m];
                clas = i;
                last = lst;
            }
        }

        printf("%lld %d %d\n", ans, clas, last);
    }

    return 0;
}
