#include<bits/stdc++.h>
using namespace std;

const int N = 22, N_2 = (1 << 20) + 5;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int n, K, STA, mi[N][N_2], cnt[N_2], f[N_2], ans;
vector<int > Cnt[N];

int lowbit(int x) {return x & -x;}

int main() {
	io >> n >> K; STA = 1 << n; 
	memset(mi, 31, sizeof(mi));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) io >> mi[i][1 << j];
	}
	
	for (int i = 0; i < n; ++i) {
		for (int j = 3; j < STA; ++j) if (j - lowbit(j)) {
			mi[i][j] = min(mi[i][lowbit(j)], mi[i][j - lowbit(j)]);
		}
	}
	
	cnt[0] = 0;
	Cnt[0].push_back(0);
	for (int i = 1; i < STA; ++i) {
		cnt[i] = cnt[i - lowbit(i)] + 1;
		Cnt[cnt[i]].push_back(i);
	}
	
	memset(f, 31, sizeof(f)); ans = f[0];
	f[0] = 0;
	for (int i = 1; i <= n - K; ++i) {
		for (auto &j : Cnt[i]) {
			for (int k = 0; k < n; ++k) if (j & (1 << k)) {
				f[j] = min(f[j], f[j - (1 << k)] + mi[k][(~j) & (STA - 1)]);
			}
		}
	}
	
	for (auto &i : Cnt[n - K]) ans = min(ans, f[i]);
	
	printf("%d", ans);
	
	return 0;
} 
