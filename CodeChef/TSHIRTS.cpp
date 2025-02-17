#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1 << 10, Mo = 1e9 + 7;
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

int T, n, f[N];
vector<int > sb[101];

int main() {
    io >> T;
    while (T--) {
        io >> n;
        For (i, 1, n) {
            int x;
            do {
                io >> x;
                sb[x].pb(i);
            } while (io.c == ' ');
        }
        memset(f, 0, sizeof f);
        f[0] = 1;
        For (i, 1, 100) {
            rFor (s, (1 << n) - 1, 0) {
                for (auto &x : sb[i]) if (!(s >> (x - 1) & 1))
                    add(f[s ^ (1 << (x - 1))], f[s]);
            }
        }
        printf("%d\n", f[(1 << n) - 1]);
        For (i, 1, 100) sb[i].resize(0);
    }

    return 0;
}
