#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const int N = 505, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }

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
pair<lf, int > A[N][N], B[N];

int main() {
    io >> n;
    For (i, 1, n) io >> a[i], a[i] += a[i - 1];
    For (i, 1, n) io >> b[i], b[i] += b[i - 1];
    For (i, 0, n - 1) {
        For (j, 1, n - i) A[i][j] = {1.0 * (a[i + j] - a[i]) / j, i + j};
        sort(A[i] + 1, A[i] + n - i + 1);
    }
    f[0][0] = 1;
    For (j, 1, n) {
        For (k, 0, j - 1) B[k] = {1.0 * (b[j] - b[k]) / (j - k), k};
        sort(B, B + j);
        For (i, 0, n - 1) {
            int s = 0, t = j - 1;
            rFor (k, n - i, 1) {
                while (~t && B[t].first >= A[i][k].first) add(s, f[i][B[t--].second]);
                add(f[A[i][k].second][j], s);
            }
        }
    }
    printf("%d", f[n][n]);
    
    return 0;
}
