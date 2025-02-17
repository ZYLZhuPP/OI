#include<bits/stdc++.h>
using namespace std;

#define pi M_PI

typedef complex<double > com;

const int N = 3e6 + 5;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x){
        for(f=1; !isdigit(c); c=gc()) f|=-!(c^45);
        for(x=0; isdigit(c); c=gc()) x=(x*10)+(c^48); x*=f;
        return *this;
    }
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int n, m, x;
com a[N], b[N];

void reverse(com a[], int n) {
    int bit = 0; 
    vector<int > rev(n);
    while ((1 << bit) < n) bit++;
    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
}

void FFT(com a[], int n, int inv) {
    reverse(a, n);
    for (int mid = 1; mid < n; mid <<= 1) {
        com o(cos(pi / mid), inv * sin(pi / mid));
        for (int i = 0; i < n; i += mid*2) {
            com p(1, 0);
            for (int j = 0; j < mid; j++, p *= o) {
                com x = a[i + j], y = p * a[i + j + mid];
                a[i + j] = x + y; a[i + j + mid] = x - y;
            }
        }
    }
}

int main() {
    io >> n >> m;
    for (int i = 0; i <= n; ++i) io >> x, a[i] = com(x, 0);
    for (int i = 0; i <= m; ++i) io >> x, b[i] = com(x, 0);
    int k = 1; while (k <= n + m) k <<= 1;
    FFT(a, k, 1); FFT(b, k, 1);
    for (int i = 0; i < k; ++i) a[i] *= b[i];
    FFT(a, k, -1);
    for (int i = 0; i <= n + m; ++i) 
        printf("%d ", (int)(a[i].real()/k + 0.5));
    return 0;
}
