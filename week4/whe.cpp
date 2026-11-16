#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Dijkstra from intersection 1; report the smallest distance to a station and
// all stations at exactly that distance.

int main(){
    int t;
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++){
        int n, m, s;
        scanf("%d %d %d", &n, &m, &s);
        vector<vector<pair<int,int>>> adj(n + 1);
        for (int i = 0; i < m; i++){
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            adj[a].push_back({b, c});
            adj[b].push_back({a, c});
        }
        vector<int> st(s);
        for (auto &x : st) scanf("%d", &x);
        const long long INF = 1e18;
        vector<long long> dist(n + 1, INF);
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
        dist[1] = 0;
        pq.push({0, 1});
        while (!pq.empty()){
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto [v, c] : adj[u])
                if (d + c < dist[v]){
                    dist[v] = d + c;
                    pq.push({dist[v], v});
                }
        }
        long long best = INF;
        for (int x : st) best = min(best, dist[x]);
        sort(st.begin(), st.end());
        st.erase(unique(st.begin(), st.end()), st.end());
        printf("Case #%d: %lld", tc, best);
        for (int x : st) if (dist[x] == best) printf(" %d", x);
        printf("\n");
    }
}
