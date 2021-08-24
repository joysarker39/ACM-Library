const int MAX = 2e5+7;
int arr[MAX + 5], blkId[MAX];

struct Query {
    int l,r,id;
    Query() {}
    Query(int x,int y,int i) {
        l=x;
        r=y;
        id=i;
    }
    bool operator<(const Query other) const {
        int a = blkId[l];
        int b = blkId[other.l];
        return a == b ? (a & 1 ? (r > other.r) : (r < other.r)) : a < b;
    }
};

struct MO {
    int unique_values, L, R, N,  block_s = 320; /// 320 is acceptable
    Query queries[MAX + 5];
    int perQ[MAX + 5], freq[1000007];

    MO(int n) {
        L = 0;
        R = -1;
        unique_values = 0;
        N = n;
        block_s = sqrt(n);
        memset(freq,0,sizeof(freq));
        for(int i=0; i<=n; i++) blkId[i] = i/block_s;
    }

    void add(int idx) {
        freq[arr[idx]]++;
        if(freq[arr[idx]] == 1) unique_values++;
    }

    void del(int idx) {
        freq[arr[idx]]--;
        if(freq[arr[idx]] == 0) unique_values--;
    }
    void add_query(int Q) {
        for(int i = 0; i < Q; i++) {
            scanf("%d%d", &queries[i].l, &queries[i].r);
            --queries[i].l;
            --queries[i].r;
            queries[i].id = i;
        }
    }
    void process_query(int Q) {
        sort(queries, queries + Q);
        for(int i = 0; i < Q; i++) {
            while(queries[i].l < L) add(--L);
            while(queries[i].l > L) del(L++);
            while(queries[i].r < R) del(R--);
            while(queries[i].r > R) add(++R);
            perQ[queries[i].id] = unique_values;
        }
    }
};
