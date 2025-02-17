#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 3e5 + 5;

struct IO {
    static const int BufS=1<<20;
    char ibuf[BufS], *iS, *iT, obuf[BufS], c;
    int top, f, num[66], t;
#define gc() ((iS==iT && (iT=(iS=ibuf)+fread(ibuf, 1, BufS, stdin)), iS==iT)? EOF: *iS++)
    #define pc(c) (obuf[top==BufS? fwrite(obuf, 1, BufS, stdout), !(top=1): top++]=c)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline void flush() {fwrite(obuf, 1, top, stdout);}
    ~IO() {flush();}
    template<class C>
    inline IO& operator << (C x) {
        if (!x) pc('0'); if (x < 0) pc('-'), x = -x;
        while (x) num[++t] = x % 10, x /= 10;
        while (t) pc(num[t--] ^ 48);
        return *this;
    }
    inline IO& operator << (char x) {
        pc(x);
        return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

ll n, h[N], st[N], ed[N], L, R, H, l1, r1;
vector<ll > ans;
stack<ll > q;

ll get(int i, ll x) {
    if (x <= 1) return x;
    if (ed[i] - st[i] + 1 <= x) return (ll)(i - st[i] + 1) * (ed[i] - i + 1);
    
    ll res = 0;
    ll l = i - st[i] + 1, r = ed[i] - i + 1; if (l > r) swap(l, r);
    if (x <= l) return x * (x + 1) / 2; res += l * (l + 1) / 2;
    if (x <= r) return res + l * (x - l); res += l * (r - l);
    return res + (l - 1 + (l - (x - r))) * (x - r) / 2;  
} 

ll pre(ll x) {
    ll res = 0;
    for (int i = 1; i <= n; ++i) {
        ll cnt = (x - 1) / h[i];
        res += get(i, cnt);
    }
    return res;
}

int main() {
    io >> n;
    for (int i = 1; i <= n; ++i) {
        io >> h[i]; H = max(H, h[i] * n); 
        st[i] = 1; ed[i] = n;
        while (!q.empty() && h[q.top()] > h[i]) ed[q.top()] = i - 1, q.pop();
        if (!q.empty()) st[i] = q.top() + 1;
        q.push(i);
    }
    io >> L >> R;
    
    ll l = 1, r = H;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (pre(mid) < L) l1 = mid, l = mid + 1;
        else r = mid - 1;
    }
    
    l = l1, r = H;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (pre(mid) < R) r1 = mid, l = mid + 1;
        else r = mid - 1;
    }
    
    if (l1 == r1) {
        for (int i = 0; i <= R - L; ++i) io << l1 << ' ';
        return 0;
    }
    
    ll cntl = pre(l1 + 1) - L + 1;
    ll cntr = R - pre(r1);
        
    for (int i = 1; i <= n; ++i) {
        ll len = ed[i] - st[i] + 1;
        ll a = (l1 + 1 + h[i] - 1) / h[i], b = (r1 - 1) / h[i];
        for (int j = a; j <= b && j <= len; ++j) {
            ll cnt = get(i, j) - get(i, j - 1);
            for (int k = 1; k <= cnt; ++k) ans.push_back(h[i] * j);
        }
    }
    
    for (int i = 1; i <= cntl; ++i) io << l1 << ' ';
    sort(ans.begin(), ans.end());
    for (auto &x : ans) io << x << ' ';
    for (int i = 1; i <= cntr; ++i) io << r1 << ' ';

    return 0;
} 

