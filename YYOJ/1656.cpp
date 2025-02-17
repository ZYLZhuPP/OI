#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i) 
typedef long long ll;
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
    inline IO& operator >> (char &x) {
        while ((c = gc()) < 33 && ~c);
        x = c; return *this;
    }
    inline bool operator ~() {return ~c;}
} io;

int n, d, m;
char x, y, a[N];
ll s[26][26], f[26], ans;
bool ok[26];

int main() {
    io >> n;
    scanf("%s", a + 1);
    io >> m;
    For (i, 1, m) {
        io >> x >> y >> d;
        s[x - 'a'][y - 'a'] += d;
    } 
    
    For (i, 1, n) {
        int c = a[i] - 'a';
        ll res = 0;
        For (j, 0, 25) if (ok[j]) res = max(res, f[j] + s[j][c]);
        f[c] = res;
        ok[c] = 1;
        ans = max(ans, res);
    }
    
    printf("%lld", ans);
    
    return 0;
} 
