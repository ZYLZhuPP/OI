#include <bits/stdc++.h>
using namespace std;

const int N = 6e3 + 5;

int n, u, v, k, f[2][N], val[N], root;
int head[N], nxt[N], to[N], t;
bool pd = 1, vis[N];

#define gc() getchar()

template <class T>
inline void read(T &x)
{
	x = 0;
	int f = 1;
	char ch = gc();
	for (; !isdigit(ch); ch = gc())
		if (!(ch ^ '-'))
			f = -1;
	for (; isdigit(ch); ch = gc())
		x = (x << 3) + (x << 1) + (ch ^ 48);
	x *= f;
}

void add(int u, int v)
{
	nxt[++t] = head[u];
	to[t] = v;
	head[u] = t;
}

void dfs(int u)
{
	if (vis[u])
		return;
	vis[u] = 1;
	f[1][u] = val[u];
	int v;
	for (int i = head[u]; v = to[i], i; i = nxt[i])
	{
		dfs(v);
		f[1][u] += f[0][v];
		f[0][u] += max(f[0][v], f[1][v]);
	}
}

int main()
{
	read(n);
	for (int i = 1; i <= n; i++)
		read(val[i]);
	for (int i = 1; i <= n - 1; ++i)
	{
		read(u);
		read(v);
		add(v, u);
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i])
		{
			dfs(i);
			root = i;
		}
	printf("%d", max(f[0][root], f[1][root]));
	return 0;
}
