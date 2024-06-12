#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

struct UnionFind{
    vector<int> parent;

    void init(int n){
        parent = vector<int>(n+1, -1);
    }

    int Find(int x){
        return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
    }

    bool Union(int x, int y){
        x = Find(x), y = Find(y);
        if(x == y) return false;
        parent[x] += parent[y];
        parent[y] = x;
        return true;
    }
};

struct BCC{
    vector<int> dfn;
    vector<vector<pii>> adj;
    vector<tuple<int, int, int>> edge;
    vector<vector<int>> bcc;
    UnionFind UF;
    int n, id;

    void init(int _n){
        n = _n;
        id = 0;
        adj.clear();
        adj.resize(n+1);
        dfn.clear();
        dfn.resize(n+1);
        UF.init(n);
    }

    void addEdge(int u, int v, int idx){
        adj[u].push_back({v, idx});
        adj[v].push_back({u, idx});
    }

    int dfs(int prevIdx, int cur){
        int ret = dfn[cur] = ++id;
        for(auto [next, idx]: adj[cur]){
            if(idx == prevIdx) continue;
            if(!dfn[next]){
                int low = dfs(cur, next);
                if(low > dfn[cur]) edge.push_back({cur, next, idx});
                else UF.Union(cur, next);
                ret = min(ret, low);
            }
            else ret = min(ret, dfn[next]);
        }
        return ret;
    }

    void get_bcc(){
        for(int i=1; i<=n; i++){
            if(!dfn[i]) dfs(-1, i);
        }
        bcc.clear();
        bcc.resize(n+1);
        for(auto [u, v, idx]: edge){
            u = UF.Find(u);
            v = UF.Find(v);
            bcc[u].push_back(v);
            bcc[v].push_back(u);
        }
    }
}bcc;