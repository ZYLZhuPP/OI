#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 5;
char s[N];
int num[N][27],q1[N],q2[N];
ll f[N],sum[N];
ll a,b,c,d;

int getch(int x,int y) {
	int Max = 0;
	for (int i = 0; i < 26; i++) 
		Max = max(Max, num[y][i] - num[x][i]);
	return Max;
}

ll Y(int x) { return f[x] + a * sum[x] * sum[x]; }
ll X(int x) { return sum[x]; }
ll dY (int x, int y) { return Y(x) - Y(y); }
ll dX (int x, int y) { return X(x) - X(y); }
ll qz(int x) { return f[x] - c * sum[x]; }

int main() {
	int n, l, r;
	cin >> n >> a >> b >> c >> d >> l >> r;
	scanf("%s", s + 1);
	
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 26; j++)
		  num[i][j] = num[i-1][j];
		num[i][s[i] - 'a']++;
	}
	for (int i = 1; i <= n; i++){
		ll x;
		scanf("%lld", &x);
		sum[i] = sum[i - 1] + x;
	}
	
	memset(f, 31, sizeof(f));
	f[0] = 0;
	
	int h1 = 1, t1 = 1, h2 = 1, t2 = 0, ed=0;
	q1[h1] = 0;
	for (int i = 1; i <= n; i++) {
		while (ed < i && getch(ed, i) >= l) {
			while (h2 <= t2 && qz(ed) <= qz(q2[t2])) t2--;
			q2[++t2] = ed;
			ed++;
		}
		while (h2 <= t2 && getch(q2[h2], i) > r) h2++;
		if (h2 <= t2) f[i] = f[q2[h2]] + c * (sum[i] - sum[q2[h2]]) + d;
		
		while (h1 < t1 && dY(q1[h1 + 1], q1[h1]) <= 2ll * a * sum[i] * dX(q1[h1 + 1], q1[h1])) h1++;
		f[i] = min(f[i], f[q1[h1]] + a * (sum[i] - sum[q1[h1]]) * (sum[i] - sum[q1[h1]]) + b);
		while (h1 < t1 && dY(i, q1[t1]) * dX(q1[t1], q1[t1 - 1]) <= dY(q1[t1], q1[t1 - 1]) * dX(i, q1[t1])) t1--;
		q1[++t1] = i;
		
		printf("%lld\n", f[i]);
	}
	return 0;
}

