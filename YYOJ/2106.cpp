#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (register int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;

struct IO {
    int c, f;
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

int n, a[N], pos[N];
ll m;

priority_queue<int > h;
void pre(int k) {
    if (!k) return;
    For (i, 1, n) pos[a[i]] = i;
    For (i, 1, k) a[i] = i, h.push(pos[i]);
    For (i, k + 1, n)
        if (pos[i] < h.top())
            a[h.top()] = i, h.pop(), h.push(pos[i]);
}

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i];
    For (i, 1, n) {
        if (m > n - i) m -= n - i;
        else {
            pre(i - 1);
            For (j, i + 1, n) {
                if (a[j] < a[i]) swap(a[i], a[j]);
                if (!--m) break;
            }
            For (j, 1, n) printf("%d ", a[j]);
            return 0;
        }
    }
}
