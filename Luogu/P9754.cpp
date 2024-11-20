#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 105;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

struct XX {
    string name; int id; ll sz;
} X[N];

struct TYPE {
    ll sz, fm;
    vector<XX > o;
} T[N];

int n, Ttot, Xtot;
ll Sz;
unordered_map<string, int > Tmp, Xmp;
string name, ans, tp;

inline ll up(ll x, ll y) { return x + (y - (x % y)) % y; }

inline void solve(int Tid, ll x) {
    if (Tid <= 4) return;
    ans.pb('.');
    int n = T[Tid].o.size(), id = 0;
    For (i, 0, n - 1) if (i == n - 1 || T[Tid].o[i + 1].sz > x) {
        id = T[Tid].o[i].id; ans += T[Tid].o[i].name; x -= T[Tid].o[i].sz;
        if (T[id].sz <= x) return ans = "ERR", void();
        break;
    }
    solve(id, x);
}

inline void init() {
    Tmp["byte"] = ++Ttot; T[Ttot].sz = T[Ttot].fm = 1;
    Tmp["short"] = ++Ttot; T[Ttot].sz = T[Ttot].fm = 2;
    Tmp["int"] = ++Ttot; T[Ttot].sz = T[Ttot].fm = 4;
    Tmp["long"] = ++Ttot; T[Ttot].sz = T[Ttot].fm = 8;
}

int main() {
    init();
    io >> n;
    int op;
    while (n--) {
        io >> op;
        if (op == 1) {
            int m;
            cin >> name; io >> m;
            Tmp[name] = ++Ttot;
            ll sz = 0, fm = 0;
            For (i, 1, m) {
                cin >> tp >> name; int id = Tmp[tp];
                sz = up(sz, T[id].fm);
                cmax(fm, T[id].fm);
                T[Ttot].o.pb({name, id, sz});
                sz += T[id].sz;
            }
            sz = up(sz, fm);
            printf("%lld %lld\n", sz, fm);
            T[Ttot].sz = sz; T[Ttot].fm = fm;
        } else if (op == 2) {
            cin >> tp >> name; int id = Tmp[tp];
            Xmp[name] = ++Xtot;
            Sz = up(Sz, T[id].fm);
            printf("%lld\n", Sz);
            X[Xtot] = {name, id, Sz};
            Sz += T[id].sz;
        } else if (op == 3) {
            name = ""; char c;
            while (isalpha(c = gc())) name.pb(c);
            int Xid = Xmp[name]; ll x = X[Xid].sz;
            int Tid = X[Xid].id;
            while (c == '.') {
                name = "";
                while (isalpha(c = gc())) name.pb(c);
                for (auto &[Name, id, sz] : T[Tid].o) if (name == Name) {
                    x += sz; Tid = id;
                    break;
                }
            }
            printf("%lld\n", x);
        } else if (op == 4) {
            ll x;
            io >> x;
            int Xid = 0;
            For (i, 1, Xtot) if (i == Xtot || X[i + 1].sz > x) { Xid = i; break; }
            int Tid = X[Xid].id; x -= X[Xid].sz; ans = X[Xid].name;
            if (T[Tid].sz <= x) { puts("ERR"); continue; }
            solve(Tid, x);
            cout << ans << endl;
        }
    }

    return 0;
}
