int vis[MAX], start[MAX], finish[MAX];
vector < int > edge[MAX], redge[MAX], order;
vector < vector < int > > scc;

void dfs(int u) {
    vis[u] = 1;
    start[u] = ++cnt;
    for(int v: edge[u])
        if(!vis[v]) dfs(v);
    finish[u] = ++cnt;
    order.push_back(u);
}

void dfs2(int u) {
    vis[u] = 1;
    for(int v: redge[u])
        if(!vis[v]) dfs2(u);
    scc.back().push_back(u);
}
void SCC() {
    for(int i = 1; i <= n; i++)
        if(!vis[i]) dfs(i);
    memset(vis,0,sizeof vis);
    for(int u: order)
        if(!vis[u]) scc.emplace_back(), dfs2(u);
    for(auto X: scc) {
        for(int x: X) cout << x << " ";
        cout << endl;
    }
}
