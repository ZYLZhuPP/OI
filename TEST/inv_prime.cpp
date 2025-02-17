#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int pri[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
ull n, ans;
int op;

namespace FACTOR {
    inline void dfs(int p, ull num, ull fac, int up) {
        if (fac > n || p >= 16) return;
        if (fac == n && ans > num) {
            ans = num;
            return;
        }
        for (int i = 1; i <= up; ++i) {
            if (num *pri[p] > ans) break;
            dfs(p + 1, num = num * pri[p], fac * (i + 1), i);
        }
    }
}

namespace NUM {
    inline void dfs(int p, ull num, ull fac, int up) {
        if (num > n || p >= 16) return;
        if (fac > ans) {
            ans = fac;
            return;
        }
        for (int i = 1; i <= up; ++i) {
            if (num *pri[p] > n) break;
            dfs(p + 1, num = num * pri[p], fac * (i + 1), i);
        }
    }
}

int main() {
    while (1) {
        io >> op;
        if (!op) break;
        io >> n;
        if (op == 1) {
            ans = ~0ull;
            FACTOR::dfs(0, 1, 1, 66);
            printf("%llu\n", ans);
        } else if (op == 2) {
            ans = 0ull;
            NUM::dfs(0, 1, 1, 66);
            printf("%llu\n", ans);
        }
    }

    return 0;
}
