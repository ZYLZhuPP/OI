#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

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

int mu[N], mip[N], psz, pri[N], sm[N];
int T, a, b, c, d, k;

void init_Mu() {
    mu[1] = 1;
    For (i, 2, N - 1) {
        if (!mip[i]) {
            pri[mip[i] = ++psz] = i;
            mu[i] = -1;
        }
        For (j, 1, mip[i]) {
            int ne = i * pri[j];
            if (ne >= N) break;
            mip[ne] = j;
            if (j ^ mip[i]) mu[ne] = -mu[i];
            else mu[ne] = 0;
        }
    }
    For (i, 1, N - 1) sm[i] = sm[i - 1] + mu[i];
}

inline ll solve(int n, int m) {
    ll res = 0;
    for (int l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        res += 1ll * (n / l) * (m / l) * (sm[r] - sm[l - 1]);
    }
    return res;
}

int main() {
    init_Mu();
    io >> T;
    while (T--) io >> a >> b >> c >> d >> k, printf("%lld\n", solve(b / k, d / k) - solve((a - 1) / k, d / k) - solve(b / k, (c - 1) / k) + solve((a - 1) / k, (c - 1) / k));

    return 0;
}
