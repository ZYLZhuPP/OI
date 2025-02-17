#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505;

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

int n, a[N], cnt;

bool ck() {
    For (i, 1, n) if (a[i] == 1) {
        printf("%d\n", i), fflush(stdout), a[i] = 0;
        int x; io >> x; return 1;
    }
    puts("-1"), fflush(stdout);
    return 0;
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i], cnt += a[i] > 1;
    do {
        int x;
        io >> x;
        if (a[x] == 1) puts("1"), fflush(stdout), a[x] = 0;
        else {
            if (cnt == 1) printf("%d\n", a[x]), fflush(stdout), a[x] = 0, cnt--;
            else printf("%d\n", a[x] - 1), fflush(stdout), a[x] = 1, cnt--;
        }
    } while (ck());

    return 0;
}
