#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 55;

struct IO {
    int c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () { return ~c; }
} io;

int num, T, n, A, B;
bool f[N][N][N];

int main() {
    f[1][0][0] = 1;
    For (b, 1, 50) f[2][0][b] = !(b&1);
    For (a, 1, 50) For (b, 0, 50) f[2][a][b] = !(a&1);
    For (i, 3, 50) {
        For (a, 0, 50) For (b, 0, 50) {
            bool p = f[i - 1][a][b];
            f[i][a + 2][b] |= p; f[i][a][b + 2] |= p;
            if (a) f[i][a + 1][b] |= p; if (b) f[i][a][b + 1] |= p;
        }
        For (a, 0, 50) For (b, 0, 50) {
            bool p = f[i][a][b];
            f[i][a + 2][b] |= p; f[i][a][b + 2] |= p;
            if (b) f[i][a + 2][b - 1] |= p;
        }
    }

    io >> num;
    io >> T;
    //int ans = 0;
    while (T--) {
        io >> n >> A >> B;
        //ans += f[n][A][B];
        puts(f[n][A][B]? "1": "0");
    }
    //cout << ans << endl;

    return 0;
}
