#ifndef __EXPR_H__
#define __EXPR_H__

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct {
        int x;
    } Data;
    Data F(Data a, Data b, int op);
    void init(int test_id, int n, int m, int k, const Data *a, const int *ops);  // precedences: 1 ~ k, larger is higher
    Data modify_data(int id, int pos, Data x);
    Data modify_op(int id, int pos, int new_op); // modify the operator between pos and pos - 1
    Data reverse(int id, int l, int r);
#ifdef __cplusplus
}
#endif

#endif
