#include<bits/stdc++.h>
using namespace std;
#define D(x) cout<<__LINE__<<" : "<<#x<<" = "<<x<<endl


// bipartite matching using dfs [ 1 indexing ]

int Left[MAX+10], Right[MAX+10];
bool vis[MAX+10];
vector<int> edge[MAX+10]; // Left side Graph

bool dfs(int idx)
{
    if(vis[idx]) return false;
    vis[idx] = 1;

    int i, nw, len = edge[idx].size();
    for(i = 0; i < len; i++)
    {
        nw = edge[idx][i];
        if(Right[nw] == -1)
        {
            Right[nw] = idx;
            Left[idx] = nw;
            return true;
        }
    }

    for(i = 0; i < len; i++)
    {
        nw = edge[idx][i];
        if(dfs(Right[nw]))
        {
            Left[idx] = nw;
            Right[nw] = idx;
            return true;
        }
    }

    return false;
}

int match(int can) // can = cardinality of left half
{
    int i, ret = 0;
    bool done;

    memset(Left, -1, sizeof(Left));
    memset(Right, -1, sizeof(Right));
    do{
        done = true;
        memset(vis, false, sizeof(vis));
        for(i = 1; i <= can; i++)
            if(Left[i] == -1 && dfs(i))
                done = false;
    }while(!done);

    for(i = 1; i <= can; i++) ret += (Left[i] != -1);
    return ret;
}


int n, m, x, y;

int main()
{
    cin>>n>>m;
    while(m--){
        cin>>x>>y;
        edge[x].push_back(y);
    }
    int _match = match(n);
    cout<<_match<<endl;
    return 0;
}
