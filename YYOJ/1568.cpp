#include<bits/stdc++.h>
using namespace std;

const int N = 2005;

int n, ans, s[N][N], to[N], a[N], t, ned[N];

struct IO {
	static const int BufS=1<<20;
	char ibuf[BufS], *iS, *iT, obuf[BufS], c;
    int top, f, num[66], t;
	#define gc() ((iS==iT && (iT=(iS=ibuf)+fread(ibuf, 1, BufS, stdin)), iS==iT)? EOF: *iS++)
    #define pc(c) (obuf[top==BufS? fwrite(obuf, 1, BufS, stdout), !(top=1): top++]=c)
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline void flush() {fwrite(obuf, 1, top, stdout);}
    ~IO() {flush();}
    template<class C>
    inline IO& operator << (C x) {
        if (!x) pc('0'); if (x < 0) pc('-'), x = -x;
        while (x) num[++t] = x % 10, x /= 10;
        while (t) pc(num[t--] ^ 48);
        return *this;
    }
    inline IO& operator << (char x) {
        pc(x);
        return *this;
    }
	inline bool operator ~ () {return ~c;}
} io;

void dfs(int k) {
	while (to[k] && !s[k][to[k]]) to[k]--;
	if (!to[k]) return;
	s[k][to[k]]--;
	a[++t] = k - to[k];
	dfs(to[k]);
}

int main() {
	io >> n;
	if (n & 1) ans = n - 1 + (n - 3) * ((n - 1) / 2) / 2;
	else ans = n - 1 + (1 + n - 3) * (n / 2 - 1) / 2;
	printf("%d\n", ans); 
	
	for (int i = n; i >= 1; --i)
		for (int j = 1; j < i; ++j) s[i][j] = 1;

	for (int i = 1; i <= n; ++i) to[i] = i - 1;
	for (int i = n / 2 + 1; i < n; ++i) s[n][i] += i - 1 - (n - i);
	
	for (int i = 1; i <= ans; ++i) {
		t = 0;
		dfs(n);
		io << t << ' ';
		for (int j = 1; j <= t; ++j) io << a[j] << ' ';
		io << '\n';
	}
	
	return 0;
} 
