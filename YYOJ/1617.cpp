#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll Mo = 19491001;

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

struct Mat {
	ll f[2][2];
	Mat (int x) {
		memset(f, 0, sizeof(f));
		if (x == 1) {
			f[0][0] = f[1][1] = 1;
		} else if (x == 2) {
			f[0][1] = f[1][0] = f[1][1] = 1; 
		}
	}
	
	Mat operator * (const Mat &X) const {
		Mat res(0);
		for (int k = 0; k < 2; ++k) 
			for (int i = 0; i < 2; ++i) 
				for (int j = 0; j < 2; ++j) res.f[i][j] = (res.f[i][j] + f[i][k] * X.f[k][j]) % Mo;
		return res;
	}
} a(2);

ll n;

Mat qPow(Mat a, ll b) {
	Mat res(1);
	while (b) {
		if (b & 1) res = res * a;
		a = a * a;
		b >>= 1; 
	}
	return res;
}

int main() {
	io >> n;
	a = qPow(a, n);
	
	printf("%lld", (a.f[0][0] + a.f[0][1] - 1 + Mo) % Mo);
	
	return 0;
} 
