#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1005;

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
	inline bool operator ~ () { return ~c; }
} io;

int n, m, L, a[N][N], mi1[N][N], mi2[N][N], ma1[N][N], ma2[N][N];
int q[N], ans = INT_MAX;

int main() {
    io >> n >> m >> L;
    For (i, 1, n) For (j, 1, m) io >> a[i][j];

    For (i, 1, n) {
        int h = 1, t = 0;
        For (j, 1, m) {
            while (h <= t && q[h] <= j - L) h++;
            while (h <= t && a[i][q[t]] >= a[i][j]) t--;
            q[++t] = j;
            if (j >= L) mi1[i][j] = a[i][q[h]];
        }
    }
    For (j, L, m) {
        int h = 1, t = 0;
        For (i, 1, n) {
            while (h <= t && q[h] <= i - L) h++;
            while (h <= t && mi1[q[t]][j] >= mi1[i][j]) t--;
            q[++t] = i;
            if (i >= L) mi2[i][j] = mi1[q[h]][j];
        }
    }

    For (i, 1, n) {
        int h = 1, t = 0;
        For (j, 1, m) {
            while (h <= t && q[h] <= j - L) h++;
            while (h <= t && a[i][q[t]] <= a[i][j]) t--;
            q[++t] = j;
            if (j >= L) ma1[i][j] = a[i][q[h]];
        }
    }
    For (j, L, m) {
        int h = 1, t = 0;
        For (i, 1, n) {
            while (h <= t && q[h] <= i - L) h++;
            while (h <= t && ma1[q[t]][j] <= ma1[i][j]) t--;
            q[++t] = i;
            if (i >= L) ma2[i][j] = ma1[q[h]][j];
        }
    }

    For (i, L, n) For (j, L, m) ans = min(ans, ma2[i][j] - mi2[i][j]);
    printf("%d", ans);

    return 0;
}
