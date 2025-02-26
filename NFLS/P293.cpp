#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 52;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m, a[N], b[N], c[N], ca[N], cb[N], Y[N], Z[N], vis[N];
ll ans, tot, C0, C1[N], C2[N][N], C3[N][N][N], C4[N][N][N][N];
vector<int > A[10], B;

inline void clear() { For (i, 1, 5) ca[a[i]]--, cb[b[i]]--; }
inline bool check() {
    For (i, 3, 5) if (a[i - 1] - a[i] != 1) return 0;
    if (a[1] == 12 && a[2] == 3) {
        For (i, 2, 5) swap(a[i], a[i - 1]), swap(b[i], b[i - 1]);
        return 1;
    }
    return a[1] - a[2] == 1;
}

void dfs(int k, int x) {
    if (k == 6) {
        For (i, 1, 5) a[i] = c[i] / 4, b[i] = c[i] % 4, ca[a[i]]++, cb[b[i]]++;
        For (i, 1, 2) if (ca[a[i]] == 4) {
            For (j, 0, i - 2) For (k, i - j, i - j + 3) swap(a[k], a[k - 1]), swap(b[k], b[k - 1]);
            int x = 0;
            For (j, 1, 5) x = x * 13 + a[j];
            For (j, 1, 5) x = x * 4 + b[j];
            A[2].pb(x);
            return clear();
        }
        For (i, 1, 3) if (ca[a[i]] == 3) {
            For (j, 0, i - 2) For (k, i - j, i - j + 2) swap(a[k], a[k - 1]), swap(b[k], b[k - 1]);
            int x = 0;
            For (j, 1, 5) x = x * 13 + a[j];
            For (j, 1, 5) x = x * 4 + b[j];
            A[ca[a[5]] == 2? 3: 6].pb(x);
            return clear();
        }
        For (i, 1, 4) if (ca[a[i]] == 2) {
            For (j, 0, i - 2) For (k, i - j, i - j + 1) swap(a[k], a[k - 1]), swap(b[k], b[k - 1]);
            if (ca[a[5]] == 2) For (k, 4, 5) swap(a[k], a[k - 1]), swap(b[k], b[k - 1]);
            int x = 0;
            For (j, 1, 5) x = x * 13 + a[j];
            For (j, 1, 5) x = x * 4 + b[j];
            A[ca[a[4]] == 2? 7: 8].pb(x);
            return clear();
        }
        bool f1 = cb[b[1]] == 5, f2 = check();
        int x = 0;
        For (j, 1, 5) x = x * 13 + a[j];
        For (j, 1, 5) x = x * 4 + b[j];
        A[f1? f2? 1: 4: f2? 5: 9].pb(x);
        return clear();
    }
    rFor (i, x - 1, 0) c[k] = i, dfs(k + 1, i);
}

inline void calc() {
    For (i, 1, n) if (!vis[Y[i]]) return;
    ans += C0;
    For (i, 1, 5) ans -= C1[a[i]];
    For (i, 1, 4) For (j, i + 1, 5) ans += C2[a[i]][a[j]];
    For (i, 1, 3) For (j, i + 1, 4) For (k, j + 1, 5) ans -= C3[a[i]][a[j]][a[k]];
    For (i, 1, 2) For (j, i + 1, 3) For (k, j + 1, 4) For (l, k + 1, 5) ans += C4[a[i]][a[j]][a[k]][a[l]];
}

inline void upd() {
    For (i, 1, n - 1) if (!vis[Z[i]]) return;
    C0++;
    For (i, 1, 5) C1[a[i]]++;
    For (i, 1, 4) For (j, i + 1, 5) C2[a[i]][a[j]]++;
    For (i, 1, 3) For (j, i + 1, 4) For (k, j + 1, 5) C3[a[i]][a[j]][a[k]]++;
    For (i, 1, 2) For (j, i + 1, 3) For (k, j + 1, 4) For (l, k + 1, 5) C4[a[i]][a[j]][a[k]][a[l]]++;
}

int main() {
    freopen("showhand.in", "r", stdin);
    freopen("showhand.out", "w", stdout);
    dfs(1, 52);
    rFor (i, 9, 1) {
        sort(A[i].begin(), A[i].end());
        for (auto &x : A[i]) B.pb(x);
    }
    m = B.size();
    io >> n;
    int x, y;
    For (i, 1, n) io >> x >> y, Y[i] = (x==1? 12: x - 2) * 4 + (4 - y);
    For (i, 1, n - 1) io >> x >> y, Z[i] = (x==1? 12: x - 2) * 4 + (4 - y);
    For (i, 0, m - 1) {
        int x = 1024, y = 1;
        For (j, 1, 5) a[j] = (B[i] / x % 13) * 4 + (B[i] / y % 4), x *= 13, y *= 4, vis[a[j]] = 1;
        sort(a + 1, a + 6);
        calc();
        upd();
        For (j, 1, 5) vis[a[j]] = 0;
    }
    tot = 1;
    For (i, 0, 10 - 2 * n) tot *= 53 - 2 * n - i;
    For (i, 1, 5 - n) tot /= i;
    For (i, 1, 6 - n) tot /= i;
    ll g = __gcd(ans, tot);
    ans /= g; tot /= g;
    printf("%lld/%lld", ans, tot);

    fclose(stdin); fclose(stdout);
    return 0;
}
