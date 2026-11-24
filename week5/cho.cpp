#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

// Max flow from a super source (all fountains) to a super sink (all wrapping
// stations) with undirected belts. Dinic on flat arrays with a dead-end
// pruning step; parallel belts are merged first so the graph stays small.

static char *buf; static size_t bp = 0;
static inline int readInt(){
    while (buf[bp] < '0') bp++;
    int x = 0;
    while (buf[bp] >= '0') x = x * 10 + (buf[bp++] - '0');
    return x;
}

static const int INF = 1e9;
static vector<int> head, nxt, to, cap, lvl, cur, que;
static int S, T;

static inline void addEdge(int u, int v, int c, int rc){
    to.push_back(v); cap.push_back(c); nxt.push_back(head[u]); head[u] = to.size() - 1;
    to.push_back(u); cap.push_back(rc); nxt.push_back(head[v]); head[v] = to.size() - 1;
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
    size_t sz = 1 << 20, len = 0;
    buf = (char*)malloc(sz);
    while (true){
        len += fread(buf + len, 1, sz - len - 1, stdin);
        if (len + 1 < sz) break;
        sz *= 2; buf = (char*)realloc(buf, sz);
    }
    buf[len] = 0;

    int t = readInt();
    for (int tc = 1; tc <= t; tc++){
        int n = readInt(), k = readInt(), m = readInt(), l = readInt();
        int tot = n + k + m;
        S = 0; T = tot + 1;
        int V = tot + 2;

        // merge parallel belts: key = (min,max) -> summed capacity
        vector<long long> keys; keys.reserve(l);
        vector<int> cs; cs.reserve(l);
        vector<pair<long long,int>> es; es.reserve(l);
        for (int j = 0; j < l; j++){
            int a = readInt(), b = readInt(), c = readInt();
            if (a == b) continue;
            if (a > b) swap(a, b);
            es.push_back({(long long)a * V + b, c});
        }
        sort(es.begin(), es.end());

        head.assign(V, -1);
        to.clear(); cap.clear(); nxt.clear();
        lvl.assign(V, 0); cur.assign(V, 0); que.assign(V, 0);
        for (size_t i = 0; i < es.size();){
            size_t j = i; int c = 0;
            while (j < es.size() && es[j].first == es[i].first) c += es[j++].second;
            addEdge((int)(es[i].first / V), (int)(es[i].first % V), c, c);
            i = j;
        }
        for (int s = 1; s <= n; s++) addEdge(S, s, INF, 0);
        for (int w = n + k + 1; w <= tot; w++) addEdge(w, T, INF, 0);

        long long flow = 0;
        while (bfs(V)){
            cur = head;
            flow += dfs(S, INF);
        }
        printf("Case #%d: %lld\n", tc, flow);
    }
}
