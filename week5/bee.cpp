#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

// Max flow with real capacities (pipe cross-section areas), pipes undirected.
// Dinic instead of Edmonds-Karp: Edmonds-Karp needs O(VE) augmentations,
// Dinic's blocking flows are far fewer and cheaper.
// Area of a regular k-gon with side x: k*x^2 / (4*tan(pi/k)); circle: pi*x^2.

typedef long double ld;
static const ld EPS = 1e-12L;

static vector<int> head, nxt, to, lvl, cur, que;
static vector<ld> cap;
static int S, T;

static void addEdge(int u, int v, ld c){
    // undirected pipe: both directions share the full capacity
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
            if (cap[e] > EPS && lvl[to[e]] < 0){
                lvl[to[e]] = lvl[u] + 1;
                if (to[e] == T) return true;
                que[qt++] = to[e];
            }
    }
    return false;
}

static ld dfs(int u, ld f){
    if (u == T) return f;
    ld sent = 0;
    for (int &e = cur[u]; e != -1; e = nxt[e]){
        int v = to[e];
        if (cap[e] > EPS && lvl[v] == lvl[u] + 1){
            ld d = dfs(v, min(f - sent, cap[e]));
            if (d > EPS){
                cap[e] -= d; cap[e ^ 1] += d;
                sent += d;
                if (f - sent <= EPS) return sent;
            }
        }
    }
    lvl[u] = -1;
    return sent;
}

int main(){
    const ld PI = acosl(-1.0L);
    int t;
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++){
        int n, m;
        scanf("%d %d", &n, &m);
        head.assign(n + 1, -1);
        to.clear(); cap.clear(); nxt.clear();
        lvl.assign(n + 1, 0); cur.assign(n + 1, 0); que.assign(n + 1, 0);
        for (int j = 0; j < m; j++){
            int a, b, k; double x;
            scanf("%d %d %d %lf", &a, &b, &k, &x);
            if (a == b) continue;
            ld area = (k == 0) ? PI * x * x : k * (ld)x * x / (4.0L * tanl(PI / k));
            addEdge(a, b, area);
        }
        S = 1; T = n;
        ld flow = 0;
        while (bfs(n + 1)){
            cur = head;
            flow += dfs(S, 1e18L);
        }
        if (flow < 1e-9L) printf("Case #%d: impossible\n", tc);
        else printf("Case #%d: %.10Lf\n", tc, flow);
    }
}
