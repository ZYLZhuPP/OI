#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef __int128 lll;
typedef long long ll;

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

int n;
ll K;
vector<int > ans;

namespace TP1 {
    const int N = 105, M = 1e4 + 5;
    lll f[N][M], s[N][M];
    void main() {
        f[1][0] = 1; For (i, 0, M - 1) s[1][i] = 1;
        For (i, 2, n) For (j, 0, M - 1) f[i][j] = s[i - 1][j] - (j>=i? s[i - 1][j - i]: 0), s[i][j] = (j? s[i][j - 1]: 0) + f[i][j];
        int x = 0; while (s[n][x] < K) x++;
        if (x) K -= s[n][x - 1];
        vector<int > a; rFor (i, n, 1) a.pb(i);
        rFor (i, n, 2) {
            ll S = 0; int y = 0;
            while (S + f[i - 1][x - y] < K) S += f[i - 1][x - y], y++;
            ans.pb(*(a.end() - y - 1)); a.erase(a.end() - y - 1);
            K -= S; x -= y;
        }
        ans.pb(*a.begin());
    }
}

namespace TP2 {
    const int N = 2e5 + 5, M = 55;
    lll f[N][M], s[N][M];
    void main() {
        f[1][0] = 1; For (i, 0, M - 1) s[1][i] = 1;
        For (i, 2, n) For (j, 0, M - 1) f[i][j] = s[i - 1][j] - (j>=i? s[i - 1][j - i]: 0), s[i][j] = (j? s[i][j - 1]: 0) + f[i][j];
        int x = 0; while (s[n][x] < K) x++;
        if (x) K -= s[n][x - 1];
        vector<int > a; rFor (i, n, 1) a.pb(i);
        rFor (i, n, 2) {
            ll S = 0; int y = 0;
            while (S + f[i - 1][x - y] < K) S += f[i - 1][x - y], y++;
            ans.pb(*(a.end() - y - 1)); a.erase(a.end() - y - 1);
            K -= S; x -= y;
        }
        ans.pb(*a.begin());
    }
}

int main() {
    io >> n >> K;
    if (n <= 100) TP1::main();
    else TP2::main();
    for (auto &x : ans) printf("%d ", x);

    return 0;
}
