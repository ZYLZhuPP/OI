#include<bits/stdc++.h>
using namespace std;

const int N=14;
const int Mo=1e8;

int n,m,x,msta[N],ok[1<<N],f[N][1<<N],ans;
int stasiz,STA;

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
    read(n); read(m);
    for(int i=1; i<=n; i++){
        for(int j=0; j<m; j++){
            read(x);
            msta[i]=(msta[i]<<1)+x;
        }
    }
    STA=1<<m;
    for(int sta=0; sta<STA; sta++)if(!(sta&(sta>>1))) ok[++stasiz]=sta;
    f[0][0]=1;
    for(int i=1; i<=n; i++){
        for(int l=1; l<=stasiz; l++)if((ok[l]|msta[i-1])==msta[i-1]){
            for(int r=1; r<=stasiz; r++)if(!(ok[l]&ok[r]) && ((ok[r]|msta[i])==msta[i]))
                (f[i][ok[r]]+=f[i-1][ok[l]])%=Mo;
        }
    }
    for(int i=1; i<=stasiz; i++) (ans+=f[n][ok[i]])%=Mo;
    printf("%d", ans);
    return 0;
}
