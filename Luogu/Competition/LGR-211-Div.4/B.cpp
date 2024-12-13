#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 4e5 + 5;

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

int x[5], y[5], ans;

int main() {
    For (i, 1, 4) cin >> x[i];
    For (i, 1, 4) cin >> y[i];
    For (i, 1, 3) For (j, i + 1, 4) if ((x[i] - x[j]) * (y[i] - y[j]) < 0) ans++;
    cout << ans;

    return 0;
}
