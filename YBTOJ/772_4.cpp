#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

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

int n, fa[N], pre[N], f[N], g[N], B, dep[N];
ll ans[N], s[N];
vector<int > o[N];

int main() {
    io >> n;
    For (i, 2, n) io >> fa[i], pre[i] = i, dep[i] = dep[fa[i]] + 1, s[dep[i]]++;
    B = sqrt(n);
    For (x, 1, B) {
        For (i, 1, n) f[i] = g[i] = 0;
        rFor (i, n, 2) {
            f[i]++; g[pre[i]] += f[i];
            ans[x] += 1ll * f[fa[i]] * g[i]; f[fa[i]] += g[i];
            pre[i] = fa[pre[i]];
        }
    }
    
    rFor (u, n, 2) {
        o[u].pb(1);
        int f = fa[u];
        if (o[u].size() > o[f].size()) swap(o[u], o[f]);
        int nf = o[f].size(), nu = o[u].size();
        For (x, B + 1, nu) {
            int a = 0, b = 0;
            for (int i = x; i <= nf; i += x) a += o[f][nf - i];
            for (int i = x; i <= nu; i += x) b += o[u][nu - i];
            ans[x] += 1ll * a * b;
        }
        For (i, 1, nu) o[f][nf - i] += o[u][nu - i];
    }

    rFor (i, n - 1, 1) for (int j = i << 1; j < n; j += i) ans[i] -= ans[j];
    rFor (i, n - 1, 1) s[i] += s[i + 1];
    For (i, 1, n - 1) printf("%lld\n", ans[i] + s[i]);
    
    return 0;
}
