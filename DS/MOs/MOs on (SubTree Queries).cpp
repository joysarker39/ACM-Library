#include<bits/stdc++.h>
using namespace std;
#define D(x) cerr<<__LINE__<<" : "<<#x<<" -> "<<x<<endl

const int MAX = 2e5+7;            ///Check Every Time
int t=1, n, m, l, k, tc, q;
vector < int > edge[MAX];
int w[MAX], euler[MAX*2], tin[MAX], tout[MAX];
int arr[MAX + 5], blkId[MAX];
int Time = 0;

void dfs(int u, int par){
    tin[u] = Time;
    euler[Time++] = u;
    for(int v: edge[u])
        if(v != par) dfs(v,u);
    tout[u] = Time;
    euler[Time++] = u;
}

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
        freq[euler[idx]]++;
        if(freq[euler[idx]] == 2) unique_values++;
    }

    void del(int idx) {
        freq[euler[idx]]--;
        if(freq[euler[idx]] == 1) unique_values--;
    }
    void add_query(int Q) {
        for(int i = 0; i < Q; i++) {
            int node ;
            scanf("%d",&node); ///subtree of this node
            node--;
            queries[i].l = tin[node];
            queries[i].r = tout[node];
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
            perQ[queries[i].id] = unique_values; ///this means size of subtree
        }
    }
};


signed main(){
    while(t--){
        scanf("%d%d",&n,&q);
        for(int i = 1; i < n ;i++){
            int u, v;
            scanf("%d%d",&u,&v);
            u--, v--;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        dfs(0,-1);
        MO mos(Time);
        mos.add_query(q);
        mos.process_query(q);
        for(int i = 0; i < q;i++)
            cout << mos.perQ[i] << "\n";
    }
    return 0;
}

