#include"longesttrip.h"
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)

inline bool ask(int u, int v) { return are_connected({u}, {v}); }
inline void link(vector<int > &a, vector<int > b) { while (!b.empty()) a.pb(b.back()), b.pop_back(); }
inline vector<int > get(const vector<int > &a) { int u = a.front(), v = a.back(); vector<int > res = {u}; if (u ^ v) res.pb(v); return res; }

vector<int > longest_trip(int N, int D) {
    int n = N;
    vector<int > a, b;
    if (n & 1) {
        if (ask(1, 2)) a = {0}, b = {1, 2};
        else if (ask(0, 1)) a = {0, 1}, b = {2};
        else a = {0, 2}, b = {1};
    } else a = {0}, b = {1};
    for (int i = 2 + (n & 1); i < n; i += 2) {
        int u = i, v = i + 1;
        if (ask(u, v)) {
            if (ask(a.back(), u)) link(a, {v, u});
            else if (ask(a.back(), b.back())) link(a, b), b = {u, v};
            else link(b, {v, u});
        } else {
            if (ask(a.back(), v)) swap(u, v);
            a.pb(u);
            if (ask(b.back(), u)) link(a, b), b = {v};
            else b.pb(v);
        }
    }
    if (are_connected(get(a), get(b))) {
        if (are_connected({a.front()}, get(b))) reverse(a.begin(), a.end());
        if (ask(a.back(), b.front())) reverse(b.begin(), b.end());
        link(a, b);
        return a;
    }
    if (!are_connected(a, b)) return a.size()>b.size()? a: b;
    int l = 0, r = a.size() - 1, A = -1, B = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        vector<int > c;
        For (i, 0, mid) c.pb(a[i]);
        if (are_connected(b, c)) A = mid, r = mid - 1;
        else l = mid + 1;
    }
    l = 0, r = b.size() - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        vector<int > c;
        For (i, 0, mid) c.pb(b[i]);
        if (are_connected({a[A]}, c)) B = mid, r = mid - 1;
        else l = mid + 1;
    }
    vector<int > ans;
    For (i, A + 1, (int)a.size() - 1) ans.pb(a[i]);
    For (i, 0, A) ans.pb(a[i]);
    For (i, B, (int)b.size() - 1) ans.pb(b[i]);
    For (i, 0, B - 1) ans.pb(b[i]);
    return ans;
}
