#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, s[N], R[N][N], L[N][N], sl[N][N], sr[N][N], f[N][N], inv[N];

inline void init() {
    inv[1] = 1; For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
}

int main() {
    init();
    io >> n;
    int x;
    For (i, 1, n) io >> x, s[i] = s[i - 1] + x;
    For (i, 1, n) {
        int r = i;
        For (j, i, n) {
            while (r < n && s[r + 1] - s[j] < s[j] - s[i - 1]) r++;
            R[i][j] = r;
        }
    }
    For (i, 1, n) {
        int l = i;
        rFor (j, i, 1) {
            while (l > 1 && s[i] - s[j - 1] >= s[j - 1] - s[l - 2]) l--;
            L[j][i] = l;
        }
    }
    rFor (len, n, 1) {
        For (l, 1, n - len + 1) {
            int r = l + len - 1;
            if (l == 1 && r == n) f[l][r] = 1;
            else f[l][r] = mo(mo(sr[l][r + 1] - sr[l][R[l][r] + 1]) + mo(sl[l - 1][r] - sl[L[l][r] - 1][r]));
            sr[l][r] = mo(sr[l][r + 1] + ml(f[l][r], inv[r - l]));
            sl[l][r] = mo(sl[l - 1][r] + ml(f[l][r], inv[r - l]));
        }
    }
    For (i, 1, n) printf("%d\n", f[i][i]);

    return 0;
}
