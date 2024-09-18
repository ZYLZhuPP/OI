#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, a[N], pos[N], tot;
char ch[N];

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

int main() {
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]), pos[a[i]] = i;
	
	a[n + 1] = 0;
	
	for (int i = 2; i <= n; ch[pos[i]] = tot, i++) {
		if (a[pos[i-1] + 1] > a[pos[i] + 1]) tot++; 
	}
	
	if (tot >= 26) {
		puts("-1");
		return 0;
	}
	
	for (int i = 1; i <= n; i++) putchar(ch[i] + 'a');
	
	return 0;
}

