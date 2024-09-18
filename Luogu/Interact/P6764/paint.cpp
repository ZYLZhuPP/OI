#include "paint.h"
#include <vector>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e5 + 5;

bool ok[N];
int _[2][N], *f = _[0], *g = _[1];
vector<int > pos[N];

int minimumInstructions(int n, int m, int K, vector<int > C, vector<int > A, vector<vector<int > > B) {
    For (i, 0, m - 1) for (auto &x : B[i]) pos[x].pb(i);
    rFor (i, n - 1, 0) {
        swap(f, g);
        if (i + 2 < n) for (auto &j : pos[C[i + 2]]) f[j] = 0;
        for (auto &j : pos[C[i]]) {
            f[j] = g[(j + 1) % m] + 1;
            if (f[j] >= m) ok[i] = 1;
        }
    }
    int lst = 0, o = -1, ans = 0;
    For (i, 0, n - 1) {
        if (ok[i]) o = i;
        if (i == lst) {
            if (~o) ans++, lst = o + m, o = -1;
            else return -1;
        }
    }

    return ans;
}
