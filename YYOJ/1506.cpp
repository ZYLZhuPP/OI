#include<bits/stdc++.h>
using namespace std;

typedef __int128 ll;

const int N = 1e5 + 5;
const ll INF = (ll)LLONG_MAX/3*LLONG_MAX;

template<class C> inline bool chkmax(C &x, const C &y) {return x<y? x=y, 1: 0;}
template<class C> inline bool chkmin(C &x, const C &y) {return x>y? x=y, 1: 0;}

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
}io;

ll n, a, b, c, d, dif[N], s[N], L, R, f[N], sc[N][26], tail = 0, l, r, q2[N];
char st[N];
deque<int > q1;

ll get(int l, int r) {
    ll res = 0;
    for (int i = 0; i < 26; i++) chkmax(res, sc[r][i] - sc[l][i]);
	return res;
}

ll f1(int x) {
	return f[x] - c*s[x] + d;
}

ll Y(int x) {
	return f[x] + a*s[x]*s[x];
}

ll X(int x) {
    return s[x];
}

ll dX(int x, int y) {
    return X(y) - X(x);
}

ll dY(int x, int y) {
    return Y(y) - Y(x);
}

bool better(int x, int y, int z) {
	return dY(x, y)*dX(y, z) >= dY(y, z)*dX(x, y);
}

void write(ll x) {
	if (!x) return;
	write(x/10);
	putchar((x%10)^48);
}

int main() {
    io >> n >> a >> b >> c >> d >> L >> R;
	scanf("%s", st + 1);
	for (int i = 1; i <= n; i++) io >> dif[i];
	
	for (int i = 1; i <= n; ++i) {
		f[i] = INF;
		s[i] = s[i-1] + dif[i];
		for (int j = 0; j < 26; j++) sc[i][j] = sc[i-1][j];
		sc[i][st[i]-'a']++; 
		
		while (tail < i && get(tail, i) >= L) {
			while (!q1.empty() && f1(tail) <= f1(q1.back())) q1.pop_back();
			q1.push_back(tail);
			tail++;
		}
        while (!q1.empty() && get(q1.front(), i) > R) q1.pop_front();
	    if (!q1.empty()) f[i] = f1(q1.front()) + c*s[i];
		
		int j = i-1;
		while (l<r && better(q2[r - 1], q2[r], j)) r--;
		q2[++r] = j;
		while (l<r && dY(q2[l], q2[l+1]) <= 2*a*s[i]*dX(q2[l], q2[l+1])) l++;
		chkmin(f[i], f[q2[l]] + a*(s[i]-s[q2[l]])*(s[i]-s[q2[l]]) + b);
		
		write(f[i]); puts("");
	}
	
	return 0;
} 

