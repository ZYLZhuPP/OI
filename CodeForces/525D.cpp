#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;

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
    inline bool operator ~ () { return ~c; }
} io;

int n, m, dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
char s[N][N];

inline bool is(int x, int y) { return x>0 && x<=n && y>0 && y<=m && s[x][y]=='.'; }
inline bool check(int x, int y) { return x>0 && x<=n && y>0 && y<=m && s[x][y]=='*' && ((is(x - 1, y) && ((is(x - 1, y - 1) && is(x, y - 1)) || (is(x - 1, y + 1) && is(x, y + 1)))) || (is(x + 1, y) && ((is(x + 1, y - 1) && is(x, y - 1)) || (is(x + 1, y + 1) && is(x, y + 1))))); }

inline void dfs(int x, int y) {
    s[x][y] = '.';
    For (i, 0, 7) {
        int x_ = x + dx[i], y_ = y + dy[i];
        if (check(x_, y_)) dfs(x_, y_);
    }
}

int main() {
    io >> n >> m;
    For (i, 1, n) scanf("%s", s[i] + 1);
    For (i, 1, n) For (j, 1, m) if (check(i, j)) dfs(i, j);
    For (i, 1, n) printf("%s\n", s[i] + 1);

    return 0;
}