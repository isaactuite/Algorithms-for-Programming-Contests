#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

// Max flow from city 1 to city n over undirected connections. Dinic on flat
// arrays with fast input and dead-end pruning.

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
        int n = readInt(), m = readInt();
        head.assign(n + 1, -1);
        to.clear(); cap.clear(); nxt.clear();
        lvl.assign(n + 1, 0); cur.assign(n + 1, 0); que.assign(n + 1, 0);
        for (int j = 0; j < m; j++){
            int a = readInt(), b = readInt(), w = readInt();
            if (a != b) addEdge(a, b, w);
        }
        S = 1; T = n;
        long long flow = 0;
        while (bfs(n + 1)){
            cur = head;
            flow += dfs(S, INF);
        }
        if (flow == 0) printf("Case #%d: impossible\n", tc);
        else printf("Case #%d: %lld\n", tc, flow);
    }
}
