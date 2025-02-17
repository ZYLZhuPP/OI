#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e6+5;

ll n,x,y,a[N<<1],s[N<<1];
ll h,t,q[N<<1];
bool ok[N];

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
    read(n);
    for(int i=1; i<=n; i++){
        read(x); read(y);
        a[i]=a[i+n]=x-y;
    }
    for(int i=1; i<=2*n; i++) s[i]=s[i-1]+a[i];
    
    h=1; t=0;
    for(int i=1; i<=2*n; i++){
        if(h<=t && q[h]<i-n+1) h++;
        while(h<=t && s[q[t]-1]<=s[i-1]) t--;
        q[++t]=i;
        if(i>n) ok[i-n]=(s[i]-s[q[h]-1])>=0;
    }
    
    h=1; t=0;
    for(int i=2*n; i>=1; i--){
        if(h<=t && q[h]>i+n-1) h++;
        while(h<=t && s[q[t]]>=s[i]) t--;
        q[++t]=i;
        if(i<=n && (s[q[h]]-s[i-1])>=0) ok[i]=1;
    }

    for(int i=1; i<=n; i++) printf(ok[i]?"TAK":"NIE"), printf("\n");
    return 0;
}
