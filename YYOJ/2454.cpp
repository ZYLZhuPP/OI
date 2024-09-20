#include<bits/stdc++.h> 
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef long double Lf;
const Lf eps = 1e-8;

struct Vec {
    Lf x, y;
    Lf len() { return sqrtl(x * x + y * y); }
    Vec operator + (Vec _) { return {x + _.x, y + _.y}; }
    Vec operator += (Vec _) {x += _.x;y += _.y;return * this; }
    Vec operator - (Vec _) { return {x - _.x, y - _.y}; }
    Vec operator -= (Vec _) {x -= _.x;y -= _.y;return * this; }
    Vec operator * (Lf _) { return {x * _, y * _}; }
} s;
bool operator < (Vec a, Vec b) { return (a - s) .len() < (b - s) .len(); }
bool operator == (Vec a, Vec b) { return abs(a.x - b.x) < eps && abs(a.y - b.y) < eps; }
Lf Dot(Vec a, Vec b) { return a.x *  b.x + a.y * b.y; }
Lf Cro(Vec a, Vec b) { return a.x * b.y - a.y * b.x; }

struct Seg { Vec s, t; };
int dcmp(Lf x) { return (x < -eps)? -1: ((x > eps)? 1: 0); }
bool Onseg(Vec a, Seg b) { return (dcmp(Cro(a - b.s, b.t - b.s) == 0)) && (dcmp(Dot(a - b.s, a - b.t)) <= 0); }
bool onseg(Vec a, Seg b, bool heng) {
    if (b.s.x > b.t.x) swap(b.s.x, b.t.x);
    if (b.s.y > b.t.y) swap(b.s.y, b.t.y);
    if (heng) return abs(b.s.y - a.y) < eps && b.s.x - a.x < -eps && a.x - b.t.x < -eps;
    return abs(b.s.x - a.x) < eps && b.s.y - a.y < -eps && a.y - b.t.y < -eps;
}
bool isinter(Seg a, Seg b) {
    Lf c1 = Cro(a.t - a.s, b.s - a.s), c2 = Cro(a.t - a.s, b.t - a.s);
    Lf d1 = Cro(b.t - b.s, a.s - b.s), d2 = Cro(b.t - b.s, a.t - b.s);
    return (dcmp(c1) * dcmp(c2) <= 0 && dcmp(d1) * dcmp(d2) <= 0 && (dcmp(c1) * dcmp(c2) == 0 && dcmp(d1) * dcmp(d2) == 0) == 0);
}
Vec inter(Seg a,  Seg b) {
    if (!isinter(a, b)) return {1e14, 1e14};
    Vec x = b.s - a.s, y = b.t - a.s, xx = b.t - a.t, yy = b.s - a.t;
    Lf w1 = Cro(x, y), w2 = Cro(xx, yy);
    return a.s + (a.t - a.s) * (w1/(w1 + w2));
}
bool OnD(Seg a, Seg b) {  
    Vec o = inter(a, b);if (o.x == 1e14 && o.y == 1e14) return 0;
    if (a.s == o || a.t == o || b.s == o || b.t == o) return 0;
    return 1;
}
Vec Inter(Seg a, Seg b) {
    if (OnD(a, b)) return inter(a, b);
    return {1e14, 1e14};
}

struct Rec { Seg a, b, c, d; } p[55];
Lf vx, vy;
Lf acc(Lf v, Lf x, Lf y) { return (x > -eps? min(v + x, y) : max(v + x, y)); }
int style, at, lei, m; bool near;

inline int check() {
    bool a = 0, b = 0, c = 0, d = 0;at = lei = 0;
    bool aa = 0, bb = 0, cc = 0, dd = 0;
    For (i, 1, m) {
        if (onseg(s, p[i].a, 1)) a = 1, at = i, lei = 1;
        if (onseg(s, p[i].b, 0)) b = 1, at = i, lei = 2;
        if (onseg(s, p[i].c, 1)) c = 1, at = i, lei = 3;
        if (onseg(s, p[i].d, 0)) d = 1, at = i, lei = 4;
        if (p[i].a.s == s) aa = 1;
        if (p[i].b.s == s) bb = 1;
        if (p[i].c.s == s) cc = 1;
        if (p[i].d.s == s) dd = 1;
    }
    if (aa | bb) {style = 3;lei = 1;return style; }
    if (cc | dd) {style = 2;near = cc;lei = (cc? 2: 4);return style; }
    if (!a && !b && !d) style = 1;
    if (b || d) style = 2, near = b;
    if (a) style = 3;
    return style;
}

inline bool in(Vec s) {
    For (i, 1, m) if (p[i].a.s.y - s.y < -eps && s.y - p[i].c.s.y < -eps && p[i].d.s.x - s.x < -eps && s.x - p[i].b.s.x < -eps) return 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> m;
    For (i, 1, m) {
        Lf a, b, c, d; cin >> a >> b >> c >> d;
        Vec A = {a, b}, B = {c, b}, C = {c, d}, D = {a, d};
        p[i] = { {A, B}, {B, C}, {C, D}, {D, A}};
    }
    cin >> s.x >> s.y;
	check();
    int T; cin >> T;
    int cnt = 2, jcnt = 0, run = 0;bool jie = 0, jump = 0;
    bool DW, DS, DA, DD;
    while (T--) {
        string o;cin >> o;
        bool W = 0, S = 0, A = 0, D = 0, L = 0, K = 0;
		for(auto i : o) W |= (i == 'W'), S |= (i = 'S'), A |= (i == 'A'), D |= (i == 'D'), L |= (i == 'L'), K |= (i == 'K');
        if (style == 3) cnt = 2;
        if (jie) {
            if (DW) vy = -160;
            if (DS) vy = 160;
            if (DA) vx = -160;
            if (DD) vx = 160;
            if (DW & DA) vx = -113, vy = -113;
            if (DA & DS) vx = -113, vy = 113;
            if (DS & DD) vx = 113, vy = 113;
            if (DD & DW) vx = 113, vy = -113;
            jie = 0;
        }
        if (run) {
            run--; if (!run) jie = 1;
        }else if (L && cnt) {
            jump = jcnt = 0;
            run = 9; cnt--;
            vx = 0; vy = 0;
            DW = W, DS = S, DA = A, DD = D;
            if (W) vy =  - 240;
            if (S) vy = 240;
            if (A) vx =  - 240;
            if (D) vx = 240;
            if (W & A) vx = -169, vy = -169;
            if (A & S) vx = -169, vy = 169;
            if (S & D) vx = 169, vy = 169;
            if (D & W) vx = 169, vy = -169;
        }else {
            if (A | D) {
                int k = (A? -1: 1);
                if (k * vx > 0 && abs(vx) > 90) {
                    vx = acc(vx, (style == 3?  - 6.7 * k:  - 4.3 * k), 90 * k);
                }else {
                    vx = acc(vx, (style == 3? 45 * k: 30 * k), 90 * k);
                }
            }else {
                int k = (vx > 0? 1: -1);
                vx = acc(vx, (style == 3? -16.7 * k: -10.8 * k), 0);
            }
            if (K) {
                Lf tmp = vy; vy = -105; jump = 1;
                if (style == 3) jcnt = 1;
                if (style == 2) {
                    if (near) vx += 130;
                    else vx += -130;
                    jcnt = 0;
                }
                if (style == 1) {
                    if (jcnt) {
                        if (jcnt == 12) jcnt = 0, jump = 0, vy = tmp;
                        else jcnt++;
                    }else jump = jcnt = 0, vy = tmp;
                }
            }else jump = jcnt = 0;
            if (!jump) {
                if (style == 1) vy = acc(vy, 15, S? 240: 160);
                if (style == 2) vy = acc(vy, 1.9, S? 240: 160);
            }
        }
        if (at && in((Vec) {s.x + vx * 1e-7, s.y + vy * 1e-7})) {
            if (lei == 1) vy = 0;if (lei == 2) vx = 0;
            if (lei == 3) vy = 0;if (lei == 4) vx = 0;
        }else {
            Seg u = {s, {s.x + vx, s.y + vy}};Vec h = {1e14, 1e14};
            For (i, 1, m) {
                h = min(Inter(u, p[i].a), h);
                h = min(Inter(u, p[i].b), h);
                h = min(Inter(u, p[i].c), h);
                h = min(Inter(u, p[i].d), h);
            }
            if (h.x == 1e14 && h.y == 1e14) {
                s.x += vx; s.y += vy;
            }else {
                Vec tmp = s;
                s = h; check();
                if (lei == 1) vy = 0; if (lei == 2) vx = 0;
                if (lei == 3) vy = 0; if (lei == 4) vx = 0;
            }
        }
        check();
        printf("%.6Lf %.6Lf\n", s.x, s.y);
    }
    return 0;
}