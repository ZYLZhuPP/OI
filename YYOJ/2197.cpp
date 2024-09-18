#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
typedef array<int, 2 > P;
const int N = 3e3 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, a[N], b[N], f[N][N];
P q[N];

struct Queue {
    int j, h, t, q[N];
    Queue() { h = 1; t = 0; }
    inline int X(int i) { return i; }
    inline int Y(int i) { return f[i][j] + i * i; }
    inline lf K(int a, int b) { return 1.l * (Y(a) - Y(b)) / (X(a) - X(b)); }
    inline bool empty() { return h > t; }
    inline int front(int k) {
        while (h < t && K(q[h], q[h + 1]) <= k) h++;
        return q[h];
    }
    inline void push(int i) {
        while (h < t && K(q[t], i) <= K(q[t], q[t - 1])) t--;
        q[++t] = i;
    }
} Q[N];

inline int X(P a) { return a[1]; }
inline int Y(int i, P a) { return f[a[0]][a[1]] + (i - a[0]) * (i - a[0]) + a[1] * a[1]; }
inline lf K(int i, P a, P b) { return 1.l * (Y(i, a) - Y(i, b)) / (X(a) - X(b)); }
inline int F(int i, int j, P a) { return f[a[0]][a[1]] + (i - a[0]) * (i - a[0]) + (j - a[1]) * (j - a[1]); }

int main() {
    io >> n;
    For (i, 0, n + 1) io >> a[i];
    For (i, 0, n + 1) io >> b[i], Q[i].j = i;
    memset(f, 31, sizeof f);
    f[0][0] = 0;
    For (i, 1, n + 1) {
        int h = 1, t = 0;
        For (j, 1, n + 1) {
            if (a[i] == b[j]) {
                f[i][j] = i * i + j * j;
                while (h < t && K(i, q[h], q[h + 1]) <= 2 * j) h++;
                if (h <= t) cmin(f[i][j], F(i, j, q[h]));
            }
            if (!Q[j].empty()) {
                int x = Q[j].front(2 * i);
                while (h < t && K(i, {x, j}, q[t]) <= K(i, q[t], q[t - 1])) t--;
                q[++t] = {x, j};
            }
        }
        For (j, 1, n + 1) if (a[i] == b[j]) Q[j].push(i);
    }
    printf("%d", f[n + 1][n + 1]);

    return 0;
}