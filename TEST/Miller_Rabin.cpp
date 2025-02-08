#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

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
	inline bool operator ~ () {return ~c;}
} io;

const int pri[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

inline ll mul(ll x, ll y, ll Mo) {
    ll r = x * y - Mo * ll(1.L / Mo * x * y);
    return r + Mo * ((r < 0) - (r >= Mo));
}

inline ll qPow(ll a, ll b, ll Mo) {
    ll res = 1;
    while (b) {
        if (b & 1) res = mul(res, a, Mo);
        a = mul(a, a, Mo);
        b >>= 1;
    }
    return res;
}

inline bool Miller_Rabin(ll n) {
    for (int i = 0; i < 12; ++i)
        if (pri[i] == n) return 1;
    ll u = n - 1; u /= u & -u;
    for (int i = 0; i < 12; ++i) {
        ll a = pri[i], v = qPow(a, u, n);
        if (v == 1) continue;
        for (; v ^ n - 1 && u < n - 1; u <<= 1) 
            v = mul(v, v, n);
        if (u == n - 1) return 0;
    }
    return 1;
}

int main() {
    ll n;
    cin >> n;
    cout << Miller_Rabin(n);
    return 0;
}/*O(12*log(n))判断[1, 2^64)内的素数
基于
费马小定理:a^(p-1) % p == 1
二次探测定理:x^2 % p == 1 的解有且仅有 x = 1 or p-1
令:p-1 = u << t
有:a^(u << (t - 1)) % p == 1 or p-1
若 == 1 则:a^(u << (t - 2)) % p == 1 or p-1
同理 递推
得:A={a^(u << (t - i)), i = t -> 0} 必为:1, (1, 1, ...), p-1, x1, x2, ...(x[i] != 1 or p-1) or 1, 1, 1, ...
由此 倒推 若a^u != 1 则不断平方必先出现 p-1 而非 1
*/
