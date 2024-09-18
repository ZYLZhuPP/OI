#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int N=2e5+5;
const ull P=19260817, Mo=16341163;

ull n,a[N],p[N],f1[N],f2[N],ans,an[N],ansiz;
int bkt[Mo];

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

void init(){
    p[0]=1;
    for(int i=1; i<=n; i++) p[i]=p[i-1]*P;
}

ull getf1(int l, int r){
    if(l>r) return 0;
    l--;
    return (f1[r]-f1[l]*p[r-l])%Mo;
}

ull getf2(int l, int r){
    if(l>r) return 0;
    r++;
    return (f2[l]-f2[r]*p[r-l])%Mo;
}

int ok(int k){
    int res=0;
    for(int i=1; i<=n/k; i++){
        ull p1=getf1(i*k-k+1,i*k);
        ull p2=getf2(i*k-k+1,i*k);
        if((bkt[p1]^k) && (bkt[p2]^k)) res++;
	bkt[p1]=bkt[p2]=k;
    }
    return res;
}

int main(){
    read(n);
    init();
    for(int i=1; i<=n; i++){
        read(a[i]);
        f1[i]=f1[i-1]*P+a[i];
    }
    for(int i=n; i>0; i--) f2[i]=f2[i+1]*P+a[i];
    ans=1;
    for(int i=1; i<=n/ans; i++){
        int ret=ok(i);
        if(ans==ret) an[++ansiz]=i;
        else if(ans<ret){
            an[ansiz=1]=i;
            ans=ret;
        }
    }
    printf("%llu %llu\n", ans, ansiz);
    for(int i=1; i<=ansiz; i++) printf("%llu ", an[i]);
    return 0;
}
