#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5;

int n, pos;
string a, b, c;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    cin >> a >> b;
    if (a[0] ^ b[0]) {
        For (i, 1, n) putchar('1');
        return 0;
    }
    c = a; c[n - 1]++;
    rFor (i, n - 1, 0) if (c[i] - '0' > 1) c[i] -= 2, c[i - 1]++;
    if (!(b[n - 1] & 1) && a != b && b != c) b[n - 1]++;
    cout << b;

    return 0;
}
