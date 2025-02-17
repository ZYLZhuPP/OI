#include<bits/stdc++.h>
using namespace std;

const int N=2055;

char ch;
int n,m,x,y,X,Y;
int bit[N][N],Bit[3][N][N],ad;

#define gc() getchar()

template<typename T>
inline void read(T *x)
{
    (*x)=0;
    int f=1;
    char ch=gc();
    for(;!isdigit(ch);ch=gc())
        if(!(ch^'-'))
            f=-1;
    for(;isdigit(ch);ch=gc())
        (*x)=((*x)<<3)+((*x)<<1)+(ch^48);
    (*x)*=f;
}

template<typename T>
inline void sread(int k,T *o,...)
{
    read(o);
    va_list in;
    va_start(in,o);
    while(--k){
        T* x=va_arg(in,T*);
        read(x);
    }
}

#define lowbit(x) (x&-x)

inline void norm_update(int bit[][N],int x,int y,int ad)
{
    for(int i=x;i<=n;i+=lowbit(i))
    for(int j=y;j<=m;j+=lowbit(j))
        bit[i][j]+=ad;
}

inline void inr_update_(int x,int y,int ad)
{
    for(int i=x;i<=n;i+=lowbit(i))
    for(int j=y;j<=m;j+=lowbit(j)){
        bit[i][j]+=ad;
        Bit[0][i][j]+=ad*x;
        Bit[1][i][j]+=ad*y;
        Bit[2][i][j]+=ad*x*y;
    }
}

inline void inr_update(int x,int y,int X,int Y,int ad)
{
    inr_update_(x,y,ad);
    X++;Y++;
    inr_update_(x,Y,-ad);
    inr_update_(X,y,-ad); 
    inr_update_(X,Y,ad);
}

inline void pt_update(int x,int y,int ad)
{
    inr_update(x,y,x,y,ad);
}

inline int getnum(int x,int y)
{
    int num=0;
    for(int i=x;i;i-=lowbit(i))
    for(int j=y;j;j-=lowbit(j))
        num+=bit[i][j];
    return num;
}

inline int getpresum(int x,int y)
{
    int sum=(x+1)*(y+1)*getnum(x,y);
    for(int i=x;i;i-=lowbit(i))
    for(int j=y;j;j-=lowbit(j)){
        sum-=(y+1)*Bit[0][i][j];
        sum-=(x+1)*Bit[1][i][j];
        sum+=Bit[2][i][j];
    }
    return sum;
}

inline int getsum(int x,int y,int X,int Y)
{
    x--;y--;
    return getpresum(X,Y)-getpresum(X,y)-getpresum(x,Y)+getpresum(x,y);
}

int main()
{
    scanf("%c%d%d",&ch,&n,&m);
    while(ch^EOF){
        if(!(ch^'L')){
            read(&x);read(&y);read(&X);read(&Y);read(&ad);
            inr_update(x,y,X,Y,ad);
        }else if(!(ch^'k')){
            read(&x);read(&y);read(&X);read(&Y);
            printf("%d\n",getsum(x,y,X,Y));
        }
        ch=gc();
    }
    return 0;
} 
