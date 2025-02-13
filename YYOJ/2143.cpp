#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, M = 350, Mo = 998244353;
inline void add(int &x, const int &y) { x = x+y>=Mo? x+y-Mo: x+y; }
inline void del(int &x, const int &y) { x = x-y<0? x-y+Mo: x-y; }

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
	inline bool operator ~ () { return ~c; }
} io;

int w[N], sum[M], s[M][N], d[M], L[M], R[M], f[N];
int n, B, lst[N], lst_[N], ans, k;

namespace Block {
	inline void change(int x, int ad) {
		int b = x / B + 1;
		del(s[b][w[x]], f[x]);
		del(sum[b], ((w[x] + d[b]) <= k) * f[x]);
		w[x] += ad;
		add(s[b][w[x]], f[x]);
		add(sum[b], ((w[x] + d[b]) <= k) * f[x]);
	}
	inline void upd(int l, int r, int ad) {
		if (l > r) return; 
		int bl = l / B + 1, br = r / B + 1;
		if (bl == br) For (i, l, r) change(i, ad);
		else  {
			For (i, l, R[bl]) change(i, ad);
			For (i, L[br], r) change(i, ad);
			For (i, bl + 1, br - 1) {
				if (ad > 0) del(sum[i], s[i][k - d[i]]), d[i] += ad;
				else d[i] += ad, add(sum[i], s[i][k - d[i]]);
			}
		}
	}
	inline int query(int x) {
		int res = 0, b = x / B + 1;
		For (i, 1, b - 1) add(res, sum[i]);
		For (i, L[b], x) add(res, ((w[i] + d[b]) <= k) * f[i]);
		return res;
	}
}
using namespace Block;

int main() {
	io >> n >> k;
	B = sqrt(n) + 1;
	For (i, 1, B) L[i] = (i - 1) * B, R[i] = i * B - 1;
	R[B] = n;
	f[0] = s[1][0] = sum[1] = 1;
	int x;
	For (i, 1, n) {
		//For (j, 1, B) cout << sum[j] << " ";
		//cout << endl;
		io >> x;
		int l1 = lst[x], l2 = lst_[x];
		lst_[x] = lst[x]; lst[x] = i;
		upd(l1, i - 1, 1); upd(l2, l1 - 1, -1);
		f[i] = query(i - 1); //cout << f[i] << endl;
		int b = i / B + 1;
		add(s[b][0], f[i]); add(sum[b], f[i]);
	}
	printf("%d", f[n]);
}

