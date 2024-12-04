#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

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

namespace BIT {
    const int M = 1e9;
    int tot;
    unordered_map<int, int > L, R;
#define lowbit(x) ((x) & -(x))
    inline void upd(int l, int r) {
        tot++;
        for (; l; l -= lowbit(l)) L[l]++;
        for (; r <= M; r += lowbit(r)) R[r]++;
    }
    inline int query(int l, int r) {
        int res = tot;
        for (; l <= M; l += lowbit(l)) if (L.count(l)) res -= L[l];
        for (; r; r -= lowbit(r)) if (R.count(r)) res -= R[r];
        return res;
    }
}
using namespace BIT;

int n, ans[N];
array<int, 3 > ops[N];
array<int, 4 > qs[N];

int main() {
    io >> n;
    int l, r, k;
    For (i, 1, n) io >> l >> r >> k, qs[i] = {k, r - k + 1, l + k - 1, i}, ops[i] = {r - l, l, r};
    sort(qs + 1, qs + n + 1); sort(ops + 1, ops + n + 1);
    int t = n;
    rFor (i, n, 1) {
        auto [k, l, r, id] = qs[i]; 
        while (t && ops[t][0] >= k) upd(ops[t][1], ops[t][2]), t--;
        ans[id] = query(l, r) - 1;
    }
    For (i, 1, n) printf("%d\n", ans[i]);

    return 0;
}
