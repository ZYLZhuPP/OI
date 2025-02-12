#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 15;

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

int n, K, a[N], b[N], ans;

inline int solve() {
    int res = 0, flag;
    do {
        flag = 0;
        For (i, 1, n - 1) if (b[i] > b[i + 1]) swap(b[i], b[i + 1]), flag = 1;
        rFor (i, n - 1, 1) if (b[i] > b[i + 1]) swap(b[i], b[i + 1]), flag = 1;
        res += flag;
    } while (flag);
    return res;
}

inline bool check() {
    For (i, 1, n) b[i] = a[i];
    return solve() <= K;
}

int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    io >> n >> K;
    For (i, 1, n) a[i] = i;
    do ans += check(); while (next_permutation(a + 1, a + n + 1));
    printf("%d", ans);

    fclose(stdin); fclose(stdout);
    return 0;
}
