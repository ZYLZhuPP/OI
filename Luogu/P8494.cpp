#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2005;

int n, m, cnt, id[N];
bool b[N], B[N];
mt19937 rnd(1145141);

void move_inside(int i);
void move_outside(int i);
int press_button();

inline void in(int x) { move_inside(x); cnt++; b[x] = 1; }
inline void out(int x) { move_outside(x); cnt--; b[x] = 0; }
inline bool chk(int k) {
    For (i, 0, n - 1) id[i] = i, b[i] = 0;
    shuffle(id, id + n, rnd);
    For (i, 0, n - 1) {
        int x = id[i];
        if (B[x]) continue;
        in(x);
        if (press_button() > k) out(x);
        else if (cnt == m * k) return 1;
    }
    return cnt == m * k;
}

int min_cardinality(int N) {
    m = n = N;
    chk(1);
    m = cnt;
    if (m == 1) return n;
    For (i, 0, n - 1) B[i] = b[i];
    int l = 1, r = n / m, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (chk(mid)) {
            ans = mid, l = mid + 1;
            For (i, 0, n - 1) B[i] |= b[i];
        } else {
            r = cnt / m;
            For (i, 0, n - 1) if (b[i]) out(i); else B[i] = 1;
        }
    }
    return ans;
}
