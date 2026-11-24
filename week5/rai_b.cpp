#include <bits/stdc++.h>
using namespace std;
// Railroad Network, variant B: Dinic on a merged capacity matrix, cin/cout.

// Capacity-matrix flow: parallel edges are merged into one matrix entry and
// each vertex keeps a list of distinct neighbours.
template<class F> struct Net {
    int n; vector<F> c; vector<vector<int>> adj; vector<char> has;
    Net(int n_) : n(n_), c((size_t)n_ * n_, 0), adj(n_), has((size_t)n_ * n_, 0) {}
    F& C(int u, int v){ return c[(size_t)u * n + v]; }
    // undirected pipe/rail
    void add(int u, int v, F w){
        if (u == v) return;
        C(u, v) += w; C(v, u) += w;
        if (!has[(size_t)u * n + v]){
            has[(size_t)u * n + v] = has[(size_t)v * n + u] = 1;
            adj[u].push_back(v); adj[v].push_back(u);
        }
    }
};

template<class F> F maxflow(Net<F>& g, int s, int t, F eps){
    int n = g.n;
    if (s == t) return 0;
    vector<int> lvl(n), cur(n), q(n);
    F flow = 0;
    function<F(int,F)> dfs = [&](int u, F f) -> F {
        if (u == t) return f;
        F sent = 0;
        for (int &i = cur[u]; i < (int)g.adj[u].size(); i++){
            int v = g.adj[u][i];
            if (g.C(u, v) > eps && lvl[v] == lvl[u] + 1){
                F d = dfs(v, min(f - sent, g.C(u, v)));
                if (d > eps){
                    g.C(u, v) -= d; g.C(v, u) += d; sent += d;
                    if (f - sent <= eps) return sent;
                }
            }
        }
        lvl[u] = -1;
        return sent;
    };
    while (true){
        fill(lvl.begin(), lvl.end(), -1);
        int qh = 0, qt = 0; q[qt++] = s; lvl[s] = 0;
        while (qh < qt){
            int u = q[qh++];
            for (int v : g.adj[u])
                if (g.C(u, v) > eps && lvl[v] < 0){ lvl[v] = lvl[u] + 1; q[qt++] = v; }
        }
        if (lvl[t] < 0) break;
        fill(cur.begin(), cur.end(), 0);
        flow += dfs(s, numeric_limits<F>::max() / 4);
    }
    return flow;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; if (!(cin >> t)) return 0;
    for (int tc = 1; tc <= t; tc++){
        int n, m; if (!(cin >> n >> m)) break;
        Net<long long> g(n + 1);
        for (int j = 0; j < m; j++){
            int a, b, w; cin >> a >> b >> w;
            if (a >= 1 && a <= n && b >= 1 && b <= n) g.add(a, b, w);
        }
        long long f = maxflow<long long>(g, 1, n, 0);
        if (f == 0) cout << "Case #" << tc << ": impossible\n";
        else cout << "Case #" << tc << ": " << f << "\n";
    }
}
