#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=5e5+5;

ll n,len[N<<1],to[255],mid=1,mar=1,ans;
string st;
char p_st[N];

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
    to['0']='1';
    to['1']='0';
    to['#']='#';
    to['$']='$';
    to['%']='%';
}

int main(){
    init();
    read(n);
    scanf("%s", p_st);
    st="$";
    for(int i=0; i<n; i++){
        st+='#';
        st+=p_st[i];
    }
    st+="#%";
    n=st.size();
    for(int i=1; i<n; i+=2){
        len[i]=(i<mar)?min(mar-i, len[(mid<<1)-i]):1;
        while(to[st[i+len[i]]]==st[i-len[i]]) len[i]++;
        if(len[i]+i>mar) mar=i+len[i], mid=i;
        if(st[i]=='#') ans+=len[i]>>1;
    }
    printf("%lld", ans);
    return 0;
}
