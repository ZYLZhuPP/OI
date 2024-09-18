#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct IO {
	char c, f;
	#define gc() getchar()
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

char st[(int)1e7 + 5];
ll T;

int main() {
	io >> T;
	
	while (T--) {
		fgets(st, sizeof(st), stdin);
		bool flag = 1;
		ll len = strlen(st) - 1, i = 0;
		if (!len) {
			puts("Input Error");
			continue;
		}
		ll x = 0, y = 0, f = 1;
		
		if (st[i] == '-') f = -1, i++;
		if (!isdigit(st[i]) || (st[i] == '0' && st[i+1] ^ ' ')) {
			puts("Input Error");
			continue;
		}
		x = (st[i++] ^ 48);
		
		for (; i < len; i++) {
			if (st[i] == ' ') break;
			if (!isdigit(st[i])) {
				flag = 0;
				break;
			}
			
			x = (x << 3) + (x << 1) + (st[i] ^ 48);
			if (x*f < INT_MIN || INT_MAX < x*f) {
				flag = 0;
				break;
			}
		}
		
		if (!flag || i >= len-1) {
			puts("Input Error");
			continue;
		}
		x *= f;
		
		i++; f = 1;
		if (st[i] == '-') f = -1, i++;
		if (!isdigit(st[i]) || (st[i] == '0' && i < len-1)) {
			puts("Input Error");
			continue;
		}
		y = (st[i++] ^ 48);
		
		for (; i < len; i++) {
			if (st[i] == ' ') break;
			if (!isdigit(st[i])) {
				flag = 0;
				break;
			}
			
			y = (y << 3) + (y << 1) + (st[i] ^ 48);
			if (y*f < INT_MIN || INT_MAX < y*f) {
				flag = 0;
				break;
			}
		}
		
		if (!flag || i < len) {
			puts("Input Error");
			continue;
		}
		y *= f;
		
		printf("%lld\n", x + y);
	}
	return 0;
}

