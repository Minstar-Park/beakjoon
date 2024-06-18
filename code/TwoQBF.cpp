#include <bits/stdc++.h>
using namespace std;

struct strongly_connected{
    vector<vector<int>> adj, comp, dag;
    vector<int> dfn, sccId;
    int pv, scc_cnt;
    stack<int> st;
    
    strongly_connected(int _n): adj(_n+1) {}
    
    void addEdge(int u, int v){
        adj[u].push_back(v);
    }
    
    int dfs(int cur){
        int ret = dfn[cur] = ++pv;
        st.push(cur);
        for(auto next: adj[cur]){
            if(dfn[next] == -1) ret = min(ret, dfs(next));
            else if(sccId[next] == -1) ret = min(ret, dfn[next]);
        }
        if(ret == dfn[cur]){
            vector<int> tmp;
            while(1){
                int t = st.top(); st.pop();
                sccId[t] = scc_cnt;
                tmp.push_back(t);
                if(t == cur) break;
            }
            comp.push_back(tmp);
            scc_cnt++;
        }
        return ret;
    }

    void get_scc(int n){
        dfn = vector<int>(n+1, -1);
        sccId = vector<int>(n+1, -1);
        pv = scc_cnt = 0;
        for(int i=1; i<=n; i++){
            if(dfn[i] == -1) dfs(i);
        }
        dag = vector<vector<int>>(scc_cnt);
        for(int i=1; i<=n; i++){
            for(auto next: adj[i]){
                if(sccId[i] != sccId[next]){
                    dag[sccId[i]].push_back(sccId[next]);
                }
            }
        }
    }
};

struct TwoSat{
    strongly_connected scc;
    int n;
    vector<int> res;

    TwoSat(int _n): n(_n), scc(_n*2+1) {}
    
    int Not(int x) {return x > n ? x - n : x + n;}

    void addEdge(int u, int v){
        if(u < 0) u = n - u;
        if(v < 0) v = n - v;
        scc.addEdge(Not(u), v);
        scc.addEdge(Not(v), u);
    }

    bool satisfy(){
        scc.get_scc(n*2);
        res = vector<int>(n+1);
        for(int i=1; i<=n; i++){
            if(scc.sccId[i] == scc.sccId[Not(i)]){
                return false;
            }
        }
        for(int i=1; i<=n; i++){
            res[i] = (scc.sccId[i] < scc.sccId[Not(i)]);
        }
        return true;
    }
};

struct TwoQbf{
    int n;
    TwoSat twosat;
    string str;
    vector<int> res;
    TwoQbf(int _n, TwoSat _twosat, string _str): n(_n), twosat(_twosat), str(_str) {}

    bool satisfy(){
        if(!twosat.satisfy()) return false;
        int scc_cnt = twosat.scc.scc_cnt;
        vector<int> has(scc_cnt, -1), from(scc_cnt), to(scc_cnt);
        for(int i=n; i>=1; i--){
            if(has[twosat.scc.sccId[i]] != -1 || has[twosat.scc.sccId[twosat.Not(i)]] != -1){
                return false;
            }
            if(str[i-1] == 'A'){
                has[twosat.scc.sccId[i]] = i;
                has[twosat.scc.sccId[twosat.Not(i)]] = i + n;
            }
        }
        for(int i=0; i<scc_cnt; i++){
            if(has[i] != -1) from[i] = to[i] = 1;
        }
        for(int i=0; i<scc_cnt; i++){
            bool reach = false;
            for(auto next: twosat.scc.dag[i]) reach |= to[next];
            if(reach && to[i]){
                return false;
            }
            to[i] |= reach;
        }
        for(int i=scc_cnt-1; i>=0; i--){
            for(auto next: twosat.scc.dag[i]){
                from[next] |= from[i];
            }
        }
        for(int i=0; i<scc_cnt; i++){
            if(has[i]!=-1){
                for(auto v: twosat.scc.comp[i]){
                    if(v > n) res[v-n] = (has[i] > n ? 1 : 0);
                    else res[v] = (has[i] <= n ? 1 : 0);
                }
            }
            else if(from[i]){
                for(auto v: twosat.scc.comp[i]){
                    if(v > n) res[v-n] = 0;
                    else res[v] = 1;
                }
            }
            else if(to[i]){
                for(auto v: twosat.scc.comp[i]){
                    if(v > n) res[v-n] =1;
                    else res[v] = 0;
                }
            }
        }
        for(int i=1; i<=n; i++){
            if(res[i] == -1) res[i] = (twosat.scc.sccId[i+n] < twosat.scc.sccId[i]);
        }
        return true;
    }
};