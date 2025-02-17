#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll Mo = 1e9 + 7;

struct XY {
    ll n[3][3]; 
    
    XY operator * (const XY &x) {
        XY res;
        memset(res.n, 0, sizeof(res.n));
        for (int i = 0; i < 3; ++i) 
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    (res.n[i][j] += n[i][k] * x.n[k][j]) %= Mo;
        return res;
    }
};

ll n, x, y, ans;

#define gc() getchar() 

template<class C>
inline bool read(C &x) {
    x=0;
    int f=1;
    char c=gc();
    for(; !isdigit(c); c=gc()) 
        if(!(c^EOF)) return 0;
        else if(!(c^45)) f=-1;
    for(; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48);
    x*=f;
    return 1;
}

inline XY quickPow(XY a, ll b) {
    XY res = a; b--;
    while (b) {
        if (b&1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

inline ll quickPow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b&1) (res *= a) %= Mo; 
        (a *= a) %= Mo;
        b >>= 1;
    }
    return res;
}

int main() {
    read(n);
    
    if (n == 1) {
        puts("1");
        return 0;
    }
    
    if (n == 2) {
        puts("500000005");
        return 0;
    }
    
    XY a;
    a.n[0][2] = a.n[1][0] = a.n[1][2] = 0;
    a.n[0][0] = a.n[1][1] = a.n[2][0] = 2;
    a.n[0][1] = a.n[2][1] = a.n[2][2] = 1;
    XY b = quickPow(a, n - 2);
    x = 2*b.n[2][0] + 2*b.n[2][1] + 3*b.n[2][2];
    y = quickPow(2, n - 1);
    y = quickPow(y, Mo - 2);
    ans = x * y % Mo;
    
    printf("%lld", ans);
    
    return 0;
} 
