/// 0 based Indexing 

const int MAX = 2e5+7; ///Check Every Time
const int maxN = 19;
int t=1, n, m, l, k, tc, q;

vector < int > edge[MAX];
int w[MAX], euler[MAX*2], tin[MAX], tout[MAX];
int arr[MAX + 5], blkId[MAX];
int Time = 0, LCA[MAX][20], level[MAX], par[MAX];

void dfs(int u, int prv) {
    par[u] = prv;
    tin[u] = Time;
    euler[Time++] = u;
    for(int v: edge[u])
        if(v != prv) level[v] = level[u]+1,dfs(v,u);
    tout[u] = Time;
    euler[Time++] = u;
}
/// /////////////////////////////////////////////////////
void build_LCA() {
    memset(LCA,-1,sizeof LCA);
    for(int i = 0; i <= n; i++)
        LCA[i][0] = par[i];
    for(int j = 1; j<=maxN; j++)
        for(int i = 0; i<=n; i++)
            if(LCA[i][j-1] != -1)
                LCA[i][j] = LCA[LCA[i][j-1]][j-1];
}

int lca(int a, int b) {
    if(level[a]<level[b]) swap(a, b);
    int d = level[a] - level[b];
    while(d>0) {
        int i = log2(d);
        a = LCA[a][i];
        d-=(1<<i);
    }
    if(a == b) return a;
    for(int i = maxN; i>=0; i--) {
        int parA = LCA[a][i],parB = LCA[b][i];
        if(parA != -1 and (parA != parB))
            a = parA, b = parB;
    }
    return LCA[a][0];
}
////////////////////////////////////////////////////////////
struct Query {
    int l,r,id, lca;
    Query() {}
    Query(int x,int y,int i, int lc) {
        l=x;
        r=y;
        id=i;
        lca = lc;
    }
    bool operator<(const Query other) const {
        int a = blkId[l];
        int b = blkId[other.l];
        return a == b ? (a & 1 ? (r > other.r) : (r < other.r)) : a < b;
    }
};

struct MO {
    int nodeCount, L, R, N,  block_s = 320; /// 320 is acceptable
    Query queries[MAX + 5];
    int perQ[MAX + 5], freq[1000007];

    MO(int n) {
        L = 0;
        R = -1;
        nodeCount = 0;
        N = n;
        block_s = sqrt(n);
        memset(freq,0,sizeof(freq));
        for(int i=0; i<=n; i++) blkId[i] = i/block_s;
    }

    void add(int idx) {
        int node = euler[idx];
        freq[node]++;
        if(freq[node] == 1) nodeCount++;
        if(freq[node] == 2) nodeCount--;
    }

    void del(int idx) {
        int node = euler[idx];
        freq[node]--;
        if(freq[node] == 1) nodeCount++;
        if(freq[node] == 0) nodeCount--;
    }
    void add_lca(int node) {
        return true;
    }
    void add_query(int Q) {
        for(int i = 0; i < Q; i++) {
            int u, v;
            scanf("%d%d",&u,&v);
            u--, v--;
            if(tin[u] > tin[v]) swap(u,v);
            int Lca = lca(u,v);
            if(Lca == u)
                queries[i] = {tin[u], tin[v], i, -1};
            else
                queries[i] = {tout[u],tin[v],i, Lca};
        }
    }
    void process_query(int Q) {
        sort(queries, queries + Q);
        for(int i = 0; i < Q; i++) {
            while(queries[i].l < L) add(--L);
            while(queries[i].l > L) del(L++);
            while(queries[i].r < R) del(R--);
            while(queries[i].r > R) add(++R);

            int ex = 0;
            if(queries[i].lca != -1) ex = add_lca(queries[i].lca);
            perQ[queries[i].id] = nodeCount + ex; ///number of node in path(u,v);
        }
    }
};
////////////////////////////////////////////////////////////

signed main() {
    while(t--) {
        scanf("%d%d",&n,&q);
        for(int i = 1; i < n ; i++) {
            int u, v;
            scanf("%d%d",&u,&v);
            u--, v--;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        dfs(0,-1);
        build_LCA();
        MO mos(Time);
        mos.add_query(q);
        mos.process_query(q);
        for(int i = 0; i < q; i++)
            cout << mos.perQ[i] << "\n";
    }
    return 0;
}
