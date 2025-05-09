/* This is sample grader for the contestant */

#include"expr.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<time.h>

#define debug(...) // fprintf(stderr,__VA_ARGS__)

static double clock_start;

inline static void __exit()
{
    debug("time: %.0lf ms\n",(clock()-clock_start)*1000.0/CLOCKS_PER_SEC);
    exit(0);
}

inline static void WA()
{
    printf("-1\n");
}


#define MAXN 20005
#define MAXM 20005
#define MAX_K 105

static int rand_seed;

inline static int getrand()
{
    return rand_seed = rand_seed * 16807LL % 2147483647LL;
}

inline static void init_rand_seed()
{
    rand_seed = 31473487;
}

static int F_counter;

static int test_id;
static int n;
static int m;
static int k;
static int F_counter_limit;

#define u32 unsigned int

static u32 mask1[MAX_K];
static u32 mask2[MAX_K];

inline static Data new_data()
{
    return (Data){getrand()};
}

inline static void init_masks()
{
    int i,j;
    for (i=1;i<=k;i++) {
        for (j=0;j<32;j++) {
            if ((getrand()>>17)&1) {
                mask1[i]|=1<<j;
            } else {
                mask2[i]|=1<<j;
            }
        }
    }
}

inline static u32 _F(u32 a, u32 b, int op)
{
    assert(op > 0 && op <= k);
    return (mask1[op]&((mask1[op]&a)+(mask1[op]&b)))
            |(mask2[op]&((mask2[op]&a)^(mask2[op]&b)));
}

Data F(Data a, Data b, int op)
{
    if (op < 1 || op > k) {
        WA();
        printf("Invalid operation (op = %d)\n", op);
        __exit();
    }
    ++F_counter;
    if (F_counter > F_counter_limit) {
        WA();
        printf("Too many calls of F()\n");
        __exit();
    }
    return (Data){(int)_F((u32)a.x,(u32)b.x,op)};
}

static Data a[MAXN];
static int ops[MAXN];

static int _id[MAXM];
static int _type[MAXM];
static int _pos[MAXM];
static int _new_op[MAXM];
static int _l[MAXM];
static int _r[MAXM];

int main()
{
    freopen("expr.in", "r", stdin);
    freopen("expr.out", "w", stdout);

    assert(scanf("%d%d%d%d", &test_id, &n, &m, &k) == 4);
    assert(scanf("%d", &F_counter_limit) == 1);

    assert(n > 1 && n <= 20000);
    assert(m > 0 && m <= 20000);
    assert(k > 0 && k <= 100);

    assert(F_counter_limit > 0);

    init_rand_seed();
    init_masks();

    int i;
    for (i=0;i<n;i++) {
        a[i] = new_data();
    }
    
    for (i=1;i<n;i++) {
        assert(scanf("%d",ops+i) == 1);
    }

    for (i=1;i<=m;i++) {
        assert(scanf("%d",_id+i) == 1);
        assert(_id[i] >= 0 && _id[i] < i);

        assert(scanf("%d",_type+i) == 1);

        if (_type[i] == 1) {
            assert(scanf("%d",_pos+i) == 1);
            assert(_pos[i] >= 0 &&  _pos[i] < n);
        } else if (_type[i] == 2) {
            assert(scanf("%d%d",_pos+i,_new_op+i) == 2);
            assert(_pos[i] > 0 && _pos[i] < n);
            assert(_new_op[i] > 0 && _new_op[i] <= k);
        } else {
            assert(_type[i] == 3);
            assert(scanf("%d%d",_l+i,_r+i) == 2);
            assert(0 <= _l[i] && _l[i] <= _r[i] && _r[i] < n);
        }
    }

    init(test_id, n, m, k, a, ops);

    int checksum = 0;

    for (i=1;i<=m;i++) {
        Data ret;
        if (_type[i] == 1) {
            Data x = new_data();
            ret = modify_data(_id[i], _pos[i], x);
        } else if (_type[i] == 2) {
            ret = modify_op(_id[i], _pos[i], _new_op[i]);
        } else {
            assert(_type[i] == 3);
            ret = reverse(_id[i], _l[i], _r[i]);
        }
        checksum = (checksum * 998244353LL + ret.x) % 1000000009;
    }
    
    if (checksum < 0) {
        checksum += 1000000009;
    }
    
    printf("%d\n", checksum);
    
    printf("%d\n", F_counter);
    
    __exit();
    
}