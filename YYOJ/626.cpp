#include<bits/stdc++.h>
using namespace std;

const int N = 2005;

int t, k, n, m, c[N][N], f[N][N];

#define gc() getchar()

template<class T>
inline bool read(T &x){
	x=0;
	bool f(0); 
	char ch(gc());
	for(; !isdigit(ch); f|=!(ch^45), ch=gc()) if(!(ch^EOF)) return 0;
	for(; isdigit(ch); ch=gc()) x=(x<<3)+(x<<1)+(ch^48);
	if(f) x=-x;
	return 1;
}

int main() {
	read(t); read(k);
	
	c[0][0] = 1;
	for (int i = 1; i < N; i++ ) {
	    c[i][0] = c[i][i] = 1;
	    for (int j = 1; j < i; j++) 
	        c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % k;
	    for (int j = 1, sum = 0; j < i; j++) {
	        sum += !c[i][j];
	        f[i][j] = f[i - 1][j] + sum;
	    }
	    for (int j = i; j < N; j++)
	        f[i][j] = f[i][j -1];
	}
	
	while (t--) {
		read(n); read(m);
		printf("%d\n", f[n][m]);
	}
	return 0;
} 

