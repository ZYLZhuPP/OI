#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

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

int n, q, m, x, l[N], r[N], s[N], ans;

int main() {
	io >> n >> q;
	for (int i = 1; i <= n; ++i) io >> l[i] >> r[i];
	while (q--) {
		ans = 0;
		memset(s, 0, sizeof(s));
		io >> m;
		while (m--) {
			io >> x;
			s[x]++;
		}
		
		for (int j = 1; j <= n; ++j) s[j] += s[j - 1];
		for (int j = 1; j <= n; ++j) if ((s[r[j]] - s[l[j] - 1]) & 1) ans++;
		io << ans << '\n';
	} 
	
	return 0;
}
