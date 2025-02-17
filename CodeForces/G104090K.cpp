#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;

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

int n, q, tot = 1, pos[26], ch[N][26], siz[N];
ll ans, a[26][26], ans0;
char s[N];

inline void add(char s[]) {
    int n = strlen(s + 1), u = 1;
    For (i, 1, n) {
        int c = s[i] - 'a';
        if (!ch[u][c]) ch[u][c] = ++tot;
        For (j, 0, 25) a[c][j] += siz[ch[u][j]];
        u = ch[u][c];
        siz[u]++;
    }
    For (i, 0, 25) ans0 += siz[ch[u][i]];
}

int main() {
    io >> n >> q;   
    For (i, 1, n) scanf("%s", s + 1), add(s);
    while (q--) {
        ans = ans0;
        scanf("%s", s);
        For (i, 0, 25) pos[s[i] - 'a'] = i;
        For (i, 0, 25) For (j, 0, 25) if (pos[i] < pos[j]) ans += a[i][j];
        printf("%lld\n", ans);
    }

    return 0;
}
