#include<bits/stdc++.h>
using namespace std;

#define double long double

const int N = 1e6 + 5;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int n, l[N], r[N];
double E;

int main() {
	io >> n;
	for (int i = 1; i <= n; ++i) {
		io >> l[i] >> r[i];
	} 
	
	E = (double)(l[n] + r[n]) / 2.0;
	for (int i = n - 1; i >= 1; --i) {
	    if (l[i] == r[i]) E = max(E, (double)l[i]);
	    else {
    		double H = max((double)0, r[i] - E);
    		double L = min((double)(r[i] - l[i]), E - l[i]);
    		E = (H / 2.0 * (E + r[i]) + L * E) / (double)(r[i] - l[i]);
        }
	}
	
	printf("%.5Lf", E);
	
	return 0;
} 
