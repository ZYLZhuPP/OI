#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, inf = 2e9 + 1;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && c != '?' && ~c) f |= -!(c ^ 45);
        if (c == '?') x = inf;
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int T, n, K, a[N], b[N], tot;

int main() {
    b[0] = -2e9;
    io >> T;
    while (T--) {
        bool flag = 1;
        io >> n >> K;
        For (i, 1, n) io >> a[i];
        For (r, 1, K) {
            tot = 0;
            for (int i = r; i <= n; i += K) b[++tot] = a[i];
            b[++tot] = 2e9;
            int l = 0;
            For (i, 1, tot) {
                if (b[i] < inf) {
                    if (b[i] - i < b[l] - l) { flag = 0; break; }
                    int x = (i + l) >> 1;
                    if (b[l] >= l - x) For (j, l + 1, i - 1) b[j] = b[l] + j - l;
                    else if (b[i] <= i - x) For (j, l + 1, i - 1) b[j] = b[i] + j - i;
                    else For (j, l + 1, i - 1) b[j] = j - x;
                    l = i;
                }
            }
            if (!flag) break;
            For (i, 1, tot - 1) a[r + (i - 1) * K] = b[i];
        }
        if (!flag) puts("Incorrect sequence");
        else For (i, 1, n) printf("%d%c", a[i], " \n"[i==n]);
    }

    return 0;
}
