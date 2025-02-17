#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

struct IO {
    static const int BufS = 1 << 20;
    char ibuf[BufS], *S, *T, c; int f;
#define gc() ((S==T && (T=(S=ibuf)+fread(ibuf, 1, BufS, stdin)), S==T)? EOF: *S++)
    inline IO& operator >> (char *x){
        while ((c = gc()) < 33 && ~c);
        while (c > 32) *x++ = c, c = gc();
        *x = 0; return *this;
    }
    char obuf[BufS]; int E, st[66], t;
#define pc(c) (obuf[E==BufS && (E-=fwrite(obuf, 1, BufS, stdout)), E++]=c)
    inline void flush() {fwrite(obuf, 1, E, stdout);}
    ~IO() {flush();}
    template<class C>
    inline IO& operator << (C x) {
        while (x) st[++t] = x % 10, x /= 10;
        while (t) pc(st[t--] ^ 48);
        return *this;
    }
    inline IO& operator << (char x) {
        pc(x); return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int sa[N];
char s[N];

namespace SA {
    int cnt[N], _[2][N], *x = _[0], *y = _[1];
    void main(const char *s, int n, int m, int *sa) {
        int t = 0;
        For(i, 0, m) cnt[i] = 0; For (i, 1, n) cnt[y[i] = s[i]]++;
        For (i, 1, m) cnt[i] += cnt[i - 1];
        rFor (i, n, 1) sa[cnt[y[i]]--] = i;

        for (int j = 1; ; j <<= 1) {
            swap(x, y);

            t = 0; For (i, n - j + 1, n) y[++t] = i;
            For (i, 1, n) if (sa[i] > j) y[++t] = sa[i] - j;

            For(i, 0, m) cnt[i] = 0; For (i, 1, n) cnt[x[i]]++;
            For (i, 1, m) cnt[i] += cnt[i - 1];
            rFor (i, n, 1) sa[cnt[x[y[i]]]--] = y[i];

            m = 0; For (i, 1, n) y[sa[i]] = m += x[sa[i - 1]] ^ x[sa[i]] || x[sa[i - 1] + j] ^ x[sa[i] + j];
            if (m == n) break;
        }
    }
}

int main() {
    io >> (s + 1);
    int n = strlen(s + 1);
    SA::main(s, n, 122, sa);
    For (i, 1, n) io << sa[i] << ' ';

    return 0;
}
