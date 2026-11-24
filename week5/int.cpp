#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// 1. Dijkstra over star systems with Euclidean distances (the shortest path is
//    unique, so floating point is safe) gives the route from system 1 to N.
// 2. Each hop of the route carries at most the squared distance.
// 3. Inside each system on the route, the cargo goes from the arrival colony
//    ((i-1)n+1) to the departure colony (i*n); that capacity is a max flow
//    (Dinic) on the system's colonies. With n = 1 the two coincide: unlimited.
// The answer is the minimum over all hop capacities and system flows; 0 means
// impossible. Intrastellar edges are read for every system, but a flow is only
// computed for systems on the route. Input is read with a single fread.

static char *buf; static size_t bp = 0;
static inline int readInt(){
    while (buf[bp] != '-' && buf[bp] < '0') bp++;
    bool neg = false;
    if (buf[bp] == '-'){ neg = true; bp++; }
    int x = 0;
    while (buf[bp] >= '0') x = x * 10 + (buf[bp++] - '0');
    return neg ? -x : x;
}

static const int INF = 1e9;
static vector<int> head, nxt, to, cap, lvl, cur, que;
static int S, T;

static inline void addEdge(int u, int v, int c){
    to.push_back(v); cap.push_back(c); nxt.push_back(head[u]); head[u] = to.size() - 1;
    to.push_back(u); cap.push_back(c); nxt.push_back(head[v]); head[v] = to.size() - 1;
}

static bool bfs(int V){
    fill(lvl.begin(), lvl.begin() + V, -1);
    int qh = 0, qt = 0;
    que[qt++] = S; lvl[S] = 0;
    while (qh < qt){
        int u = que[qh++];
        for (int e = head[u]; e != -1; e = nxt[e])
            if (cap[e] > 0 && lvl[to[e]] < 0){
                lvl[to[e]] = lvl[u] + 1;
                if (to[e] == T) return true;
                que[qt++] = to[e];
            }
    }
    return false;
}

static int dfs(int u, int f){
    if (u == T) return f;
    int sent = 0;
    for (int &e = cur[u]; e != -1; e = nxt[e]){
        int v = to[e];
        if (cap[e] > 0 && lvl[v] == lvl[u] + 1){
            int d = dfs(v, min(f - sent, cap[e]));
            if (d > 0){
                cap[e] -= d; cap[e ^ 1] += d;
                sent += d;
                if (sent == f) return sent;
            }
        }
    }
    lvl[u] = -1;
    return sent;
}

int main(){
    size_t sz = 1 << 22, len = 0;
    buf = (char*)malloc(sz);
    while (true){
        len += fread(buf + len, 1, sz - len - 1, stdin);
        if (len + 1 < sz) break;
        sz *= 2; buf = (char*)realloc(buf, sz);
    }
    buf[len] = 0;

    int t = readInt();
    for (int tc = 1; tc <= t; tc++){
        int N = readInt(), M = readInt(), n = readInt(), m = readInt();
        vector<long long> X(N), Y(N), Z(N);
        for (int i = 0; i < N; i++){ X[i] = readInt(); Y[i] = readInt(); Z[i] = readInt(); }
        vector<vector<int>> adj(N);
        for (int j = 0; j < M; j++){
            int a = readInt() - 1, b = readInt() - 1;
            adj[a].push_back(b);
        }
        // intrastellar edges: system i owns lines [i*m, (i+1)*m)
        vector<int> eu((size_t)m * N), ev((size_t)m * N), ec((size_t)m * N);
        for (size_t j = 0; j < (size_t)m * N; j++){
            eu[j] = readInt(); ev[j] = readInt(); ec[j] = readInt();
        }

        auto sq = [&](int a, int b){
            long long dx = X[a] - X[b], dy = Y[a] - Y[b], dz = Z[a] - Z[b];
            return dx * dx + dy * dy + dz * dz;
        };

        // Dijkstra with Euclidean distance
        vector<double> dist(N, 1e300);
        vector<int> par(N, -1);
        priority_queue<pair<double,int>, vector<pair<double,int>>, greater<>> pq;
        dist[0] = 0; pq.push({0, 0});
        while (!pq.empty()){
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (int v : adj[u]){
                double nd = d + sqrt((double)sq(u, v));
                if (nd < dist[v]){ dist[v] = nd; par[v] = u; pq.push({nd, v}); }
            }
        }
        if (dist[N - 1] >= 1e299){ printf("Case #%d: impossible\n", tc); continue; }

        vector<int> path;
        for (int v = N - 1; v != -1; v = par[v]) path.push_back(v);
        reverse(path.begin(), path.end());

        long long ans = (long long)4e18;
        for (size_t i = 0; i + 1 < path.size(); i++)
            ans = min(ans, sq(path[i], path[i + 1]));

        if (n > 1){
            for (int sys : path){
                if (ans == 0) break;
                int V = n + 1; // colonies 1..n of this system (local ids)
                head.assign(V, -1);
                to.clear(); cap.clear(); nxt.clear();
                lvl.assign(V, 0); cur.assign(V, 0); que.assign(V, 0);
                int base = sys * n;
                for (int j = 0; j < m; j++){
                    size_t id = (size_t)sys * m + j;
                    int a = eu[id] - base, b = ev[id] - base;
                    if (a != b) addEdge(a, b, ec[id]);
                }
                S = 1; T = n;
                long long flow = 0;
                while (bfs(V)){
                    cur = head;
                    flow += dfs(S, INF);
                }
                ans = min(ans, flow);
            }
        }

        if (ans <= 0) printf("Case #%d: impossible\n", tc);
        else printf("Case #%d: %lld\n", tc, ans);
    }
}
