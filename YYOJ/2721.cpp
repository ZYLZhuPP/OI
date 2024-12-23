#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }

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

int T, n, la, lb, f[N][N][2];
char a[N], b[N];

inline void get(char s[], int &len) {
    len = 0; string buf; cin >> buf;
    for (auto &c : buf) {
        if (c == '1') continue;
        if (c == '0') len = 0;
        s[++len] = c=='+'? '+': '*';
    }
}

int main() {
    io >> T;
    while (T--) {
        io >> n;
        get(a, la); get(b, lb);
        f[0][0][1] = 1;
        For (i, 0, la) For (j, 0, lb) {
            f[i + 1][j][0] = mo(f[i][j][0] + f[i][j][1]);
            f[i][j + 1][1] = f[i][j][1];
            if (i && a[i] ^ b[j + 1]) f[i][j + 1][1] = f[i + 1][j][0];
        }
        printf("%d\n", mo(f[la][lb][0] + f[la][lb][1]));
    }

    return 0;
}
