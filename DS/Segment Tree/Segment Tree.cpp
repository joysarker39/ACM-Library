struct Node {
    int sum = 0, mx, mn;
    Node(int a = 0, int b = 0, int c = 0) {
        sum = a;
        mx = b;
        mn = c;
    }
} tree[MAX*4];

Node _merge(Node A, Node B) {
    Node C;
    C.sum = A.sum + B.sum;
    C.mx =  max(A.mx, B.mx);
    C.mn = min(A.mn, B.mn);
    return C;
}

void init(int idx, int st, int ed) {
    if(st == ed) {tree[idx] = {arr[st], arr[st], arr[st]};return;}
    int mid = (st + ed) >> 1, L = idx << 1, R = L + 1;
    init(L, st, mid);
    init(R, mid+1, ed);
    tree[idx] = _merge(tree[L], tree[R]);
}

Node range_query(int idx, int st, int ed, int i, int j) {
    if(st == i and ed == j) return tree[idx];
    int mid = (st + ed) >> 1, L = idx << 1, R = L + 1;
    if(mid < i) return range_query(R, mid+1, ed, i, j);
    if(j <= mid) return range_query(L, st, mid, i, j);
    return _merge(range_query(L, st, mid, i, mid), range_query(R, mid+1, ed, mid+1, j));
}

void point_update(int idx, int st, int ed, int pos, int val) {
    if(st == ed and ed == pos) {tree[idx] = {arr[st], arr[st], arr[st]};return;}
    int mid = (st + ed) >> 1, L = idx << 1, R = L + 1;
    if(mid < pos) point_update(R, mid+1, ed, pos, val);
    else point_update(L, st, mid, pos, val);
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
