#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Lea goes a -> supermarket c -> b, so the answer is
// min over supermarkets of dist(a,c) + w + dist(c,b). Two Dijkstra runs
// (from a and from b; roads are undirected).

typedef vector<vector<pair<int,int>>> Graph;
const long long INF = 1e18;

vector<long long> dijkstra(const Graph &g, int src){
    vector<long long> dist(g.size(), INF);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, c] : g[u])
            if (d + c < dist[v]){
                dist[v] = d + c;
                pq.push({dist[v], v});
            }
    }
    return dist;
}

int main(){
    int t;
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++){
        int n, m, s, a, b;
        scanf("%d %d %d %d %d", &n, &m, &s, &a, &b);
        Graph g(n + 1);
        for (int i = 0; i < m; i++){
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            g[x].push_back({y, z});
            g[y].push_back({x, z});
        }
        auto da = dijkstra(g, a), db = dijkstra(g, b);
        long long best = INF;
        for (int j = 0; j < s; j++){
            int c, w;
            scanf("%d %d", &c, &w);
            if (da[c] < INF && db[c] < INF) best = min(best, da[c] + w + db[c]);
        }
        if (best >= INF) printf("Case #%d: impossible\n", tc);
        else printf("Case #%d: %lld:%02lld\n", tc, best / 60, best % 60);
    }
}
