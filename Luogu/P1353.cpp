#include<bits/stdc++.h>
using namespace std;

const int N=1e4+5;
const int M=505;

int n,m,f[N][M],d[N];

#define gc() getchar()

template<class T>
inline bool read(T &x){
	x=0;
	int f=1;
	char ch=gc();
	for(; !isdigit(ch); ch=gc())
		if(!(ch^'-')) f=-1;
		else if(!(ch^EOF)) return 0;
	for(; isdigit(ch); ch=gc()) x=(x<<3)+(x<<1)+(ch^48);
	x*=f;
	return 1;
}

int main(){
	read(n); read(m);
	for(int i=1; i<=n; i++)read(d[i]);
	for(int i=1; i<=n; i++){
		f[i][0]=max(f[i][0], f[i-1][0]);
		for(int j=1; j<=m; j++){
			f[i][j]=max(f[i][j], f[i-1][j-1]+d[i]);
			if(i+j<=n) f[i+j][0]=max(f[i+j][0], f[i][j]);
		}
	}
	printf("%d", f[n][0]);
	return 0;
}
