#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 55;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, A, B, mn[N][N], mx[N][N], cnt1, cnt2, cnt3;
char s[N];

int main() {
    io >> n >> A >> B;
    For (i, 1, n) {
        scanf("%s", s + 1);
        For (j, 1, n) {
            if (s[j] == '+') mn[i][j] = 1, mx[i][j] = 2;
            if (s[j] == '-') mn[i][j] = -2, mx[i][j] = -1;
            if (s[j] == '=') mn[i][j] = mx[i][j] = 0;
            if (s[j] == '?') mn[i][j] = -2, mx[i][j] = 2;
        }
    }
    For (k, 1, n) For (i, 1, n) For (j, 1, n) cmax(mn[i][j], mn[i][k] + mn[k][j]), cmin(mx[i][j], mx[i][k] + mx[k][j]);
    For (i, 1, n) if (i ^ A && i ^ B) For (j, i + 1, n) if (j ^ A && j ^ B) {
        if (mn[A][i] > mx[j][B] || mn[A][j] > mx[i][B]) cnt1++;
        if (mn[A][i] == mx[A][i] && mx[A][i] == mx[j][B] && mx[j][B] == mn[j][B] ||
            mn[A][j] == mx[A][j] && mx[A][j] == mx[i][B] && mx[i][B] == mn[i][B]) cnt2++;
        if (mx[A][i] < mn[j][B] || mx[A][j] < mn[i][B]) cnt3++;
    }
    printf("%d %d %d", cnt1, cnt2, cnt3);

    return 0;
}
