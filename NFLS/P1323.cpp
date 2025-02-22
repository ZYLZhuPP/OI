#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e5 + 5;

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

int a[N], T, n, x, pos[N];
vector<array<int, 2 > > ans;

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const int &d) { for (; x < N; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

void swap0(int x, int y) { ans.pb({x, y}), swap(pos[a[x]], pos[a[y]]), swap(a[x], a[y]); }
void move(int l, int r, int p) {
    if(pos[p] == p) return;
    int t1 = p + (p^r? 1: -1), t3 = p + (p^r? 3: -3);
    if (~(pos[p] ^ p) & 1) {
        if (~(pos[x] ^ p) & 1) swap0(t1, pos[x]);
        swap0(pos[x], pos[p]);
    }
    if (pos[x] ^ p) {
        if (~(pos[x] ^ p) & 1) swap0(pos[p]^t1? t1: t3, pos[x]);
        swap0(p, pos[x]);
    }
    swap0(p, pos[p]);
}

int main() {
    freopen("big.in","r",stdin);
    freopen("big.out","w",stdout);
    io >> T;
    while (T--) {
        io >> n >> x;
        For (i, 0, n) o[i] = 0;
        For (i, 1, n) io >> a[i], pos[a[i]] = i;
        bool flag = (pos[x] ^ x) & 1;
        rFor (i, n, 1) flag ^= query(a[i]) & 1, upd(a[i], 1);
        if(flag) { puts("NO"); continue; }
        ans.clear(); int l = 1, r = n;
        For (i, 1, n - 3) if(l == x) { move(l, r, r); r--; } else { move(l, r, l); l++; }
        while (pos[x] < x) swap0(pos[x], pos[x] + 1);
        while (pos[x] > x) swap0(pos[x], pos[x] - 1);
        puts("YES");
        printf("%d\n", (int)ans.size());
        for (auto &[x, y] : ans) printf("%d %d\n", x, y);
    }

    fclose(stdin); fclose(stdout);
    return 0;
}