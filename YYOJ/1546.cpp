#include<bits/stdc++.h>
using namespace std;

struct IO {
    char c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, R, P, S, c[3], to[3][2] = {{0, 2}, {1, 0}, {2, 1}};
string f[3][22];
char ch[3] = {'R', 'P', 'S'};

bool check(int k) {
    if (k == n) return c[0] == R && c[1] == P && c[2] == S;
    int x = c[0];
    c[0] += c[1]; c[1] += c[2]; c[2] += x;
    return check(k + 1);
}

void dfs(int x, int k) {
    if (f[x][k].length()) return;
    if (!k) {
        f[x][k] = ch[x];
        return;
    }
    
    dfs(to[x][0], k - 1); dfs(to[x][1], k - 1);
    if (f[to[x][0]][k - 1] < f[to[x][1]][k - 1]) f[x][k] = f[to[x][0]][k - 1] + f[to[x][1]][k - 1];
    else f[x][k] = f[to[x][1]][k - 1] + f[to[x][0]][k - 1];
    return;
}

int main() {
    io >> R >> P >> S;
    n = log2(R + P + S);
    for (int i = 0; i < 3; ++i) {
        c[0] = c[1] = c[2] = 0;
        c[i] = 1;
        if (check(0)) {
            dfs(i, n);
            for (int j = 0; j < (1 << n); ++j) putchar(f[i][n][j]);
            return 0;
        }
    }
    
    puts("IMPOSSIBLE");
    
    return 0;
}

