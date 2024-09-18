#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 6e5 + 5, M = 405;

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

int n, K, x, a[N];
ll f0[M], f1[M], s[N], ans = LLONG_MAX;
int q[M];

inline ll p2(ll x) { return x * x; }
inline ll dx(int i, int j) { return s[i] - s[j]; }
inline ll dy(int i, int j) { return f0[i] + p2(s[i]) - (f0[j] + p2(s[j])); }
inline ll F(int i, int j) { return f0[j] + p2(s[i] - s[j]); }

int main() {
    io >> n >> K;
    For (i, 1, n) io >> a[i], a[i + n] = a[i];
    For (i, 1, 2 * n) s[i] = s[i - 1] + a[i];

    if (K == 2) {
        int j = 1;
        For (i, 0, n - 1) {
            while (j < i + n && 2ll * (s[j] - s[i]) < s[n]) j++;
            ans = min(ans, p2(s[j] - s[i]) + p2(s[i + n] - s[j]));
        }
    } else if (K == 3) {
        int j = 1, k = 1;
        For (i, 0, n - 1) {
            while (j < i + n && 3ll * (s[j] - s[i]) < s[n]) j++;
            k = max(k, j + 1);
            while (k < i + n && s[k] - s[j] < s[i + n] - s[k]) k++;
            ans = min(ans, p2(s[j] - s[i]) + p2(s[k] - s[j]) + p2(s[i + n] - s[k]));
            ans = min(ans, p2(s[j] - s[i]) + p2(s[k - 1] - s[j]) + p2(s[i + n] - s[k - 1]));
        }
    } else {
        For (o, 0, n - 1) {
            For (i, 1, n) s[i] = s[i - 1] + a[o + i];
            memset(f1, 31, sizeof f1); f1[0] = 0;
            For (k, 1, K) {
                swap(f0, f1);
                int h = 1, t = 0; q[++t] = 0;
                For (i, 1, n) {
                    ll k = 2ll * s[i];
                    while (h < t && dy(q[h + 1], q[h]) <= dx(q[h + 1], q[h]) * k) h++;
                    f1[i] = F(i, q[h]);
                    while (h < t && dy(i, q[t]) * dx(q[t], q[t - 1]) <= dy(q[t], q[t - 1]) * dx(i, q[t])) t--;
                    q[++t] = i;
                }
            }
            ans = min(ans, f1[n]);
        }
    }
    printf("%lld", K * (ans * K - p2(s[n])));

    return 0;
}
