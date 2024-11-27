#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int n, m, K, q, len, ch[N][26], tot = 1, fa[N], ed[N], p[N], P, a[N][N], f[N];
char s[N];

inline void add(char s[]) {
    int u = 1;
    For (i, 1, m) {
        int c = s[i] - 'a';
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    ed[u] = 1;
}

inline void build() {
    For (i, 0, K - 1) ch[0][i] = 1;
    queue<int > q; q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        For (i, 0, K - 1) (ch[u][i]? q.push(ch[u][i]), fa[ch[u][i]]: ch[u][i]) = ch[fa[u]][i];
    }
}

inline void Gauss(int n) {
    For (i, 1, n) {
        int r = i; while (r <= n && !a[r][i]) r++;
        swap(a[i], a[r]);
        int x = qPow(a[i][i], Mo - 2);
        For (j, i, n + 1) mul(a[i][j], x);
        For (j, 1, n) if (i ^ j) {
            x = a[j][i];
            For (k, i, n + 1) add(a[j][k], -ml(x, a[i][k]));
        }
    }
}

inline int query(int n) {
    int u = 1;
    For (i, 1, n) {
        u = ch[u][s[i] - 'a'];
        if (ed[u]) break;
    }
    return u;
}

inline void query0(int n) {
    int u = 1;
    For (i, 1, n) {
        if (!ed[u]) u = ch[u][s[i] - 'a'];
        printf("%d\n", i + f[u]);
    }
}

int main() {
    io >> n >> m >> K;
    For (i, 0, K - 1) io >> p[i], P += p[i];
    P = qPow(P, Mo - 2); For (i, 0, K - 1) mul(p[i], P);
    For (i, 1, n) scanf("%s", s + 1), add(s);
    build();
    For (i, 1, tot) {
        if (ed[i]) { a[i][i] = 1; continue; }
        a[i][i] = a[i][tot + 1] = 1;
        For (j, 0, K - 1) add(a[i][ch[i][j]], -p[j]);
    }
    Gauss(tot);
    For (i, 1, tot) f[i] = a[i][tot + 1];
    scanf("%s", s + 1); len = strlen(s + 1);
    query0(len);
    io >> q;
    int op, x; char c[3];
    while (q--) {
        io >> op;
        if (op == 1) {
            io >> x; scanf("%s", c);
            For (i, len - x + 1, len) s[i] = c[0];
        } else {
            io >> x;
            printf("%d\n", x + f[query(x)]);
        }
    }

    return 0;
}
