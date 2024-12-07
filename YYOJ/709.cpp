#include<bits/stdc++.h>
using namespace std;

const int N=1e3+5;

int n,m,p,a[N][N],b[N],s[N][N],f[N][N],ff[N],q_[N][N],h_[N],t_[N],k[N][N];

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
    read(n); read(m); read(p); 
    memset(f, 128, sizeof(f)); 
    memset(ff, 128, sizeof(ff)); 
    for(int i=0; i<n; i++){ 
        int x=i;
		for(int j=1; j<=m; j++,x=(x+n-1)%n) read(a[x][j]), k[x][j]=i;
	}
	for(int i=0; i<n; i++) read(b[i]);
	for(int i=0; i<n; i++)
    	for(int j=1; j<=m; j++) s[i][j]=s[i][j-1]+a[i][j];
    ff[0]=0;
    for(int i=0; i<n; i++) f[i][0]=0;
	for(int i=1; i<=m; i++)
    	for(int j=0; j<n; j++){
            int *q=q_[j],&h=h_[j],&t=t_[j];
	    	if(h<=t && q[h]<i-p) h++;
	    	while(h<=t && (ff[q[h]]-s[j][q[h]]-b[k[j][q[h]+1]])<=(ff[i-1]-s[j][i-1]-b[k[j][i]])) t--;
             q[++t]=i-1;
             f[j][i]=ff[q[h]]+s[j][i]-s[j][q[h]]-b[k[j][q[h]+1]];
             ff[i]=max(ff[i], f[j][i]);
        }
    printf("%d", ff[m]);
	return 0;
}
