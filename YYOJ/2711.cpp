#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

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

int n, q, s[N], R[N][18], L[N][18], sR[N][18], sL[N][18];
char a[N << 1], b[N];

inline int dis(int u, int v) {
    int res = 0;
    rFor (i, 17, 0) if (R[u][i] < v) res |= 1 << i, u = R[u][i];
    return res + 1;
}

int main() {
    io >> n >> q;
    scanf("%s", a + 1);
    scanf("%s", b + 1);
    For (i, 1, n) s[i] = s[i - 1] + (b[i] & 1);
    int x = 0, y = 0;
    For (i, 1, 2 * n) if (a[i] == 'L') y++; else R[++x][0] = y, sR[x][0] = s[y];
    x = y = n + 1;
    rFor (i, 2 * n, 1) if (a[i] == 'R') y--; else L[--x][0] = y, sL[x][0] = s[y - 1];
    rFor (i, n, 1) For (j, 1, 17) R[i][j] = R[R[i][j - 1]][j - 1], sR[i][j] = sR[i][j - 1] + sR[R[i][j - 1]][j - 1];
    For (i, 1, n) For (j, 1, 17) L[i][j] = L[L[i][j - 1]][j - 1], sL[i][j] = sL[i][j - 1] + sL[L[i][j - 1]][j - 1];
    int u, v;
    while (q--) {
        io >> u >> v;
        int d = dis(u, v), ans = (b[u] & 1) + (b[v] & 1);
        For (i, 0, 17) if ((d - 1) >> i & 1) ans += sR[u][i] - sL[v][i], u = R[u][i], v = L[v][i];
        printf("%d %d\n", d, ans);
    }

    return 0;
}
