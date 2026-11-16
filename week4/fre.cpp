#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// System of difference constraints, solved with Bellman-Ford (feasible iff no
// negative cycle). Each dish has a time t_v.
//   SIM A B T:  |tA - tB| <= T   ->  tA - tB <= T and tB - tA <= T
//   BEF A B T:  tB - tA >= T     ->  tA - tB <= -T
//   meal length <= K: add a virtual start t0 with t0 <= t_v <= t0 + K.
// Constraint x - y <= c becomes an edge y -> x of weight c.

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    cin >> N >> K;
    map<string,int> id;
    auto get = [&](const string &s){
        auto it = id.find(s);
        if (it != id.end()) return it->second;
        int v = id.size() + 1; // node 0 is the virtual start
        id[s] = v;
        return v;
    };
    struct Edge { int u, v, w; };
    vector<Edge> edges;
    for (int i = 0; i < N; i++){
        string type, A, B;
        int T;
        cin >> type >> A >> B >> T;
        int a = get(A), b = get(B);
        if (type == "SIM"){
            edges.push_back({b, a, T});
            edges.push_back({a, b, T});
        } else {
            edges.push_back({b, a, -T});
        }
    }
    int V = id.size() + 1;
    for (int v = 1; v < V; v++){
        edges.push_back({v, 0, 0});  // t0 - tv <= 0
        edges.push_back({0, v, K});  // tv - t0 <= K
    }
    vector<long long> dist(V, 0);
    bool changed = true;
    for (int it = 0; it < V && changed; it++){
        changed = false;
        for (auto &e : edges)
            if (dist[e.u] + e.w < dist[e.v]){
                dist[e.v] = dist[e.u] + e.w;
                changed = true;
            }
    }
    cout << (changed ? "NO" : "YES") << endl;
}
