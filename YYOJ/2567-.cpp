#include<bits/stdc++.h>
using namespace std;

const int Mo = 1e9 + 7;

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

int ans = 1;

int main() {
    scanf("%*[^\n]%*[\n]");
    scanf("%*[^\n]%*[\n]");
    while (1) {
        scanf("%*[^af]");
        char ch = gc();
        if (ch == 'a') break;
        scanf("%*[^(]%*[(]");
        int a, b, c = 1;
        io >> a >> b;
        if (io.c == ',') io >> c;
        if (c < 0) a = -a, b = -b, c = -c;
        if (a >= b) ans = 0;
        else ans = 1ll * ans * ((b - a + c - 1) / c) % Mo;
        scanf("%*[^\n]%*[\n]");
    }
    printf("%d", ans);

    return 0;
}
