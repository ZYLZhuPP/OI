#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int n, q;
char s[N];

namespace Seg {
    struct Node {
        int a, b, c, ab, bc, abc;
        Node(char ch = ' ') {
            a = ch=='a'; b = ch=='b'; c = ch=='c';
            ab = bc = abc = 0;
        }
    } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) {
        o[p].a = o[ls].a + o[rs].a;
        o[p].b = o[ls].b + o[rs].b;
        o[p].c = o[ls].c + o[rs].c;
        o[p].ab = min(o[ls].a + o[rs].ab, o[ls].ab + o[rs].b);
        o[p].bc = min(o[ls].b + o[rs].bc, o[ls].bc + o[rs].c);
        o[p].abc = min(o[ls].ab + o[rs].bc, min(o[ls].a + o[rs].abc, o[ls].abc + o[rs].c));
    }
    inline void build(int p, int l, int r) {
        if (l == r) return void(o[p] = Node(s[l]));
        M; build(goL); build(goR); up(p);
    }
    inline void upd(int p, int l, int r, int x, const char &ch) {
        if (l > x || r < x) return;
        if (l == r) return void(o[p] = Node(ch));
        M; upd(goL, x, ch); upd(goR, x, ch); up(p);
    }
}
using namespace Seg;

int main() {
    io >> n >> q;
    scanf("%s", s + 1);
    build(1, 1, n);
    while (q--) {
        int x; char ch[2];
        io >> x; scanf("%s", ch);
        upd(1, 1, n, x, ch[0]);
        printf("%d\n", o[1].abc);
    }

    return 0;
}
