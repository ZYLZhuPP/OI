#include<bits/stdc++.h>
using namespace std;

const int N=17;
const int N_=4e4+5;
const int INF=INT_MAX;

int m,x,y,z,p[N];
int s[N_];
double f[N_],zhe,kil[N][N_],ans; 

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

int lowbit(int x){return x&-x;}

int main(){
    while(read(m) && m){
        ans=INF;
        for(int i=0; i<(1<<m); i++) f[i]=INF;
        memset(s, 0, sizeof(s));
        for(int i=0; i<m; i++)
        for(int j=0; j<(1<<m); j++) kil[i][j]=1;
        for(int i=0; i<m; i++){
            read(p[i]); read(s[1<<i]);
            read(z);
            while(z--){
                read(x); read(y);
                x--; zhe=(100-y)/100.0;
                kil[x][1<<i]*=zhe;
            } 
            f[1<<i]=p[i];
        }
        for(int i=1; i<(1<<m); i++)
            s[i]=s[i-lowbit(i)]+s[lowbit(i)];
        for(int i=0; i<m; i++)
        for(int j=1; j<(1<<m); j++)
            kil[i][j]=kil[i][j-lowbit(j)]*kil[i][lowbit(j)];
        for(int i=1; i<(1<<m); i++){
            for(int j=0; j<m; j++)if(!(i&(1<<j))){
                int sta=i|(1<<j);
                if(f[sta]>f[i]+kil[j][i]*(double)p[j]) f[sta]=f[i]+kil[j][i]*(double)p[j];
            }
            ans=min(ans, f[i]/(double)s[i]);
        }
        printf("%.4lf\n", ans);
    }
    return 0;
} 
