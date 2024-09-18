#include<bits/stdc++.h>
using namespace std;

const int N=1e3+5;

struct IO {
	static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x){
		for(f=1; !isdigit(c); c=gc()) if(!(c^'-')) f=-1;
		for(x=0; isdigit(c); c=gc()) x=x*10+(c^48); x*=f;
		return *this;
	}
	inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

struct P{
    int num,id;
    bool operator < (P X) const{
        return num<X.num;
    }
}p[N];

int n,a[N],b[N],ans[N],A,B;

int main(){
    io>>n;
    for(int i=1; i<=n; i++) io>>a[i];
    for(int i=1; i<=n; i++){
        io>>b[i];
        p[i]={min(a[i], b[i]), i};
    }
    sort(p+1, p+n+1);
    int l=0, r=n+1;
    for(int i=1; i<=n; i++){
        int num=p[i].num, id=p[i].id;
        if(num==a[id]) ans[++l]=id;
        else ans[--r]=id;
    }
    for(int i=1; i<=n; i++){
        A+=a[ans[i]];
        if(A>B) B=A;
        B+=b[ans[i]];
    }
    printf("%d\n", B);
    for(int i=1; i<n; i++) printf("%d ", ans[i]);
    printf("%d", ans[n]);
    return 0;
}
