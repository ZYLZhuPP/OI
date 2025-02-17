#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define N 100005

struct a__
{
    int x;
    int y;
}snl[N],els[N];

int n,m,k,must[N];
int fa[N];
int vill;
int snl_num;
int els_num;
int must_num;

int find(int x)
{
    int grandson=x;
    while(fa[x]!=x)
        x=fa[x];

    return fa[grandson]=x;
}
void unionset(int x,int y)
{
    fa[find(y)]=find(x);
}

vector<int > ans;
void algo()
{
    for(int i=1;i<=snl_num;i++)
    {
        if(vill==1)break;
        if(find(snl[i].x)==find(snl[i].y))
            continue;
        else
        {
            unionset(snl[i].x,snl[i].y);
            vill--;
        }
    }
    if(vill!=1)
    {
        for(int i=1;i<=els_num;i++)
        {
            if(vill==1)break;
            if(find(els[i].x)==find(els[i].y))
                continue;
            else
            {
                must_num++;
                must[must_num]=i;
                
                unionset(els[i].x,els[i].y);
                vill--;
            }
        }

        if(vill!=1 || must_num>k)
        {
            printf("no solution\n");
            return;
        }
    }

    vill=n;

    for(int i=1;i<=n;i++)
        fa[i]=i;

    if(must_num)
    {
        for(int i=1;i<=must_num;i++)
        {
            unionset(els[must[i]].x,els[must[i]].y);
            vill--;
            k--;
            ans.pb(must[i]);

        }
    }

    for(int i=1;i<=els_num && k>0;i++)
        {
            if(vill==1)break;
            if(find(els[i].x)==find(els[i].y))
                continue;
            else
            {
                unionset(els[i].x,els[i].y);
                vill--;
                k--;
                ans.pb(i);
                //printf("%d %d 0\n",els[i].x,els[i].y);
            }
        }
    if(k!=0)
    {
        printf("no solution\n");
        return;
    }

    for(int i=1;i<=snl_num;i++)
    {
        if(vill==1)break;
        if(find(snl[i].x)==find(snl[i].y))
            continue;
        else
        {
            unionset(snl[i].x,snl[i].y);
            vill--;
            printf("%d %d 1\n",snl[i].x,snl[i].y);
        }
    }
    for (auto &e : ans) printf("%d %d 0\n",els[e].x,els[e].y);
}

int main()
{

    scanf("%d%d%d",&n,&m,&k);
    vill=n;

    for(int i=1;i<=n;i++)
        fa[i]=i; 

    int s,d,v;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&s,&d,&v);
        if(v==0)
        {
            els_num++;
            els[els_num].x=s;
            els[els_num].y=d;
        }
        else
        {
            snl_num++;
            snl[snl_num].x=s;
            snl[snl_num].y=d;
        }
    }

    if(els_num<k)
    {
        printf("no solution\n");
        return 0;
    }

    algo();

    return 0;
}
