#include<bits/stdc++.h>
using namespace std;

#define jj (j + h - 1) 
#define j_ (j - h + 1)

typedef long long ll;

const int N = 3005;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m, h, ty;
ll x[N][N], l[N][N], r[N][N], s[N][N], ans;

struct Data_Maker{
    ll Seed,a,b,c,MOD;
    ll Random() {
        c++;
        Seed=(Seed*a+b*c)%MOD;
        return Seed;
    }
    int Random_int() {
        int tmp=Random();
        if(Random()&1)tmp*=-1;
        return tmp;
    }
    void MAKE() {
        io >> Seed >> a >> b >> c >> MOD;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                x[i][j]=Random_int();
    }
} mk;

void L(int a, int b) {
    ll s = 0;
    for (int i = a, j = b; i > 0 && j <= m; --i, ++j) {
        s += x[i][j];
        if (a - i + 1 >= h) {
            l[i][j] = s;
            s -= x[i + h - 1][j - h + 1];
        }
    } 
}

void R(int a, int b) {
    ll s = 0;
    for (int i = a, j = b; i <= n && j <= m; ++i, ++j) {
        s += x[i][j];
        if (i - a + 1 >= h) {
            r[i][j] = s;
            s -= x[i - h + 1][j - h + 1];
        }
    } 
}

int main() {
    io >> n >> m >> h >> ty;
    if (!ty) {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) io >> x[i][j];
    } else {
        mk.MAKE();
    }
    
    for (int i = 1; i <= n; ++i) L(i, 1), R(i, 1);
    for (int i = 2; i <= m; ++i) L(n, i), R(1, i);
    
    for (int i = 1; i <= h; ++i) {
        s[h][h] += x[i][h];
        for (int j = 1; j < i; ++j) s[h][h] += x[i][h - j] + x[i][h + j];
    }
    for (int i = h + 1; i < 2*h; ++i) {
        s[h][h] += x[i][h];
        for (int j = 1; j < 2*h - i; ++j) s[h][h] += x[i][h - j] + x[i][h + j];
    }
    
    ans = s[h][h];
    for (int i = h; i <= n - h + 1; ++i) {
        int ii = i + h - 1, i_ = i - h + 1;
        if (i > h) {
            s[i][h] = s[i - 1][h] - l[i_ - 1][h] - r[i - 1][2*h - 1] + l[i][2*h - 1] + r[ii][h] + x[i_ - 1][h] - x[ii][h];
            ans = max(ans, s[i][h]);
        }
        for (int j = h + 1; j <= m - h + 1; ++j) {
            s[i][j] = s[i][j - 1] - l[i_][j - 1] - r[ii][j - 1] + l[i][jj] + r[i][jj] + x[i][j_ - 1] - x[i][jj];
            ans = max(ans , s[i][j]);
        }
    }
    
    printf("%lld", ans);
    
    return 0;
} 
