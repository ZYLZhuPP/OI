// #include <bits/stdc++.h>
// #define dbg(x) std::cout << #x, printf(" = %.1lf\n", x)
// // FILE *FileV = fopen("V.out", "w");
// // FILE *FileP = fopen("P.out", "w");
// // FILE *FileX = fopen("X.out", "w");
// using Lf = long double;
// const Lf Eps = 1e-8l;
// const int N = 1e5 + 5, M = 55;
// int m, T, TTT;
// struct Comp {
// 	Lf x, y;
// 	Comp() {}
// 	Comp(Lf _x, Lf _y): x(_x), y(_y) {}
// 	Comp& operator+=(const Comp& c) { x += c.x, y += c.y; return *this; }
// 	Comp operator+(const Comp& c) const { return Comp(*this) += c; }
// 	Comp& operator-=(const Comp& c) { x -= c.x, y -= c.y; return *this; }
// 	Comp operator-(const Comp& c) const { return Comp(*this) -= c; }
// 	Comp operator*(const Comp& c) const { return Comp(x * c.x - y * c.y, x * c.y + y * c.x); }
// 	Comp operator*(const Lf p) const { return Comp(x * p, y * p); }
// 	Comp operator/(const Lf p) const { return Comp(x / p, y / p); }
// 	Lf operator&(const Comp& c) const { return x * c.x + y * c.y; }
// 	Lf operator|(const Comp& c) const { return x * c.y - y * c.x; }
// 	Lf abs() const { return sqrtl(x * x + y * y); }
// 	Comp Norm() const { return *this / abs(); }
// 	bool operator==(const Comp& c) const {
// 		return std::abs(x - c.x) < Eps && std::abs(y - c.y) < Eps;
// 	}
// } ver[4] = {
// 	Comp(0, -1), Comp(1, 0), Comp(0, 1), Comp(-1, 0)
// };
// Lf A1[3], A2[3];
// // A1 为加速的速度，A2 为减速的速度
// struct Line {
// 	Comp p, q;
// 	Comp v() const { return q - p; }
// };
// bool Online(const Line& l, const Comp& c) {
// 	return std::abs((c - l.p) | l.v().Norm()) < Eps;
// }
// bool NotOutline(const Line& l, const Comp& c) {
// 	// if (TTT == 19240) {
// 	// 	fprintf(FileP, "Online = %d\n", Online(l, c));
// 	// 	// fprintf(FileP, "%Lf\n", (c - l.p) & (c - l.q));
// 	// }
// 	// if (Online(l, c)) {
// 	// 	return ((c - l.p) & (c - l.q)) < Eps;
// 	// }
// 	// return false;
// 	return Online(l, c) && ((c - l.p) & (c - l.q)) < Eps;

// 	// Lf t = (c - l.p) & l.v().Norm();
// 	// return Online(l, c) && (t > -Eps && t < (l.v() & l.v().Norm()) + Eps);
// }
// bool Inline(const Line& l, const Comp& c) {
// 	return Online(l, c) && ((c - l.p) & (c - l.q)) < -Eps;
// 	// Lf t = (c - l.p) & l.v().Norm();
// 	// return Online(l, c) && (t > Eps && t < (l.v() & l.v().Norm()) - Eps);
// }
// Comp Inter(const Line& a, const Line& b) {
// 	if (std::abs(a.v() | b.v()) < Eps) return Comp(NAN, NAN);
// 	Lf w1 = (a.q - b.p) | (a.p - b.p);
// 	Lf w2 = (a.p - b.q) | (a.q - b.q);
// 	return b.p + b.v() / (w1 + w2) * w1;
// }
// struct Wall {
// 	int a, b, x, y;
// 	std::vector<Line> sur;
// 	void Init() {
// 		scanf("%d%d%d%d", &a, &b, &x, &y);
// 		sur.push_back({ Comp(a, b), Comp(x, b) });
// 		sur.push_back({ Comp(x, b), Comp(x, y) });
// 		sur.push_back({ Comp(x, y), Comp(a, y) });
// 		sur.push_back({ Comp(a, y), Comp(a, b) });
// 		// for (Line l : sur) {
// 		// 	ver.push_back((l.v() * Comp(0, 1)).Norm());
// 		// 	printf("%d\n", (l.v() * Comp(0, 1)).Norm());
// 		// }
// 	}
// 	bool InWall(const Comp& c) {
// 		return a + Eps < c.x && c.x < x - Eps && b + Eps < c.y && c.y < y - Eps;
// 	}
// } wall[M];

// char buff[25];

// int Pos(const Comp& c, int& fc) {
// 	int p = 2;
// 	for (int i = 1; i <= m; i++) {
// 		// if (TTT == 19240) {
// 		// 	fprintf(FileP, "TTT = %d, c = (%Lf, %Lf), sur = (%Lf, %Lf, %Lf, %Lf), NotOut = %d\n", TTT, c.x, c.y, wall[i].sur[1].p.x, wall[i].sur[1].p.y, wall[i].sur[1].q.x, wall[i].sur[1].q.y, NotOutline(wall[i].sur[1], c));
// 		// }
// 		if (NotOutline(wall[i].sur[0], c)) {
// 			fc = 0;
// 			p = std::min(p, 0);
// 		} else if (NotOutline(wall[i].sur[1], c)) {
// 			// fprintf(FileP, "c = (%Lf, %Lf)\n", c.x, c.y);
// 			fc = 1;
// 			p = std::min(p, 1);
// 		} else if (NotOutline(wall[i].sur[3], c)) {
// 			// fprintf(FileP, "c = (%Lf, %Lf)\n", c.x, c.y);
// 			fc = -1;
// 			p = std::min(p, 1);
// 		}
// 	}
// 	return p;
// }
// // Pos() == 0: 着地
// // Pos() == 1: 贴墙
// // Pos() == 2: 悬空

// void Add(Lf& x, Lf y, Lf l) {
// 	if (y < -Eps) x = std::max(l, x + y);
// 	if (y > Eps) x = std::min(l, x + y);
// }

// int main() {
// 	// freopen("1.in", "r", stdin);
// 	// freopen("1.out", "w", stdout);
// 	// {
// 	// 	Line testl = { Comp(1000, 0), Comp(1000, 9000000) };
// 	// 	Comp testc = Comp(1000.000000, 3038067.600000);
// 	// 	fprintf(FileP, "%d\n", NotOutline(testl, testc));
// 	// }
// 	scanf("%d", &m);
// 	for (int i = 1; i <= m; i++) wall[i].Init();
// 	Comp X, V(0, 0);
// 	int lstK = 0, lstKst = -1; // K 持续的时长, 引发进入跳跃状态的 Pos()
// 	int lstL = 0, restL = 2; // L 持续的时长
// 	std::unordered_map<char, bool> dirL;
// 	scanf("%Lf%Lf", &X.x, &X.y);
// 	scanf("%d", &T);
// 	A1[0] = 45, A1[1] = A1[2] = 30;
// 	A2[0] = -6.7, A2[1] = A2[2] = -4.3;
// 	for (int t = 1; t <= T; t++) {
// 		TTT = t;
// 		// printf("t = %d\n", t);
// 		// printf("pre:\n");
// 		// dbg(V.x);
// 		// dbg(V.y);
// 		int fc, curPos = Pos(X, fc);
// 		// fprintf(FileV, "X = (%Lf, %Lf), curPos = %d, ", X.x, X.y, curPos);

// 		if (curPos == 0) restL = 2;

// 		// 解除冲刺状态
// 		if (lstL) {
// 			// if (dirL['A']) V = Comp(-240, 0);
// 			// if (dirL['D']) V = Comp(240, 0);
// 			// if (dirL['W']) V = Comp(0, -240);
// 			// if (dirL['S']) V = Comp(0, 240);
// 			// if (dirL['A'] && dirL['W']) V = Comp(-169, -169);
// 			// if (dirL['D'] && dirL['W']) V = Comp(169, -169);
// 			// if (dirL['A'] && dirL['S']) V = Comp(-169, 169);
// 			// if (dirL['D'] && dirL['S']) V = Comp(169, 169);
// 			if (++lstL > 10) {
// 				lstL = 0;
// 				if (dirL['A']) V = Comp(-160, 0);
// 				if (dirL['D']) V = Comp(160, 0);
// 				if (dirL['W']) V = Comp(0, -160);
// 				if (dirL['S']) V = Comp(0, 160);
// 				if (dirL['A'] && dirL['W']) V = Comp(-113, -113);
// 				if (dirL['D'] && dirL['W']) V = Comp(113, -113);
// 				if (dirL['A'] && dirL['S']) V = Comp(-113, 113);
// 				if (dirL['D'] && dirL['S']) V = Comp(113, 113);
// 			}
// 		}

// 		Comp newV = V;
// 		std::unordered_map<char, bool> key;
// 		scanf("%s", buff + 1);
// 		int len = strlen(buff + 1);
// 		for (int i = 1; i <= len; i++) key[buff[i]] = true;

// 		// 横向移动
// 		if (lstL == 0) {
// 			// printf("!!!\n");
// 			if ((key['A'] || key['D'])) {
// 				int k = key['A'] ? -1 : 1;
// 				if (V.x * k < Eps || std::abs(V.x) < 90 - Eps) Add(newV.x, A1[curPos] * k, 90 * k);
// 				else if (V.x * k > 0 && std::abs(V.x) > 90 + Eps) Add(newV.x, A2[curPos] * k, 90 * k);
// 			}
// 			if (!key['A'] && !key['D']) {
// 				int k = newV.x > 0 ? 1 : -1;
// 				Lf a = curPos == 0 ? -16.7 : -10.8;
// 				Add(newV.x, a * k, 0);
// 			}
// 		}

// 		// 跳跃
// 		if (lstL == 0) {
// 			if (key['K']) {
// 				if (curPos == 0) {
// 					// assert(lstK == 0);
// 					newV.y = -105;
// 					lstK = 1, lstKst = 0;
// 				} else if (curPos == 1) {
// 					newV.y = -105;
// 					newV.x += fc * 130;
// 					lstK = 1, lstKst = 1;
// 				} else if (lstKst == 0) {
// 					if (++lstK <= 12) newV.y = -105;
// 					else lstK = 0, lstKst = -1;
// 				} else lstK = 0, lstKst = -1;
// 			} else lstK = 0, lstKst = -1;
// 		}

// 		// 冲刺
// 		if (key['L'] && lstL == 0) {
// 			if (restL) {
// 				// printf("restL = %d\n", restL);
// 				restL--, lstK = 0, lstKst = -1;
// 				dirL = key;
// 				if (key['A']) newV = Comp(-240, 0);
// 				if (key['D']) newV = Comp(240, 0);
// 				if (key['W']) newV = Comp(0, -240);
// 				if (key['S']) newV = Comp(0, 240);
// 				if (key['A'] && key['W']) newV = Comp(-169, -169);
// 				if (key['D'] && key['W']) newV = Comp(169, -169);
// 				if (key['A'] && key['S']) newV = Comp(-169, 169);
// 				if (key['D'] && key['S']) newV = Comp(169, 169);
// 				// printf("V = (%Lf, %Lf)\n", newV.x, newV.y);
// 				lstL++;
// 			}
// 		}
// 		// printf("%Lf %Lf\n", newV.x, newV.y);

// 		// 重力
// 		if (!lstK && !lstL) {
// 			Lf lim = key['S'] ? 240 : 160;
// 			if (curPos == 1) Add(newV.y, 1.9, lim);
// 			else if (curPos == 2) Add(newV.y, 15, lim);
// 		}
		
// 		V = newV;
// 		// printf("(%Lf, %Lf) ", V.x, V.y);
// 		// fprintf(FileV, "V = (%Lf, %Lf), ", V.x, V.y);

// 		// 计算新位置
// 		Comp NewX = X + V;
// 		// printf("(%Lf, %Lf) ", NewX.x, NewX.y);
// 		Comp detX = V;
// 		// dbg(NewXX.x);
// 		// dbg(NewXX.y);
// 		// dbg(NewXY.x);
// 		// dbg(NewXY.y);
// 		Lf dis = V.abs();
// 		Line ln = { X, NewX };
// 		bool setVx = false, setVy = false;
// 		for (int i = 1; i <= m; i++)
// 			for (int j = 0; j < 4; j++) {
// 				Line sur = wall[i].sur[j];
// 				if (Inline(sur, X) && (ln.v() & ver[j]) < -Eps) {
// 					dis = 0;
// 				} else {
// 					Comp it = Inter(sur, ln);
// 					if (!std::isnan(it.x) && !std::isnan(it.y)) {
// 						if (Inline(sur, it) && Inline(ln, it)) {
// 							dis = std::min(dis, (X - it).abs());
// 						}
// 					}
// 				}
// 			}
// 		for (int i = 1; i <= m; i++)
// 			for (int j = 0; j < 4; j++) {
// 				Line sur = wall[i].sur[j];
// 				if (Inline(sur, X) && (ln.v() & ver[j]) < -Eps) {
// 					if (std::abs(dis) < Eps) {
// 						if (j == 1 || j == 3) setVx = true;
// 						if (j == 0 || j == 2) setVy = true;
// 					}
// 				} else {
// 					Comp it = Inter(sur, ln);
// 					if (!std::isnan(it.x) && !std::isnan(it.y)) {
// 						if (Inline(sur, it) && Inline(ln, it)) {
// 							// printf("{ (%Lf, %Lf), (%Lf, %Lf), (%Lf, %Lf), (%Lf, %Lf) } [%Lf, %Lf] ", sur.p.x, sur.p.y, sur.q.x, sur.q.y, ln.p.x, ln.p.y, ln.q.x, ln.q.y, it.x, it.y);
// 							if (std::abs(dis - (X - it).abs()) < Eps) {
// 								if (j == 1 || j == 3) setVx = true;
// 								if (j == 0 || j == 2) setVy = true;
// 							}
// 						}
// 					}
// 				}
// 			}
// 		if (V.abs() > Eps) detX = V / V.abs() * dis;
// 		X += detX;
// 		if (setVx) V.x = 0;//, dirL.erase('A'), dirL.erase('D');
// 		if (setVy) V.y = 0;//, dirL.erase('W'), dirL.erase('S');
// 		// if (std::abs(X.x) < Eps) X.x = 0;
// 		// if (std::abs(X.y) < Eps) X.y = 0;
// 		// X.x=roundl(X.x*1e6)/1e6;X.y=roundl(X.y*1e6)/1e6;
//         // if(!(X.x==(Lf)round(X.x)||(abs(X.x-round(X.x))>1e-8)))printf("d");
//         // if(!(((abs(X.x-round(X.x))<1e-30)||(abs(X.x-round(X.x))>1e-8))&&((abs(X.y-round(X.y))<1e-30)||(abs(X.y-round(X.y))>1e-8)))){
// 		// 	printf("[%.30Lf %.30Lf]\n",X.x,X.y);
// 		// }
// 		printf("%.30Lf %.30Lf\n", X.x, X.y);
		
// 		for (int i = 1; i <= m; i++)
// 			assert(!wall[i].InWall(X));
// 		// printf("(%Lf, %Lf)\n", V.x, V.y);
// 		// fprintf(FileV, "V' = (%Lf, %Lf)\n", V.x, V.y);
// 		// printf("aft:\n");
// 		// dbg(V.x);
// 		// dbg(V.y);
// 	}
// 	fclose(stdin), fclose(stdout);
// 	return 0;
// }
#include<bits/stdc++.h>
using namespace std;
#define db long double
#define ll long long
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
const db eps=1e-8l;
int m;
struct Vec{
    db x,y;
    db len(){return sqrtl(x*x+y*y);}
    Vec operator+(Vec _){return {x+_.x,y+_.y};}
    Vec operator+=(Vec _){x+=_.x;y+=_.y;return *this;}
    Vec operator-(Vec _){return {x-_.x,y-_.y};}
    Vec operator-=(Vec _){x-=_.x;y-=_.y;return *this;}
    Vec operator*(db _){return {x*_,y*_};}
};
Vec s;
bool operator<(Vec a,Vec b){return (a-s).len()<(b-s).len();}
bool operator==(Vec a,Vec b){return abs(a.x-b.x)<eps&&abs(a.y-b.y)<eps;}
db Dot(Vec a,Vec b){return a.x*b.x+a.y*b.y;}
db Cro(Vec a,Vec b){return a.x*b.y-a.y*b.x;}
struct Seg{Vec s,t;};
int dcmp(db x){return (x<-eps)?-1:((x>eps)?1:0);}
bool Onseg(Vec a,Seg b){return (dcmp(Cro(a-b.s,b.t-b.s)==0))&&(dcmp(Dot(a-b.s,a-b.t))<=0);}
bool onseg(Vec a,Seg b,bool heng){
    if(b.s.x>b.t.x)swap(b.s.x,b.t.x);
    if(b.s.y>b.t.y)swap(b.s.y,b.t.y);
    if(heng)return abs(b.s.y-a.y)<eps&&b.s.x-a.x<-eps&&a.x-b.t.x<-eps;
    return abs(b.s.x-a.x)<eps&&b.s.y-a.y<-eps&&a.y-b.t.y<-eps;
}
bool isinter(Seg a,Seg b){
    db c1=Cro(a.t-a.s,b.s-a.s),c2=Cro(a.t-a.s,b.t-a.s);
    db d1=Cro(b.t-b.s,a.s-b.s),d2=Cro(b.t-b.s,a.t-b.s);
    return (dcmp(c1)*dcmp(c2)<=0&&dcmp(d1)*dcmp(d2)<=0&&(dcmp(c1)*dcmp(c2)==0&&dcmp(d1)*dcmp(d2)==0)==0);
}
Vec inter(Seg a, Seg b){
    if(!isinter(a,b))return {1e14,1e14};
    Vec x=b.s-a.s,y=b.t-a.s,xx=b.t-a.t,yy=b.s-a.t;
    db w1=Cro(x,y),w2=Cro(xx,yy);
    return a.s+(a.t-a.s)*(w1/(w1+w2));
}
bool OnD(Seg a,Seg b){  
    Vec o=inter(a,b);if(o.x==1e14&&o.y==1e14)return 0;
    if(a.s==o||a.t==o||b.s==o||b.t==o)return 0;
    return 1;
}
Vec Inter(Seg a,Seg b){
    if(OnD(a,b))return inter(a,b);
    return {1e14,1e14};
}
struct Rec{Seg a,b,c,d;}p[55];
db vx,vy;
db acc(db v,db x,db y){return (x>-eps?min(v+x,y):max(v+x,y));}
int style,at,lei;bool near;
int check(){
    bool a=0,b=0,c=0,d=0;at=lei=0;
    bool aa=0,bb=0,cc=0,dd=0;
    rep(i,1,m){
        if(onseg(s,p[i].a,1))a=1,at=i,lei=1;
        if(onseg(s,p[i].b,0))b=1,at=i,lei=2;
        if(onseg(s,p[i].c,1))c=1,at=i,lei=3;
        if(onseg(s,p[i].d,0))d=1,at=i,lei=4;
        if(p[i].a.s==s)aa=1;
        if(p[i].b.s==s)bb=1;
        if(p[i].c.s==s)cc=1;
        if(p[i].d.s==s)dd=1;
    }
    if(aa|bb){style=3;lei=1;return style;}
    if(cc|dd){style=2;near=cc;lei=(cc?2:4);return style;}
    if(!a&&!b&&!d)style=1;
    if(b||d)style=2,near=b;
    if(a)style=3;
    return style;
}
bool in(Vec s){
    rep(i,1,m){
        if(p[i].a.s.y-s.y<-eps&&s.y-p[i].c.s.y<-eps&&p[i].d.s.x-s.x<-eps&&s.x-p[i].b.s.x<-eps)return 1;
    }
    return 0;
}
int main(){
     freopen("celeste.in","r",stdin);
     freopen("celeste.out","w",stdout);
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>m;
    rep(i,1,m){
        db a,b,c,d;cin>>a>>b>>c>>d;
        Vec A={a,b},B={c,b},C={c,d},D={a,d};
        p[i]={{A,B},{B,C},{C,D},{D,A}};
    }
    cin>>s.x>>s.y;check();
    int T;cin>>T;
    int cnt=2,jcnt=0,run=0;bool jie=0,jump=0;
    bool DW,DS,DA,DD;
    while(T--){
        string o;cin>>o;
        bool W=0,S=0,A=0,D=0,L=0,K=0;for(auto i:o)W|=(i=='W'),S|=(i=='S'),A|=(i=='A'),D|=(i=='D'),L|=(i=='L'),K|=(i=='K');
        if(style==3)cnt=2;
        if(jie){
            if(DW)vy=-160;
            if(DS)vy=160;
            if(DA)vx=-160;
            if(DD)vx=160;
            if(DW&DA)vx=-113,vy=-113;
            if(DA&DS)vx=-113,vy=113;
            if(DS&DD)vx=113,vy=113;
            if(DD&DW)vx=113,vy=-113;
            jie=0;
        }
        if(run){
            run--;if(!run)jie=1;
        }else if(L&&cnt){
            jump=jcnt=0;
            run=9;cnt--;
            vx=0;vy=0;
            DW=W,DS=S,DA=A,DD=D;
            if(W)vy=-240;
            if(S)vy=240;
            if(A)vx=-240;
            if(D)vx=240;
            if(W&A)vx=-169,vy=-169;
            if(A&S)vx=-169,vy=169;
            if(S&D)vx=169,vy=169;
            if(D&W)vx=169,vy=-169;
        }else{
            if(A|D){
                int k=(A?-1:1);
                if(k*vx>0&&abs(vx)>90){
                    vx=acc(vx,(style==3?-6.7*k:-4.3*k),90*k);
                }else{
                    vx=acc(vx,(style==3?45*k:30*k),90*k);
                }
            }else{
                int k=(vx>0?1:-1);
                vx=acc(vx,(style==3?-16.7*k:-10.8*k),0);
            }
            if(K){
                db tmp=vy;vy=-105;jump=1;
                if(style==3)jcnt=1;
                if(style==2){
                    if(near)vx+=130;
                    else vx+=-130;
                    jcnt=0;
                }
                if(style==1){
                    if(jcnt){
                        if(jcnt==12)jcnt=0,jump=0,vy=tmp;
                        else jcnt++;
                    }else jump=jcnt=0,vy=tmp;
                }
            }else jump=jcnt=0;
            if(!jump){
                if(style==1)vy=acc(vy,15,S?240:160);
                if(style==2)vy=acc(vy,1.9,S?240:160);
            }
        }
        // assert(abs(vx)<=5000&&abs(vy)<=5000);
        // rep(i,1,m){
        //     assert(Onseg(p[i].d.t,{s,{s.x+vx,s.y+vy}})==0||(abs(vx)<eps)||(abs(vy)<eps));
        //     assert(Onseg(p[i].a.t,{s,{s.x+vx,s.y+vy}})==0||(abs(vx)<eps)||(abs(vy)<eps));
        //     assert(Onseg(p[i].b.t,{s,{s.x+vx,s.y+vy}})==0||(abs(vx)<eps)||(abs(vy)<eps));
        //     assert(Onseg(p[i].c.t,{s,{s.x+vx,s.y+vy}})==0||(abs(vx)<eps)||(abs(vy)<eps));
        // }
        if(at&&in((Vec){s.x+vx*1e-7,s.y+vy*1e-7})){
            if(lei==1)vy=0;if(lei==2)vx=0;
            if(lei==3)vy=0;if(lei==4)vx=0;
        }else{
            Seg u={s,{s.x+vx,s.y+vy}};Vec h={1e14,1e14};
            rep(i,1,m){
                h=min(Inter(u,p[i].a),h);
                h=min(Inter(u,p[i].b),h);
                h=min(Inter(u,p[i].c),h);
                h=min(Inter(u,p[i].d),h);
            }
            if(h.x==1e14&&h.y==1e14){
                s.x+=vx;s.y+=vy;
            }else{
                Vec tmp=s;
                s=h;check();
                if(lei==1)vy=0;if(lei==2)vx=0;
                if(lei==3)vy=0;if(lei==4)vx=0;
            }
        }
        check();
        //assert(((s.x==(db)round(s.x))||(abs(s.x-round(s.x))>1e-6))&&((s.y==(db)round(s.y))||(abs(s.y-round(s.y))>1e-6)));
        printf("%.6Lf %.6Lf\n",s.x,s.y);
    }
    return 0;
}