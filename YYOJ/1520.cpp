#include<bits/stdc++.h>
using namespace std;

const double base = 1e7;

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

int x, n, p_;
double ans, f[205][2][305][256], p;

int main() {
    io >> x >> n >> p_;
    p = (double)p_ / 100.0;

    int a = x >> 8, b = x & 255;
    int o = a & 1, s = 0;
    if (a) {
        while ((a&1) == o) s++, a >>= 1;
    }
    f[0][o][s][b] = base;

    for (int i = 0; i < n; i++) {
        for (o = 0; o < 2; o++) {
            for (s = 0; s <= i + 50; s++) {
                for (b = 0; b < 256; b++) {
                    double x = f[i][o][s][b]*(1-p), y = f[i][o][s][b]*p;
                    int b1 = b + 1, b2 = (b&127) << 1;
                    if (o) {
                        if (b == 255) f[i+1][0][s][0] += x;
                        else f[i+1][1][s][b1] += x;

                        if (b > 127) f[i+1][1][s+1][b2] += y;
                        else f[i+1][0][1][b2] += y;
                    } else {
                        if (b == 255) f[i+1][1][1][0] += x;
                        else f[i+1][0][s][b1] += x;

                        if (b > 127) f[i+1][1][1][b2] += y;
                        else f[i+1][0][s+(s>0)][b2] += y;
                    }
                }
            }
        }
    }

    for (o = 0; o < 2; o++) {
        for (s = 0; s <= n + 50; s++) {
            for (b = 0; b < 256; b++) {
                int x = 0, y = b;
                if (y) {
                    while (!(y&1)) x++, y >>= 1;
                 }else {
                    if (o) x = 8;
                    else if (s) x = s + 8;
                }
                ans += f[n][o][s][b] * x;
            }
        }
    }

    ans /= base;

    printf("%.10lf", ans);
    return 0;
}
