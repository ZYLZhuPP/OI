#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e6 + 5;
const ll Mo = 1e6 + 3;

struct IO {
    char c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
}io;

int n, k, a[N], v[N], fa[N], sum, s;
ll inv[N], fac[N], invfac[N];

ll C(int n, int m) {
    if (n < m || m < 0) return 0;
    return fac[n] * invfac[n - m] % Mo * invfac[m] % Mo;
}

int find(int u) {
    if (u ^ fa[u]) return fa[u] = find(fa[u]);
    return u;
}

void merge(int u, int v) {
    fa[u] = v;
}

void init() {
    for (int i = 1; i <= n; i++) fa[i] = i, v[i] = -1;
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = (Mo - Mo / i) * inv[Mo % i] % Mo;
    fac[0] = invfac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % Mo, invfac[i] = invfac[i - 1] * inv[i] % Mo;
}

int main() {
    io >> n >> k;
    init();
    for (int i = 1; i <= n - k + 1; ++i) {
        io >> a[i];
        if (i > 1) {
            int l = i - 1, r = i + k - 1;
            if (a[i] == a[i - 1]) {
                merge(l, r);
            } else if (a[i] == a[i - 1] + 1) {
                v[l] = 0; v[r] = 1;
            } else if (a[i] == a[i - 1] - 1) {
                v[l] = 1; v[r] = 0;
            } else {
                puts("0");
                return 0;
            }
        }
    }

    for (int i = 1; i <= k; ++i) {
        if (~v[find(i)]) sum += v[fa[i]];
        else s++;
    }

    printf("%lld", C(s, a[1] - sum));

    return 0;
}
