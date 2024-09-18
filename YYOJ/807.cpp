#include<bits/stdc++.h>
using namespace std;

int T,a0,a1,b0,b1,ans;

int gcd(int a,int b){
    return b^0?gcd(b,a%b):a;
}

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
    read(T);
    while(T--){
        ans=0;
        read(a0); read(a1); read(b0); read(b1);
        int p=a0/a1, q=b1/b0;
        for(int x=1;x*x<=b1;x++)if(b1%x==0){
            if(x%a1==0 && gcd(x/a1,p)==1 && gcd(q,b1/x)==1) ans++;
            int y=b1/x;
            if(x==y) continue; 
            if(y%a1==0 && gcd(y/a1,p)==1 && gcd(q,b1/y)==1) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
