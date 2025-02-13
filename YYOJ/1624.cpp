#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 20;

struct IO {
	char c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int num[N], now[10];
ll L, R;
const char to[N] = "0123456789ABCDEFGHI";
unordered_map<string, ll > mp;

void getid(int k, string &st) {
    st += to[k];
    st += to[now[7]];
    For (i, 0, 9) if (i ^ 7) st += to[now[i]];
    sort(st.begin() + 2, st.end());
}

ll get(int k) {
    string st; getid(k, st);
    return mp[st];
}

void chg(int k, ll w) {
    string st; getid(k, st);
    mp[st] = w;
}

ll dfs(int k) {
    if (k < 0) return 0;
    if (k == 0) {
        For (i, 0, 9) if (now[i] == now[7] && i != 7) return 0;
        return 1;
    }
    ll res = get(k);
    if (res) return res;
    For (i, 0, 9) {
        now[i]++; res += dfs(k - 1); now[i]--;
    }
    chg(k, res);
    return res;
}

ll solve(ll n) {
    ll res = 0;
    int len = 0;
    while (n) num[++len] = n % 10, n /= 10;
    for (int i = len; i >= 1; --i) {
        For (j, i == len, num[i] - 1) {
            now[j]++; res += dfs(i - 1); now[j]--;
        }
        now[num[i]]++;
    }
    memset(now, 0, sizeof(now));
    For (i, 2, len) {
        For (j, 1, 9) {
            now[j]++; res += dfs(i - 2); now[j]--;
        }
    }
    return res;
}

int main() {
    io >> L >> R;
    printf("%lld", solve(R + 1) - solve(L));

    return 0;
}
