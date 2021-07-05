/// RM vai implementation

// Works only on directed Graph
// *** 1 based indexing
#define MAXN    205
#define MAXE    100000
#define LL long long
const int INF = 0x7f7f7f7f;

struct MCMF{
    int src, snk, nNode, nEdge;
    int fin[MAXN + 5], pre[MAXN + 5], dist[MAXN + 5];
    int cap[2*MAXE+5], cost[2*MAXE+5], Next[2*MAXE+5], to[2*MAXE+5], from[2*MAXE+5];
    bool inqueue[MAXN+5];

    MCMF(int nodes,int _src, int _snk) {
        memset(fin, -1, sizeof(fin));
        nNode = nodes, nEdge = 0;
        src = _src, snk = _snk;
    }

    void addEdge(int u, int v, int _cost, int _cap) {
        from[nEdge] = u, to[nEdge] = v, cap[nEdge] = _cap, cost[nEdge] = _cost;
        Next[nEdge] = fin[u], fin[u] = nEdge++;
        from[nEdge] = v, to[nEdge] = u, cap[nEdge] = 0, cost[nEdge] = -(_cost);
        Next[nEdge] = fin[v], fin[v] = nEdge++;
        assert(nEdge <= 2*MAXE);
    }

    bool bellman() {
        int u, v, i;
        memset(dist, 0x7f, sizeof(dist));
        memset(pre, -1, sizeof(pre));
        memset(inqueue, false, sizeof(inqueue));

        dist[src] = 0;
        queue<int> q;
        q.push(src);
        inqueue[src] = true;

        while(!q.empty()) {
            u = q.front();
            q.pop();
            inqueue[u] = false;

            for(i = fin[u]; i >= 0; i = Next[i]) {
                v = to[i];
                if(cap[i] && dist[v] > dist[u] + cost[i]) {
                    dist[v] = dist[u] + cost[i];
                    pre[v] = i;
                    if(inqueue[v] == false) {
                        q.push(v);
                        inqueue[v] = true;
                    }
                }
            }
        }
        return (dist[snk] < INF);
    }

    pair<int,int> minCostMaxFlow(LL fcost) {
        int netflow, bot, u;
        netflow = fcost = 0;
        while(bellman()) {
            bot = INF;
            for(u = pre[snk]; u >= 0; u = pre[from[u]]) bot = min(bot, cap[u]);
            for(u = pre[snk]; u >= 0; u = pre[from[u]]) {
                cap[u] -= bot;
                cap[u^1] += bot;
                fcost += (LL) bot * cost[u];
            }
            netflow += bot;
        }
        return {netflow, fcost};
    }
};
/// End MCMF with SPFA
