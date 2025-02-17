#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int Mo = 998244353, v2 = 499122177;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }
inline void mul(int &x, int y) { x = ml(x, y); }
int qPow(int a, int b) { int r = 1; while (b) { if (b & 1) mul(r, a); mul(a, a); b >>= 1; } return r; }
inline int P(int n) { return n>0? ml(ml(n, n + 1), v2): 0; }

struct IO {
    int c, f;
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

struct mat {
    int v[3][3];
    mat() { memset(v, 0, sizeof v); }
    mat operator * (const mat &x) const {
        mat r;
        For (k, 0, 2) For (i, 0, 2) For (j, 0, 2)
            add(r.v[i][j], ml(v[i][k], x.v[k][j]));
        return r;
    }
};
mat qPow(mat a, int b) {
    if (b == 1) return a;
    mat r = a; b--;
    while (b) { if (b & 1) r = r * a; a = a * a; b >>= 1; }
    return r;
}

int n, k, S, vS, ans;

inline int all(int l, int r) { return ml(l, n - r + 1); }
inline int none(int l, int r) { return mo(P(l - 1) + P(n - r)); }
void solve(int l, int r, int L, int R) {
    int A = mo(all(l, r) - all(L, R)); //son all but fa part
  //int B = mo(S - mo(all(l, r) + none(l, r))); //son part -> fa part
    int C = all(L, R); //fa all
    int D = none(L, R); //fa none -> son none
    int E = mo(none(l, r) - none(L, R)); //son none but fa part
    if (l == 1 && r == n) A = 1, C = 0;
    //printf("%d %d %d %d %d\n", A, B, C, D, E);
    mat a;
    a.v[0][0] = ml(mo(C + D), vS); a.v[0][1] = ml(E, vS); a.v[0][2] = ml(A, vS);
    a.v[1][1] = ml(mo(D + E), vS); a.v[1][2] = ml(mo(A + C), vS); a.v[2][2] = 1;
    a = qPow(a, k);
    add(ans, a.v[0][2]);
    if (l == r) return;
    int m; io >> m;
    solve(l, m, l, r); solve(m + 1, r, l, r);
}

int main() {
    io >> n >> k;
    S = P(n); vS = qPow(S, Mo - 2);
    solve(1, n, 1, n);
    printf("%d", ans);

    return 0;
}
