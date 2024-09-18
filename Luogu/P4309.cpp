#include<bits/stdc++.h>
using namespace std;

template<class C> inline bool chkmax(C &x, const C &y) { return x<y? x=y, 1: 0; } 

const int N = 1e5 + 5;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) if(!(c^45)) f=-1;
		for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int n, f[N], tr[N];
vector<int > a;

int lowbit(int x) {	return x&-x; }

void update(int pos, int val) {
	for (; pos <= n; pos += lowbit(pos))
		chkmax(tr[pos], val);
}

int query(int pos) {
	int res = 0;
	for (; pos; pos -= lowbit(pos))
		chkmax(res, tr[pos]);
	return res;
}

int main() {
	io >> n;
	for (int i = 1; i <= n; i++) {
		int x;
		io >> x;
		a.insert(a.begin()+x, i);
	}
	
	for (int i = 0; i < n; i++) {
		int x = a[i];
		update(x, f[x] = query(x-1)+1);
	}
	
	for (int i = 1; i <= n; i++) 
		printf("%d\n", f[i] = max(f[i], f[i - 1]));
	return 0;
}
