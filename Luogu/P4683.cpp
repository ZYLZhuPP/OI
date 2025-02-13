#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e4 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, tot = 1, ch[N * 20][26], ed[N * 20], mark[N * 20], mx, id;
char s[N][22];

inline void ins(char s[]) {
    int n = strlen(s + 1), u = 1;
    For (i, 1, n) {
        int c = s[i] - 'a';
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    ed[u] = 1;
}

inline void tag(char s[]) {
    int n = strlen(s + 1), u = 1;
    For (i, 1, n) {
        int c = s[i] - 'a';
        u = ch[u][c];
        mark[u] = 1;
    }
}

inline void solve(int u) {
    if (ed[u]) puts("P");
    For (i, 0, 25) if (ch[u][i] && !mark[ch[u][i]]) {
        putchar('a' + i); puts("");
        solve(ch[u][i]);
        puts("-");
    }
    For (i, 0, 25) if (ch[u][i] && mark[ch[u][i]]) {
        putchar('a' + i); puts("");
        solve(ch[u][i]);
    }
}

int main() {
    io >> n;
    For (i, 1, n) {
        scanf("%s", s[i] + 1);
        int m = strlen(s[i] + 1);
        ins(s[i]);
        if (cmax(mx, m)) id = i;
    }
    tag(s[id]);
    printf("%d\n", (tot - 1) * 2 - mx + n);
    solve(1);

    return 0;
}
