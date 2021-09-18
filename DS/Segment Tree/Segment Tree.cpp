#include<bits/stdc++.h>
using namespace std;
#define fast_cin ios_base::sync_with_stdio(false);cin.tie(NULL)
#define D(x) cerr<<__LINE__<<" : "<<#x<<" -> "<<x<<endl

const int MAX = 1e5+7;            ///Check Every Time
int t=1, n, m, l, k, tc, q;
int arr[MAX];
char s[MAX];

struct Node {
    int mp[26], d;
    Node() {
        for(int i = 0; i < 26; i++)
            mp[i] = 0;
        d = 0;
    }
} tree[MAX*4];

Node _merge(Node A, Node B) {
    if(A.d == 26) return A;
    if(B.d == 26) return B;
    Node C;
    for(int i = 0; i < 26; i++){
        C.mp[i] = (A.mp[i] or B.mp[i]);
        C.d += C.mp[i];
    }
    return C;
}

void init(int idx, int st, int ed) {
    if(st == ed) {
        tree[idx].mp[arr[st]] = 1;
        tree[idx].d = 1;
        return;
    }
    int mid = (st + ed) >> 1, L = idx << 1, R = L + 1;
    init(L, st, mid);
    init(R, mid+1, ed);
    tree[idx] = _merge(tree[L], tree[R]);
}
/// for single value
//int range_query1(int idx, int st, int ed, int i, int j) {
//    if(i > ed or j < st) return 0;
//    if( i <= st and ed <= j) return tree[idx].distinct;
//    int mid = (st + ed) >> 1, L = idx << 1, R = L + 1;
//    int lside = range_query1(L, st, mid, i, j);
//    int rside = range_query1(R, mid+1, ed, i, j);
//    return lside + rside;
//}

Node range_query(int idx, int st, int ed, int i, int j) {
    if(st == i and ed == j) return tree[idx];
    int mid = (st + ed) >> 1, L = idx << 1, R = L + 1;
    if(mid < i) return range_query(R, mid+1, ed, i, j);
    if(j <= mid) return range_query(L, st, mid, i, j);
    return _merge(range_query(L, st, mid, i, mid), range_query(R, mid+1, ed, mid+1, j));
}

void update(int idx, int st, int ed, int pos, char val) {
    if(st == ed and ed == pos) {
        tree[idx].mp[arr[pos]] = 0;
        arr[pos] = val;
        tree[idx].mp[val] = 1;
        return;
    }
    int mid = (st + ed) >> 1, L = idx << 1, R = L + 1;
    if(mid < pos) update(R, mid+1, ed, pos, val);
    else update(L, st, mid, pos, val);
    tree[idx] = _merge(tree[L], tree[R]);
}
