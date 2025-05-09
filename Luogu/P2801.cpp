#include<bits/stdc++.h>
using namespace std;

#define space putchar(' ');
#define enter putchar('\n');
#define pb push_back
#define int long long
#define P 998244353
#define HP 1000000000000002097
#define N (int)1e6 + 5

int read()
{
    char ch = getchar();
    int x = 0, f = 1;
    while (ch > '9' || ch < '0')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x * f;
}
void print(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}

int n, m, len, cnt;
int a[N], loc[N];
struct Kuai
{
    int l, r, tg;
} k[N];
vector<int> v[N];
void sortt(int x)
{
    v[x].clear();
    for (int i = k[x].l; i <= k[x].r; i++)
        v[x].pb(a[i]);
    sort(v[x].begin(), v[x].end());
}
void modify(int l, int r, int val)
{
    int idx = loc[l], idy = loc[r];
    if (idx == idy)
    {
        for (int i = l; i <= r; i++)
            a[i] += val;
        sortt(idx);
        return;
    }
    for (int i = l; i <= k[idx].r; i++)
        a[i] += val;
    sortt(idx);
    for (int i = k[idy].l; i <= r; i++)
        a[i] += val;
    sortt(idy);
    for (int i = idx + 1; i < idy; i++)
        k[i].tg += val;
}
int query(int l, int r, int val)
{
    int idx = loc[l], idy = loc[r], ans = 0;
    if (idx == idy)
    {
        for (int i = l; i <= r; i++)
            ans += (a[i] + k[idx].tg >= val);
        return ans;
    }
    for (int i = l; i <= k[idx].r; i++)
        ans += (a[i] + k[idx].tg >= val);
    for (int i = k[idy].l; i <= r; i++)
        ans += (a[i] + k[idy].tg >= val);
    for (int i = idx + 1; i < idy; i++)
    {
        ans += v[i].end() - lower_bound(v[i].begin(), v[i].end(), val - k[i].tg);
    }
    return ans;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    len = sqrtl(n);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        loc[i] = ceil(1.0 * i / len);
        v[loc[i]].pb(a[i]);
        if ((i - 1) % len == 0)
            k[loc[i]].l = i;
        if (i % len == 0)
            k[loc[i]].r = i;
    }
    k[loc[n]].r = n;
    cnt = loc[n];
    for (int i = 1; i <= cnt; i++)
    {
        sort(v[i].begin(), v[i].end());
    }
    char op;
    int x, y, z;
    while (m--)
    {
        cin >> op >> x >> y >> z;
        if (x > y)
            swap(x, y);
        if (op == 'M')
            modify(x, y, z);
        else
            cout << query(x, y, z) << "\n";
    }
    return 0;
}
