#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
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
    inline bool operator ~() {return ~c;}
} io;

int n, a[N], s, t, l[N], r[N], ma[N], to[N], m[N];
char f[N];
bool tp[256];
string st;

void mul(int l, int r) {
    For (i, l + 1, r) f[i] = '*';
}

void Mul(int x) {
    if (x > t) return;
    mul(l[x], r[to[x]]);
    Mul(to[x] + 1);
}

void solve() {
    s++;
    ll M = 1;
    For (i, s, t) {
        m[i] = 1;
        For (j, l[i], r[i]) m[i] = min(m[i] * a[j], N);
        M = min(M * m[i], (ll)N);
    }
    if (M == N) {
        mul(l[s], r[t]);
        s = t;
        return;
    }
    ma[t] = m[t]; to[t] = t;
    for (int i = t - 1; i >= s; --i) {
        M = 1;
        For (j, i, t - 1) {
            M *= m[j];
            if (M + l[j + 1] - r[j] - 1 + ma[j + 1] > ma[i]) {
                ma[i] = M + l[j + 1] - r[j] - 1 + ma[j + 1];
                to[i] = j;
            }
        }
        M *= m[t];
        if (M > ma[i]) ma[i] = M, to[i] = t;
    }
    Mul(s);
    s = t;
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    cin >> st; For (i, 0, (int)st.size() - 1) tp[(int)st[i]] = 1;

    if (st.size() == 1) {
        char c = st[0];
        putchar(a[1] ^ 48);
        For (i, 2, n) putchar(c), putchar(a[i] ^ 48);
        return 0;
    }

    if (!tp['*']) {
        char c = '+';
        putchar(a[1] ^ 48);
        For (i, 2, n) putchar(c), putchar(a[i] ^ 48);
        return 0;
    }

    if (!tp['+']) {
        putchar(a[1] ^ 48);
        For (i, 2, n) {
            if (!a[i]) putchar('-');
            else putchar('*');
            putchar(a[i] ^ 48);
        }
        return 0;
    }

    int L = 1;
    For (i, 1, n) {
        if (a[i] == 0) {
            f[i] = f[i + 1] = '+';
            if (L < i) l[++t] = L, r[t] = i - 1;
            L = i + 1;
            solve();
        }
        if (a[i] == 1) {
            f[i] = f[i + 1] = '+';
            if (L < i) l[++t] = L, r[t] = i - 1;
            L = i + 1;
        }
    }
    if (L <= n) l[++t] = L, r[t] = n;
    solve();

    putchar(a[1] ^ 48);
    For (i, 2, n) putchar(f[i]), putchar(a[i] ^ 48);

    return 0;
}
