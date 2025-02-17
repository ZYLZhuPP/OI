#include<bits/stdc++.h>
using namespace std;

const int N=1e2+5, M=1e6+5;;

int a[N],n,ans,b[M],siz;

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

int gcd(int x, int y){
    return y?gcd(y, x%y):x;
}

int main(){
    read(n);
    for(int i=1; i<=n; i++) read(a[i]);
    sort(a, a+n+1);
    for(int i=2; i<=n; i++) ans=gcd(ans,a[i]-a[i-1]);
    for(int i=2; i<=floor(sqrt(ans)); i++)if(ans%i==0){
        printf("%d ", i);
        if(i*i^ans) b[++siz]=ans/i;
    }
    for(int i=siz; i>=1; i--)printf("%d ", b[i]);
    printf("%d", ans);
    return 0;
}
