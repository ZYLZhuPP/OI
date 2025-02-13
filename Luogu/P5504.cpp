#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef double lf;
const int N = 1e5 + 5, M = 1e4 + 5;

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
	inline bool operator ~ () { return ~c; }
} io;

int n, tot[M], s[N], cnt[N];
ll f[N];
deque<int > stk[M];
#define t1 stk[t][stk[t].size() - 1]
#define t2 stk[t][stk[t].size() - 2]

inline ll X(int i) { return cnt[i]; }
inline ll Y(int i) { return f[i - 1] + 1ll * s[i] * cnt[i] * cnt[i]; }
inline lf K(int i, int j) { return 1.0 * (Y(i) - Y(j)) / (X(i) - X(j)); }
inline ll F(int i, int j) { return f[j - 1] + 1ll * s[i] * (cnt[i] - cnt[j] + 1) * (cnt[i] - cnt[j] + 1); }

int main() {
    io >> n;
    For (i, 1, n) io >> s[i], cnt[i] = ++tot[s[i]];
    For (i, 1, n) {
        int t = s[i];
		while (stk[t].size() >= 2 && K(t2, i) >= K(t1, t2)) stk[t].pop_back();
		stk[t].pb(i);
		while (stk[t].size() >= 2 && K(t1, t2) <= 2ll * t * (cnt[i] + 1)) stk[t].pop_back();
		f[i] = F(i, t1);
    }
    printf("%lld", f[n]);

    return 0;
}
