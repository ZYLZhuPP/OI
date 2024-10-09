#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5, M = 1e6 + 5;

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

int n, m, to[M][26], q[N], tot;
char a[N], b[M];

int main() {
    io >> n >> m;
    scanf("%s", a + 1);
    scanf("%s", b + 1);
    For (i, 0, 25) to[0][i] = m + 1;
    rFor (i, m, 1) {
        For (j, 0, 25) to[i][j] = to[0][j];
        to[0][b[i] - 'A'] = i;
    }
    q[++tot] = 0;
    For (i, 1, n) {
        int c = a[i] - 'A';
        if (to[q[tot]][c] <= m) q[tot + 1] = to[q[tot]][c], tot++;
        rFor (i, tot - 1, 1) if (to[q[i]][c] < q[i + 1]) q[i + 1] = to[q[i]][c];
    }
    printf("%d", tot - 1);
    
    return 0;
}
