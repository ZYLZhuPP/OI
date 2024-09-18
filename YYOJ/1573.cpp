#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

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

ll T, x[3], y[3];
int ans;

void dfs(int k) {
	if (x[0] == y[0] && x[1] == y[1] && x[2] == y[2]) {
		ans = min(ans, k);
		return;
	}
	
	if (k >= 2) return;
	
	ll back[3];
	memcpy(back, x, sizeof(x));
	for (int i = 0; i < 3; ++i) if (x[i] ^ y[i]) {
		int a = (i + 2) % 3, b = (i + 1) % 3; 
		ll ad = y[i] - x[i];
		x[i] += ad;
		dfs(k + 1); x[a] += ad; dfs(k + 1); x[b] += ad; dfs(k + 1); x[a] = back[a]; dfs(k + 1); 
		memcpy(x, back, sizeof(back));
		if (x[i] && !(y[i] % x[i])) {
			ll mul = y[i] / x[i];
			x[i] *= mul;
			dfs(k + 1); x[a] *= mul; dfs(k + 1); x[b] *= mul; dfs(k + 1); x[a] = back[a]; dfs(k + 1); 
			memcpy(x, back, sizeof(back));
		}
	}
}

int main() {
	io >> T;
	while (T--) {
		for (int i = 0; i < 3; ++i) io >> x[i];
		for (int i = 0; i < 3; ++i) io >> y[i];
		ans = 3;
		dfs(0);
		
		for (int i = 0; i < 3; ++i) if (x[i] ^ y[i]) {
			int a = (i + 2) % 3, b = (i + 1) % 3; 
			ll ad = y[i] - x[i];
			if (x[a] && x[b] && !((y[a] - ad) % x[a]) && (y[a] - ad) * x[b] == (y[b] - ad) * x[a]) ans = min(ans, 2);
			if (x[i] && !(y[i] % x[i])) {
				ll mul = y[i] / x[i];
				if (mul && !(y[a] % mul) && !(y[b] % mul)) {
					if (y[a] / mul - x[a] == y[b] / mul - x[b]) ans = min(ans, 2);
				}
			}
		}
		
		if (x[1] ^ x[0] && !((y[1] - y[0]) % (x[1] - x[0]))) {
			ll mul = (y[1] - y[0]) / (x[1] - x[0]);
			ll ad = y[0] - x[0] * mul;
			if (x[2] * mul + ad == y[2]) ans = min(ans, 2);
		}
		
		io << ans << '\n';
	} 
	
	return 0;
} 
