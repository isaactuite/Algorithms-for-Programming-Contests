#include <bits/stdc++.h>
using namespace std;
// Railroad Network, variant D: capacity scaling augmenting paths, scanf/printf.

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

// Capacity scaling: only augment along paths whose edges all have residual >= delta.
template<class F> F maxflow(Net<F>& g, int s, int t, F eps){
    int n = g.n;
    if (s == t) return 0;
    F mx = 0;
    for (F x : g.c) mx = max(mx, x);
    F flow = 0;
    vector<int> par(n), q(n);
    F delta = 1;
    while (delta * 2 <= mx) delta *= 2;
    for (; delta >= 1; delta /= 2){
        while (true){
            fill(par.begin(), par.end(), -1);
            int qh = 0, qt = 0; q[qt++] = s; par[s] = s;
            while (qh < qt && par[t] < 0){
                int u = q[qh++];
                for (int v : g.adj[u])
                    if (par[v] < 0 && g.C(u, v) >= delta){ par[v] = u; q[qt++] = v; }
            }
            if (par[t] < 0) break;
            F d = numeric_limits<F>::max();
            for (int v = t; v != s; v = par[v]) d = min(d, g.C(par[v], v));
            for (int v = t; v != s; v = par[v]){ g.C(par[v], v) -= d; g.C(v, par[v]) += d; }
            flow += d;
        }
    }
    return flow;
}

int main(){
    int t; if (scanf("%d", &t) != 1) return 0;
    for (int tc = 1; tc <= t; tc++){
        int n, m; if (scanf("%d %d", &n, &m) != 2) break;
        Net<long long> g(n + 1);
        for (int j = 0; j < m; j++){
            int a, b, w; if (scanf("%d %d %d", &a, &b, &w) != 3) break;
            if (a >= 1 && a <= n && b >= 1 && b <= n) g.add(a, b, w);
        }
        long long f = maxflow<long long>(g, 1, n, 0);
        if (f == 0) printf("Case #%d: impossible\n", tc);
        else printf("Case #%d: %lld\n", tc, f);
    }
}
