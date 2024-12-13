#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
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

const string T = "bessie";
int n, m;
char s[N];

namespace Seg {
    struct Node {
        ll to[6], L[6], R[6], s;
        Node(char c = ' ', int pos = 0) {
            memset(to, 0, sizeof to); memset(L, 0, sizeof L); memset(R, 0, sizeof R); s = 0;
            if (pos) {
                For (i, 0, 5) to[i] = T[i]==c? (i + 1) % 6: i;
                R[to[0]] = 1; if (c == T[5]) L[5] = n - pos + 1;
            }
        }
        Node operator + (const Node &a) const {
            Node r; r.s = s + a.s;
            For (i, 0, 5) {
                r.to[i] = a.to[to[i]];
                r.L[i] = L[i] + a.L[to[i]];
                r.R[i] += a.R[i]; r.R[a.to[i]] += R[i];
                r.s += R[i] * a.L[i];
            }
            return r;
        }
    } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = o[ls] + o[rs]; }
    inline void build(int p, int l, int r) {
        if (l == r) return o[p] = Node(s[l], l), void();
        M; build(goL); build(goR); up(p);
    }
    inline void upd(int p, int l, int r, int x, char c) {
        if (l == r) return o[p] = Node(c, x), void();
        M; x<=m? upd(goL, x, c): upd(goR, x, c); up(p);
    }
}
using namespace Seg;

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    build(1, 1, n);
    printf("%lld\n", o[1].s);
    io >> m;
    int x; char op[3];
    while (m--) io >> x, scanf("%s", op), upd(1, 1, n, x, op[0]), printf("%lld\n", o[1].s);

    return 0;
}
