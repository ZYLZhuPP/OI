#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e4 + 5, Mo = 123456789;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m, a[N], b[N], c;

struct Bit {
    vector<int > o;
    Bit() { o.resize(N, 0); }
#define lowbit(x) ((x) & -(x))
    void upd(int i, int d) { for (; i < N; i += lowbit(i)) add(o[i], d); }
    int pre(int i) { int r = 0; for (; i; i -= lowbit(i)) add(r, o[i]); return r; }
};

int main() {
    while (~(io >> n >> m)) {
        For (i, 1, n) io >> a[i], b[i] = a[i];
        sort(b + 1, b + n + 1); c = unique(b + 1, b + n + 1) - b - 1;
        For (i, 1, n) a[i] = lower_bound(b + 1, b + c + 1, a[i]) - b;

        Bit tr[m + 1];
        For (i, 1, n) {
            tr[1].upd(a[i], 1);
            For (j, 2, m) tr[j].upd(a[i], tr[j - 1].pre(a[i] - 1));
        }

        printf("%d\n", tr[m].pre(c));
    }

    return 0;
}
