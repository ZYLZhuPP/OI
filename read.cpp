#include <bits/stdc++.h>
using namespace std;
const int N = 250005, M = 250000;
inline int read()
{
	int x = 0;
	char c;
	while (c = getchar())
		if (c >= '0' && c <= '9')
			break;
	while (c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	return x;
}
int n;
struct tree
{
	multiset<int> s[2];
	int f[2], g[2], ans;
} tr[N << 3];
inline void pushup(int k)
{
	tr[k].ans = min(tr[k << 1].ans, min(tr[k << 1 | 1].ans, min(tr[k << 1].f[0] + tr[k << 1 | 1].g[1], tr[k << 1].f[1] + tr[k << 1 | 1].g[0])));
	for (int i = 0; i < 2; ++i)
		tr[k].f[i] = min(tr[k << 1].f[i], tr[k << 1 | 1].f[i]), tr[k].g[i] = min(tr[k << 1].g[i], tr[k << 1 | 1].g[i]);
}
inline void build(int k, int l, int r)
{
	if (l == r)
	{
		tr[k].ans = 1e9;
		for (int j = 0; j < 2; ++j)
			tr[k].s[j].insert(1e9), tr[k].f[j] = tr[k].g[j] = 1e9;
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid), build(k << 1 | 1, mid + 1, r);
	pushup(k);
}
inline void ins(int o, int k, int l, int r, int x, int y)
{
	if (l == r)
	{
		tr[k].s[o].insert(y);
		tr[k].f[o] = *tr[k].s[o].begin();
		tr[k].g[o] = tr[k].f[o] + x;
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid)
		ins(o, k << 1, l, mid, x, y);
	else
		ins(o, k << 1 | 1, mid + 1, r, x, y);
	pushup(k);
}
inline void del(int o, int k, int l, int r, int x, int y)
{
	if (l == r)
	{
		auto it = tr[k].s[o].find(y);
		tr[k].s[o].erase(it);
		tr[k].f[o] = *tr[k].s[o].begin();
		tr[k].g[o] = tr[k].f[o] + x;
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid)
		del(o, k << 1, l, mid, x, y);
	else
		del(o, k << 1 | 1, mid + 1, r, x, y);
	pushup(k);
}
int main()
{
	freopen("money.in", "r", stdin);
	freopen("money.out", "w", stdout);
	n = read();
	int op, k, x, y;
	bool cm = 1;
	build(1, -M, M);
	for (int i = 1; i <= n; ++i)
	{
		op = read(), k = read() - 1, x = read(), y = read();
		if (op == 1)
		{
			if (k == 0)
				ins(0, 1, -M, M, x - y, y);
			else
				ins(1, 1, -M, M, y - x, x);
		}
		else
		{
			if (k == 0)
				del(0, 1, -M, M, x - y, y);
			else
				del(1, 1, -M, M, y - x, x);
		}
		if (tr[1].ans == 1e9)
			puts("-1");
		else
			printf("%d\n", tr[1].ans);
	}
}