#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

int n, fa[N], s[N], d[N];

//code n as root
void encode(int n) {
    For (i, 1, n - 2) d[fa[i]]++;
    for (int i = 1, p = 1; i <= n - 2; ++i, ++p) {
        while (p <= n && d[p]) p++;
        s[i] = fa[p];
        while (i <= n - 2 && !--d[s[i]] && s[i] < p)
            s[i + 1] = fa[s[i]], i++;
    }
}

void decode(int n) {
    For (i, 1, n - 2) d[s[i]]++;
    s[n - 1] = n;
    for (int i = 1, p = 1; i <= n - 2; ++i, ++p) {
        while (p <= n && d[p]) p++;
        fa[p] = s[i];
        while (i <= n - 2 && !--d[s[i]] && s[i] < p)
            fa[s[i]] = s[i + 1], i++;
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    For (i, 1, n - 1) cin >> fa[i];
    encode(n);
    For (i, 1, n - 2) cout << s[i] << " ";
    cout << endl;
    decode(n);
    For (i, 1, n - 1) cout << fa[i] << " ";

    return 0;
}
