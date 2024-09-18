#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=205;

ll a[N],s[N],f[N][N],n,p;

#define gc() getchar()

template<class T>
inline bool read(T &x){
	x=0;
	int f=1;
	char ch=gc();
	for(; !isdigit(ch); ch=gc())
		if(!(ch^'-')) f=-1;
		else if(!(ch^EOF)) return 0;
	for(; isdigit(ch); ch=gc())
		x=(x<<3)+(x<<1)+(ch^48);
	x*=f;
	return 1;
}

int main(){
	memset(f, 127, sizeof(f));
	read(n); read(p);
	for(int i=1; i<=n; i++){
		read(a[i]);
		f[i][i]=0;
		s[i]=s[i-1]+a[i];
	}
	for(int i=2; i<=n; i++){
		for(int j=1; j+i-1<=n; j++){
			int l=j,r=i+j-1;
			for(int k=l; k<r; k++)
				f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]+s[r]-s[l-1]-p*(i-1));
		}
	}
	printf("%lld", f[1][n]);
	return 0;
}
