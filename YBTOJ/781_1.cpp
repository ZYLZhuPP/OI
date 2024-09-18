#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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
	inline bool operator ~ () const { return ~c; }
} io;

int n, k, ans[N], cnt[N];

struct Node {
    int x, y, z, o, *ans;
    Node() { o = 0; ans = NULL; }
    bool operator == (const Node &a) const { return x==a.x && y==a.y && z==a.z; }
    bool operator < (const Node &a) const { return x^a.x? x<a.x: y^a.y? y<a.y: z<a.z; }
} a[N], b[N], c[N];

void cdq2(int l, int r) {
    if (l == r) return;
    int m = (l + r) >> 1;
    cdq2(l, m); cdq2(m + 1, r);
    for (int i = l, j = l, k = m + 1, s = 0; i <= r; ++i) {
        if (j <= m && (k > r || b[j].z <= b[k].z))
            c[i] = b[j++], s += !c[i].o;
        else {
            c[i] = b[k++];
            if (c[i].o) *c[i].ans += s;
        }
    }
    For (i, l, r) b[i] = c[i];
}

void cdq1(int l, int r) {
    if (l == r) return;
    int m = (l + r) >> 1;
    cdq1(l, m); cdq1(m + 1, r);
    for (int i = l, j = l, k = m + 1; i <= r; ++i) {
        if (j <= m && (k > r || a[j].y <= a[k].y))
            b[i] = a[j++], b[i].o = 0;
        else b[i] = a[k++], b[i].o = 1;
    }
    For (i, l, r) a[i] = b[i];
    cdq2(l, r);
}

int main() {
    io >> n >> k;
    For (i, 1, n) io >> a[i].x >> a[i].y >> a[i].z;
    sort(a + 1, a + n + 1);
    rFor (i, n - 1, 1) if (a[i] == a[i + 1]) ans[i] = ans[i + 1] + 1;
    For (i, 1, n) a[i].ans = &ans[i];
    cdq1(1, n);
    For (i, 1, n) cnt[ans[i]]++;
    For (i, 0, n - 1) printf("%d\n", cnt[i]);

    return 0;
}
