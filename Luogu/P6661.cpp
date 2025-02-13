#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

struct IO {
	static const int BufS = 1 << 20;
	char ibuf[BufS], *S, *T, c; int f;
#define gc() ((S==T && (T=(S=ibuf)+fread(ibuf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
    inline IO& operator >> (char *x) {
        while ((c = gc()) < 33 && ~c);
        while (c > 32) *x++ = c, c = gc();
        *x = 0; return *this;
    }
	inline bool operator ~ () const { return ~c; }
} io;

int T, n, K, pos, ok[N];
char a[N], b[N];

int main() {
    io >> T;
    while (T--) {
        pos = 0;
        io >> (a + 1) >> (b + 1) >> K;
        n = strlen(a + 1);
        For (i, 1, n) ok[i] = ok[i - 1] + (a[i] != b[i]);
        rFor (i, n, 1) if (b[i] > '0' && K >= ok[i - 1] + (a[i] > b[i]-1) && n - i >= K - ok[i - 1] - !(b[i]=='1' && a[i]=='0')) {
            pos = i;
            K -= ok[i - 1];
            For (j, 1, pos - 1) a[j] = b[j];
            if (!K) break;
            if (a[i] != b[i]-1) a[i] = b[i] - 1, K--;
            else if (n - pos < K) a[i] = b[i] - 2, K--;
            while (pos++, K) if (a[pos] == '9') {
                if (n - pos < K) a[pos] = '8', K--; 
            } else a[pos] = '9', K--;
            break;
        }
        if (pos) printf("%s\n", a + 1);
        else puts("-1");
    }

    return 0;
}