#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e3 + 5;
int Mo;
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

int T, n;

struct mat {
    int o[N][N];
} A, B, C;

struct vec {
    int o[N];
    vec() { memset(o, 0, sizeof o); }
    vec operator * (const mat &a) const {
        vec r;
        For (i, 1, n) For (j, 1, n) add(r.o[j], ml(o[i], a.o[i][j]));
        return r;
    }
};

inline bool chk() {
    vec x; For (i, 1, n) x.o[i] = rand() % Mo;
    vec a = x * A * B, b = x * C;
    For (i, 1, n) if (a.o[i] ^ b.o[i]) return 1;
    return 0;
}

inline bool ok() {
    For (i, 1, 3) if (chk()) return 0;
    return 1;
}

int main() {
    srand(time(0));
    io >> T;
    while (T--) {
        io >> Mo;
        io >> n;
        For (i, 1, n) For (j, 1, n) io >> A.o[i][j];
        For (i, 1, n) For (j, 1, n) io >> B.o[i][j];
        For (i, 1, n) For (j, 1, n) io >> C.o[i][j];
        puts(ok()? "Yes": "No");
    }

    return 0;
}
