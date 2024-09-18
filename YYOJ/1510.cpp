#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int N = 105;

template<class C> inline bool chkmin(C &x, const C &y) {return x>y? x=y, 1: 0;}

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
}io;

ull f[N][N], n, m;

ull dfs(int n, int m) {
    if (m == 3) return (1ull << n) - 1;
    if (f[n][m]) return f[n][m];
    ull res = 1ull << 63;
    for (int i = 0; i < n; i++) 
        chkmin(res, dfs(i, m)*2 + dfs(n-i, m-1));
    return f[n][m] = res;
}

int main() {
    io >> n >> m;
    printf("%llu", dfs(n, m));
    return 0;
}
