#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

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

int T, C, n;
array<int, 2 > a[N];

int main() {
    io >> T;
    while (T--) {
        bool flag = 1;
        io >> C >> n;
        For (i, 1, n) io >> a[i][0] >> a[i][1];
        sort(a + 1, a + n + 1);
        For (i, 1, n) {
            int d = a[i][0] - a[i - 1][0];
            if (d >= abs(a[i][1]) + 1) continue;
            if (d >= abs(a[i][1] - a[i - 1][1]) && d % 2 == abs(a[i][1] - a[i - 1][1]) % 2) continue;
            flag = 0;
            break;
        }
        puts(flag? "Yes": "No");
    }

    return 0;
}
