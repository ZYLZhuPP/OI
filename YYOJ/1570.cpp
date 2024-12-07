#include<bits/stdc++.h>
using namespace std;

const int N = 5005;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
}io;

int a[N], n, ans;
map<vector<int >, bool> vis, v;
vector<int > b, c;

int get(int k) {
	if (k == b.size()) {
		if (v[c]) return 0;
		v[c] = 1;
		return 1;
	}
	
	int res = get(k + 1);
	c.push_back(b[k]);
	res += get(k + 1);
	c.pop_back();
	return res;
}

void dfs(int k) {
	if (k > n) {
		if (vis[b]) return;
		vis[b] = 1;
		map<vector<int >, bool> ().swap(v);
		ans += get(0);
		return;
	}
	
	dfs(k + 1);
	b.push_back(a[k]);
	dfs(k + 1); 
	b.pop_back();
}

int main() {
	io >> n;
	for (int i = 1; i <= n; ++i) io >> a[i];
	
	dfs(1);
	
	printf("%d", ans);
	return 0;
}
