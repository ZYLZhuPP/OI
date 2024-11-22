#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)

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

int n, ans;
vector<int > a;

int main() {
    io >> n;
    int x;
    For (i, 1, n) io >> x, a.pb(x);
    while (--n) {
        int k = 0; while (k + 2 <= n && a[k] > a[k + 2]) k++;
        int x = a[k] + a[k + 1];
        a.erase(a.begin() + k); a.erase(a.begin() + k);
        k--; while (k >= 0 && a[k] < x) k--;
        a.insert(a.begin() + k + 1, x);
        ans += x;
    }
    printf("%d", ans);

    return 0;
}
