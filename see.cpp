#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef double lf;
const int N = 5e5 + 5, Mo = 1e9 + 9;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

struct IO {
	static const int BufS = 1 << 20;
	char ibuf[BufS], *S, *T, c; int f;
#define gc() ((S==T && (T=(S=ibuf)+fread(ibuf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline IO& operator >> (char &x){
		while ((c = gc()) < 33 && ~c);
		x = c; return *this;
	}
	inline IO& operator >> (char *x){
		while ((c = gc()) < 33 && ~c);
		while (c > 32) *x++ = c, c = gc();
		*x = 0; return *this;
	}
	inline IO& operator >> (double &x){
		double p(1); x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
		if (!(c ^ 46)) while (isdigit(c = gc())) x += (c ^ 48) * (p /= 10);
		x *= f; return *this;
	}
	char obuf[BufS]; int E, st[66], t;
#define pc(c) (obuf[E==BufS && (E-=fwrite(obuf, 1, BufS, stdout)), E++]=c)
    inline void flush() {fwrite(obuf, 1, E, stdout);}
    ~IO() {flush();}
    template<class C>
    inline IO& operator << (C x) {
        if (!x) pc('0'); if (x < 0) pc('-'), x = -x;
        while (x) st[++t] = x % 10, x /= 10;
        while (t) pc(st[t--] ^ 48);
        return *this;
    }
    inline IO& operator << (char x) {
        pc(x); return *this;
    }
    template<class C>
    inline IO& operator << (C *x) {
        while (*x) pc(*x++);
        return *this;
    }
	inline bool operator ~ () const { return ~c; }
} io;

int main() {
    char a[45];
    io >> a;
    io << a;
    io << "123";
	return 0;
}