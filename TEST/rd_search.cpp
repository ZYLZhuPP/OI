#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;
const int INF=INT_MAX/3;

int n,a[N],ans;

int f(int x){return a[x];}

int rd_search(int l, int r, int d){
    int res=INF;
    while(r-l>d){
        int mid=(l+r)>>1;
        int lm=mid-d, rm=mid+d;
        int ls=f(lm), rs=f(rm);
        res=min(ls, rs);
        if(ls<rs) r=mid; else l=mid;
    }
    return res;
}

int main(){
    cin>>n;
    for(int i=1; i<=n; i++) a[i]=abs(i-(n/2))-2;
    ans=rd_search(1, n, 1);
    cout<<ans;
    return 0;
}
