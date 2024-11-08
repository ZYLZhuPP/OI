#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 255;

int n, a[N], id[N], vis[N];

int main() {
    cin >> n;
    For (i, 1, n) {
        cout << "? " << i << " ";
        For (j, 1, n) cout << (j != i);
        cout << endl;
        cin >> a[id[i] = i];
    }
    sort(id + 1, id + n + 1, [&](const int &x, const int &y) { return a[x] < a[y]; });
    int s = 0;
    rFor (i, n, 1) {
        s += a[id[i]]; vis[id[i]] = 1;
        if (s - (n - i + 1) * (n - i) / 2 == (i - 1) * (n - i + 1)) break;
    }
    cout << "! ";
    For (i, 1, n) cout << vis[i];
    cout << endl;

    return 0;
}
