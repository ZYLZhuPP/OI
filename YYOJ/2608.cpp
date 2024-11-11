#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)

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

struct OP { int x, y; char c; };
vector<OP > op;

int T, n, m;

inline void _1n(int x, int X, int y, int Y) {
    for (int j = y + 1; j <= Y; j += 2) op.pb({x, j, 'L'});
}

inline void _1m(int x, int X, int y, int Y) {
    for (int i = x + 1; i <= X; i += 2) op.pb({i, y, 'U'});
}

inline void _2n(int x, int X, int y, int Y) {
    op.pb({x + 1, y, 'U'});
    for (int j = y + 3; j <= Y; j += 3) {
        op.pb({x + 1, j - 2, 'U'}); op.pb({x - 1, j - 3, 'R'});
        op.pb({x + 1, j, 'U'}); op.pb({x - 1, j, 'L'});
        op.pb({x + 1, j - 1, 'U'}); op.pb({x - 1, j - 2, 'R'});
    }
    int d = (Y - y) % 3;
    if (d == 1) op.pb({x + 1, Y, 'U'}), op.pb({x - 1, Y - 1, 'R'});
    if (d == 2) op.pb({x + 1, Y - 1, 'U'}), op.pb({x - 1, Y - 2, 'R'}), op.pb({x, Y, 'D'});
}

inline void _2m(int x, int X, int y, int Y) {
    op.pb({x, y + 1, 'L'});
    for (int i = x + 3; i <= X; i += 3) {
        op.pb({i - 2, y + 1, 'L'}); op.pb({i - 3, y - 1, 'D'});
        op.pb({i, y + 1, 'L'}); op.pb({i, y - 1, 'U'});
        op.pb({i - 1, y + 1, 'L'}); op.pb({i - 2, y - 1, 'D'});
    }
    int d = (X - x) % 3;
    if (d == 1) op.pb({X, y + 1, 'L'}), op.pb({X - 1, y - 1, 'D'});
    if (d == 2) op.pb({X - 1, y + 1, 'L'}), op.pb({X - 2, y - 1, 'D'}), op.pb({X, y, 'R'});
}

inline void _3m(int x, int y) {
    op.pb({x + 1, y, 'U'}); op.pb({x, y + 2, 'L'}); op.pb({x - 1, y, 'D'});
}

inline void _3n(int x, int y) {
    op.pb({x, y - 1, 'R'}); op.pb({x + 2, y, 'U'}); op.pb({x, y + 1, 'L'});
}

inline void _3M(int x, int y) {
    op.pb({x - 1, y, 'D'}); op.pb({x, y + 2, 'L'}); op.pb({x + 1, y, 'U'});
}

inline void solve0(int x, int X, int y, int Y) {
    if (x == X) return _1n(x, X, y, Y);
    if (y == Y) return _1m(x, X, y, Y);
    if (x + 1 == X) return _2n(x, X, y, Y);
    if (y + 1 == Y) return _2m(x, X, y, Y);
}

inline void solve() {
    op.resize(0);
    io >> n >> m;
    if (n <= 2 || m <= 2) solve0(2, n + 1, 2, m + 1);
    else {
        int x = n % 3, y = m % 3;
        For (i, 1, x) For (j, 1, m / 3) _3m(i + 1, y + j * 3 - 1);
        rFor (j, m, 4) For (i, 1, n / 3) _3n(x + i * 3 - 1, j + 1);
        if (!x || !y) {
            rFor (i, n, x + 2) _3M(i + 1, 2);
            solve0(x + 2, x + 2, 2, 4);
        } else {
            rFor (i, n, x + 1) _3M(i + 1, 2);
            solve0(2, x + 1, 2, y + 1);
        }
    }
    printf("%d\n", (int)op.size());
    for (auto &[x, y, c] : op) printf("%d %d %c\n", x, y, c);
}

int main() {
    io >> T;
    while (T--) solve();

    return 0;
}
