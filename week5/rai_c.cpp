#include <bits/stdc++.h>
using namespace std;
// Railroad Network, variant C: FIFO push-relabel with gap heuristic, cin/cout.

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

// FIFO push-relabel with the gap heuristic.
template<class F> F maxflow(Net<F>& g, int s, int t, F eps){
    int n = g.n;
    if (s == t) return 0;
    vector<int> h(n, 0), cur(n, 0), cnt(2 * n + 2, 0);
    vector<F> ex(n, 0);
    vector<char> inq(n, 0);
    queue<int> q;
    h[s] = n; cnt[0] = n - 1; cnt[n] = 1;
    auto push = [&](int u, int v, F d){
        g.C(u, v) -= d; g.C(v, u) += d; ex[u] -= d; ex[v] += d;
        if (v != s && v != t && !inq[v] && ex[v] > eps){ inq[v] = 1; q.push(v); }
    };
    for (int v : g.adj[s]) if (g.C(s, v) > eps) push(s, v, g.C(s, v));
    while (!q.empty()){
        int u = q.front(); q.pop(); inq[u] = 0;
        while (ex[u] > eps){
            if (cur[u] == (int)g.adj[u].size()){
                int mn = 2 * n;
                for (int v : g.adj[u]) if (g.C(u, v) > eps) mn = min(mn, h[v] + 1);
                int old = h[u];
                cnt[old]--;
                h[u] = min(mn, 2 * n);
                cnt[h[u]]++;
                cur[u] = 0;
                if (cnt[old] == 0 && old < n){
                    for (int w = 0; w < n; w++)
                        if (w != s && h[w] > old && h[w] < n + 1){
                            cnt[h[w]]--; h[w] = n + 1; cnt[h[w]]++;
                        }
                }
                if (h[u] >= 2 * n) break; // cannot push anywhere (numerical corner)
            } else {
                int v = g.adj[u][cur[u]];
                if (g.C(u, v) > eps && h[u] == h[v] + 1) push(u, v, min(ex[u], g.C(u, v)));
                else cur[u]++;
            }
        }
    }
    return ex[t];
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
