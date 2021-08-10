struct SCC {
    int vis[MAX], start[MAX], finish[MAX], root[MAX];
    vector < int > edge[MAX], redge[MAX], order;
    vector < vector < int > > component;
    vector < int > conEdge[MAX];
    int node, noScc = 0;
    SCC(int _node = 0) {
        node = _node;
    }
    void add_edge(int u, int v) {
        edge[u].push_back(v);
        redge[v].push_back(u);
    }
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
            if(!vis[v]) dfs2(v);
        component.back().push_back(u);
    }

    void scc() {
        memset(vis,0,sizeof vis);
        for(int i = 1; i <= node; i++)
            if(!vis[i]) dfs(i);
        memset(vis,0,sizeof vis);
        reverse(order.begin(),order.end());
        for(int u: order)
            if(!vis[u]) {
                noScc++;
                component.emplace_back();
                dfs2(u);
                for(int x: component.back())
                    root[x] = component.size();
            }
        for(int u = 1; u <= node; u++) {
            for(int v: edge[u]) {
                if(root[u] != root[v])
                    conEdge[root[u]].push_back(root[v]);
            }
        }
    }
    void show() {
        puts("Edge :");
        for(int i = 1; i <= node; i++) {
            cout <<"from "<<i<<" -> ";
            for(int x: edge[i]) cout << x <<" ";
            cout << endl;
        }
        puts("\nrEdge:");
        for(int i = 1; i <= node; i++) {
            cout <<"from "<<i<<" -> ";
            for(int x: redge[i]) cout << x <<" ";
            cout << endl;
        }
        cout << "\ntotal components:" << noScc <<"\n";
        for(auto X: component) {
            cout <<"from "<<X.back()<<" -> ";
            for(int x: X) cout << x <<" ";
            cout << endl;
        }
        puts("\nCondensation Graph Edge");
        for(int i = 1; i<=noScc; i++) {
            cout <<"from components :"<<i<<" -> ";
            for(int x: conEdge[i]) cout << x <<" ";
            cout<<endl;
        }
    }
};
