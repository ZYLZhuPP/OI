#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int Bit = 35;

int n, m, x, a[Bit], ch[N*Bit][2], mark[N*Bit], chsiz;

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

void add(int pos) {
	int u = 0;
	for (int i = 0; i <= 32; i++) {
		int c = a[i];
		if (!ch[u][c]) ch[u][c] = ++chsiz;
		u = ch[u][c];
	}
	mark[u] = pos;
}

int main() {
	read(n); read(m);
	for (int i = 1; i <= n; i++) {
		read(x);
		for (int j = 32; j >= 0; j--) {
			a[j] = x&1;
			x >>= 1;
		} 
		add(i);
	}
	
	while (m--) {
		read(x);
		for (int j = 32; j >= 0; j--) {
			a[j] = x&1;
			x >>= 1;
		} 
		int u = 0;
		for (int j = 0; j <= 32; j++) {
			int c = a[j];
			if (!ch[u][!c]) u = ch[u][c];
			else u = ch[u][!c];
		}
		printf("%d\n", mark[u]);
	}
	return 0;
} 
