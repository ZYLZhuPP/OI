#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

struct IO {
	char c; int f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int n, m, p[N], dep[N], ch[N][26], f[N][N], ans;
char s[N];

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    io >> m;
    ch[0][s[1] - 'a'] = 1;
    ch[1][s[1] - 'a'] = 1;
    ch[1][s[2] - 'a'] = 2;
    dep[1] = 1;
    int j = 0;
    For (i, 2, n) {
        while (j && s[i] ^ s[j + 1]) j = p[j];
        if (s[i] == s[j + 1]) j++;
        p[i] = j; dep[i] = dep[p[i]] + 1;
        For (j, 0, 25) ch[i][j] = j==s[i + 1]-'a'? i + 1: ch[p[i]][j];
    }
    memset(f, 224, sizeof f);
    f[0][0] = 0;
    For (j, 0, m - 1) {
        For (i, 0, n) {
            For (c, 0, 25) cmax(f[ch[i][c]][j + 1], f[i][j] + dep[ch[i][c]]);
        }
    }
    For (i, 0, n) cmax(ans, f[i][m]);
    printf("%d", ans);

    return 0;
}
