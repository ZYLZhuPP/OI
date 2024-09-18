#include<bits/stdc++.h>
using namespace std;

const double eps = 1e-10;
const int N = 405;

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x * 10) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int T, n, A, B, Q;
double x[N], y[N], t[N], ans, dis[N][N];

double d(int i, int j) {
    return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}

void add(int o) {
    for (int i = 0; i < 3; ++i) {
        int a = o + i, b = o + (i + 2) % 3, c = o + (i + 1) % 3;
        if (fabs(d(a, b) * d(a, b) + d(a, c) * d(a, c) - d(b, c) * d(b, c)) < eps) {
            swap(x[a], x[o]); swap(y[a], y[o]);
            break;
        }
    }
    x[o + 3] = x[o + 1] + x[o + 2] - x[o];
    y[o + 3] = y[o + 1] + y[o + 2] - y[o];
}

double dist(int i, int j) {
    if (i / 4 == j / 4) {
        return d(i, j) * t[i / 4];
    } else 
        return d(i, j) * T;
}

int main() {
    io >> Q;
    while (Q--) {
        ans = 1e20;
        io >> n >> T >> A >> B; A--; B--;
        for (int i = 0; i < n; ++i) {
            for (int j = i * 4; j < i * 4 + 3; ++j) {
                io >> x[j] >> y[j];
            }
            add(i * 4);
            io >> t[i];
        }

        for (int i = 0; i < n * 4; ++i) {
            for (int j = 0; j < n * 4; ++j) dis[i][j] = dist(i, j);
        }

        for (int k = 0; k < n * 4; ++k) {
            for (int i = 0; i < n * 4; ++i) {
                for (int j = 0; j < n * 4; ++j) {
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) ans = min(ans, dis[A * 4 + i][B * 4 + j]);
        }

        printf("%.1lf\n", ans);
    }

    return 0;
}
