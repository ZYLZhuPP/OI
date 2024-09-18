#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef unsigned int uint;
const int N = 2e7 + 5;

int n, vis[N];
uint seed, a[N], ans;

inline uint getnext(){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

int main() {
    cin >> n >> seed;
    For (i, 1, n) a[i] = getnext();
    For (i, 2, n) if (!vis[i])
        For (j, 1, n / i) vis[j * i] = 1, a[j * i] += a[j];
    For (i, 1, n) ans ^= a[i];
    printf("%u", ans);

    return 0;
}
