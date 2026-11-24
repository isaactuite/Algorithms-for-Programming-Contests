#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

// Minimum vertex cut between 1 and n = max flow in the split graph:
// every vertex v becomes v_in -> v_out with capacity 1 (infinite for 1 and n),
// every connection a-b becomes a_out -> b_in and b_out -> a_in (infinite).
// Duplicate connections are dropped with a bit matrix (n <= 400), and Dinic
// runs on flat forward-star arrays. Input is read in one fread.

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
    to.push_back(u); cap.push_back(0); nxt.push_back(head[v]); head[v] = to.size() - 1;
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
    lvl[u] = -1; // dead end
    return sent;
}

int main(){
    size_t cap_ = 1 << 20, len = 0;
    buf = (char*)malloc(cap_);
    while (true){
        size_t r = fread(buf + len, 1, cap_ - len - 1, stdin);
        len += r;
        if (len + 1 < cap_) break;
        cap_ *= 2; buf = (char*)realloc(buf, cap_);
    }
    buf[len] = 0;

    int t = readInt();
    static bool adjm[401][401];
    for (int tc = 1; tc <= t; tc++){
        int n = readInt(), m = readInt();
        for (int i = 1; i <= n; i++) memset(adjm[i], 0, n + 1);
        for (int j = 0; j < m; j++){
            int a = readInt(), b = readInt();
            adjm[a][b] = adjm[b][a] = true;
        }
        int V = 2 * n + 2;
        head.assign(V, -1);
        to.clear(); cap.clear(); nxt.clear();
        lvl.assign(V, 0); cur.assign(V, 0); que.assign(V, 0);
        // in(v) = v-1, out(v) = n + v - 1
        for (int v = 1; v <= n; v++)
            addEdge(v - 1, n + v - 1, (v == 1 || v == n) ? INF : 1);
        for (int a = 1; a <= n; a++)
            for (int b = 1; b <= n; b++)
                if (adjm[a][b]) addEdge(n + a - 1, b - 1, INF);
        S = n; T = n - 1;
        int flow = 0;
        while (bfs(V)){
            cur = head;
            flow += dfs(S, INF);
        }
        printf("Case #%d: %d\n", tc, flow);
    }
}
