#include<bits/stdc++.h>
using namespace std;

const int N=2e6+5, M=1e4+5;

int son[N],nxt[N],h[M<<1],t,dis[M],q[M];
bool v[M];

void add(int x,int y){
    t++;
    son[t]=y;
    nxt[t]=h[x];
    h[x]=t;
}

int main(){
    int tt;
    cin>>tt;
    for(int p=1;p<=tt;p++)
    {
        t=0;
        memset(h,0,sizeof(h));
        memset(v,0,sizeof(v));
        int n,m,i,u,uu,w,x,head=0,tail=0,s=0,m1,m2;
        cin>>n>>m1>>m2;
        for (i=1;i<=n-1;i++)
        {
            scanf("%d%d",&u,&uu);
            add(u,uu);
            add(uu,u);
        }
        memset(q,0,sizeof(q));
        for (i=0;i<=n;i++)dis[i]=INT_MAX/3;
        tail++;
        q[tail]=0;
        v[0]=true;
        dis[0]=0;
        while (head!=tail)
        {
            head=(head%n)+1;
            x=q[head];
            v[x]=false;
            for (i=h[x];i;i=nxt[i])
             if (dis[x]+1<dis[son[i]])
             {
                  dis[son[i]]=dis[x]+1;
                  if (!v[son[i]])
                  {
                      tail=(tail%n)+1;
                      q[tail]=son[i];
                      v[son[i]]=true;
                 }
             }
        }
        long long s1=0,s2=0;
        for(int i=1;i<=m1;i++)
        {cin>>x;s1+=dis[x];}
        for(int i=1;i<=m2;i++)
        {cin>>x;s2+=dis[x];}
        if(s1<=s2)cout<<"Bob";else cout<<"Alice";
        cout<<endl;
    }
    return 0;
}
