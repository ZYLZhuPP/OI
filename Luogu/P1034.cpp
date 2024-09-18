#include<bits/stdc++.h>
using namespace std;

const int N = 55;

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int n, k, ans, x[N], y[N];

struct mat {
    int cnt, lx, ly, rx, ry;

    void add(int x, int y) {
        cnt++;
        if (cnt == 1) lx = rx = x, ly = ry = y;
        else {
            lx = min(lx, x);
            rx = max(rx, x);
            ly = min(ly, y);
            ry = max(ry, y);
        }
    }

    bool isin(int x, int y) const {
        return lx <= x && x <= rx && ly <= y && y <= ry;
    }

    int operator () () const {
        if (!cnt) return 0;
        return (rx - lx) * (ry - ly);
    }

    bool operator * (const mat &X) const {
        if (!cnt || !X.cnt) return 0;
        return X.isin(lx, ly) || X.isin(lx, ry) || X.isin(rx, ly) || X.isin(rx, ry);
    }
} m[5];

bool check() {
    for (int i = 1; i <= k; ++i) 
        for (int j = 1; j < i; ++j) if (m[i] * m[j]) return 0;
    return 1;
}

void dfs(int i, int s) {
    if (s >= ans) return;
    if (i > n) {
        if (check()) ans = s;
        return;
    }

    mat back;
    for (int j = 1; j <= k; ++j) {
        back = m[j];
        m[j].add(x[i], y[i]);
        dfs(i + 1, s - back() + m[j]());
        m[j] = back;
    }
}

int main() {
    io >> n >> k;
    for (int i = 1; i <= n; ++i) {
        io >> x[i] >> y[i];
    }

    ans = INT_MAX;
    dfs(1, 0);

    printf("%d", ans);

    return 0;
}
