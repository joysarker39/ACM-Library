struct Node {
    vector < int > vec;
};
Node tree[MAX*4];

Node _merge(Node A, Node B) {
    Node temp;
    int i = 0, j = 0, sa = A.vec.size(), sb = B.vec.size();
    while(i < sa and j < sb) {
        if(A.vec[i] < B.vec[j]) temp.vec.push_back(A.vec[i++]);
        else temp.vec.push_back(B.vec[j++]);
    }
    while(i < sa) temp.vec.push_back(A.vec[i++]);
    while(j < sb) temp.vec.push_back(B.vec[j++]);
    return temp;
}

void init(int idx, int st, int ed) {
    if(st == ed) {
        tree[idx].vec.push_back(arr[st]);
        return;
    }
    int mid = (st + ed ) >> 1, L = idx << 1, R = L + 1;
    init(L, st, mid);
    init(R, mid+1, ed);
    tree[idx] = _merge(tree[L], tree[R]);
}

int range_query(int idx, int st, int ed, int i, int j, int k) {
    if(i > ed or j < st) return 0;
    if(st >= i and ed <= j) return (tree[idx].vec.end() - upper_bound(tree[idx].vec.begin(),tree[idx].vec.end(), k));
    int mid = (st + ed ) >> 1, L = idx << 1, R = L + 1;
    int lside = range_query(R, mid+1, ed, i, j, k);
    int rside = range_query(L, st, mid, i, j, k);
    return lside + rside;
}
