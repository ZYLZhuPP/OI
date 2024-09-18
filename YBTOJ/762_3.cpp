#include<bits/stdc++.h>
using namespace std;

const int N = 1005;
inline void cmax(int &x, const int &y) { x = y>x? y: x; }

int n, m, T;

namespace Seg_Seg {
    struct Seg {
        int o[N << 1], t[N << 1];
        Seg() { memset(o, 0, sizeof o); memset(t, 0, sizeof t); }
        void upd(const int &x, const int &y, const int &v) {
            int l = x + m - 1, r = y + m + 1, L = 0, R = 0;
            for (; l ^ r ^ 1; l >>= 1, r >>= 1) {
                if (L) cmax(o[l], v);
                if (R) cmax(o[r], v);
                if (~l & 1) cmax(o[l ^ 1], v), cmax(t[l ^ 1], v), L = 1;
                if (r & 1) cmax(o[r ^ 1], v), cmax(t[r ^ 1], v), R = 1;
            }
            for (; l; l >>= 1, r >>= 1) {
                if (L) cmax(o[l], v);
                if (R) cmax(o[r], v);
            }
        }
        int query(const int &x, const int &y) {
            int res = 0, l = x + m - 1, r = y + m + 1, L = 0, R = 0;
            for (; l ^ r ^ 1; l >>= 1, r >>= 1) {
                if (L) cmax(res, t[l]);
                if (R) cmax(res, t[r]);
                if (~l & 1) cmax(res, o[l ^ 1]), L = 1;
                if (r & 1) cmax(res, o[r ^ 1]), R = 1;
            }
            for (; l; l >>= 1, r >>= 1) {
                if (L) cmax(res, t[l]);
                if (R) cmax(res, t[r]);
            }
            return res;
        }
    } o[N << 1], t[N << 1];
    inline void upd(const int &x, const int &X, const int &y, const int &Y, const int &v) {
        int l = x + n - 1, r = X + n + 1, L = 0, R = 0;
        for (; l ^ r ^ 1; l >>= 1, r >>= 1) {
            if (L) o[l].upd(y, Y, v);
            if (R) o[r].upd(y, Y, v);
            if (~l & 1) o[l ^ 1].upd(y, Y, v), t[l ^ 1].upd(y, Y, v), L = 1;
            if (r & 1) o[r ^ 1].upd(y, Y, v), t[r ^ 1].upd(y, Y, v), R = 1;
        }
        for (; l; l >>= 1, r >>= 1) {
            if (L) o[l].upd(y, Y, v);
            if (R) o[r].upd(y, Y, v);
        }
    }
    inline int query(const int &x, const int &X, const int &y, const int &Y) {
        int res = 0, l = x + n - 1, r = X + n + 1, L = 0, R = 0;
        for (; l ^ r ^ 1; l >>= 1, r >>= 1) {
            if (L) cmax(res, t[l].query(y, Y));
            if (R) cmax(res, t[r].query(y, Y));
            if (~l & 1) cmax(res, o[l ^ 1].query(y, Y)), L = 1;
            if (r & 1) cmax(res, o[r ^ 1].query(y, Y)), R = 1;
        }
        for (; l; l >>= 1, r >>= 1) { 
            if (L) cmax(res, t[l].query(y, Y));
            if (R) cmax(res, t[r].query(y, Y));
        }
        return res;
    }
}
using namespace Seg_Seg;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m >> T;
    while (T--) {
        int d, s, w, x, y;
        cin >> d >> s >> w >> x >> y; x++; y++;
        upd(x, x + d - 1, y, y + s - 1, w + query(x, x + d - 1, y, y + s - 1));
    }
    printf("%d\n", query(1, n, 1, m));

    return 0;
}
