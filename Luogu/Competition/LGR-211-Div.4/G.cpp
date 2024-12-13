#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 105;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, m;
string s[N], t[N];

int main() {
    io >> n;
    For (i, 1, n) cin >> s[i];
    io >> m;
    For (i, 1, m) cin >> t[i];
    For (i, 1, n) {
        bool flag = 1;
        For (j, 1, m) flag &= s[i].find(t[j]) >= s[i].size();
        puts(flag? "No": "Yes");
    }

    return 0;
}
