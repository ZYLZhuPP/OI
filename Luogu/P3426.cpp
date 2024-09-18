#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

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

int n, p[N], mx[N], f[N];
char s[N];

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    mx[f[1] = 1] = 1;
    int j = 0;
    For (i, 2, n) {
        while (j && s[j + 1] ^ s[i]) j = p[j];
        if (s[j + 1] == s[i]) j++;
        p[i] = j;
        f[i] = mx[f[p[i]]]>=i-p[i]? f[p[i]]: i;
        mx[f[i]] = i;
    }
    printf("%d", f[n]);

    return 0;
}
