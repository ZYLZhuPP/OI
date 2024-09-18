#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int N=5e5+5;
const ull P=31;

int l,len,x,y,T,ans;
ull p[N],f[N];
char st[N];

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

vector<int> pri;
int mip[N];
bool vis[N];

void init(){
	p[0]=1;
	for(int i=1; i<=l; i++) p[i]=p[i-1]*P;
    for(int i=2; i<=l; i++){
        if(!vis[i]){
            pri.push_back(i);
            mip[i]=i;
        }
        for(int j=0; j<pri.size() && pri[j]*i<=l; j++){
            mip[pri[j]*i]=pri[j];
            vis[pri[j]*i]=1;
            if(pri[j]>mip[i]) break;
        }
    }
}

ull getf(int l, int r){
	if(l>r) return 0;
	l--;
	return f[r]-f[l]*p[r-l];
}

bool ok(int k){
    return !(getf(x,y-k)^getf(x+k,y));
}

int main(){
	read(l);
	init();
	scanf("%s", st+1);
	for(int i=1; i<=l; i++) f[i]=f[i-1]*P+st[i];
	read(T);
	while(T--){
		read(x); read(y);
		ans=len=y-x+1;
        while(len>1){
            if(ok(ans/mip[len])) ans/=mip[len];
            len/=mip[len];
        }
        printf("%d\n", ans);
	}
	return 0;
} 
