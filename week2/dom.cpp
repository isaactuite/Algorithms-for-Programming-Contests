#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Answer = number of strongly connected components with no incoming edge
// from another component (Tarjan's SCC, iterative to avoid deep recursion).
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c;
    cin >> c;

    for (int t = 0; t < c; t++){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> graph(n + 1);
        vector<pair<int, int>> edges;
        for (int i = 0; i < m; i++){
            int d1, d2;
            cin >> d1 >> d2;
            graph[d1].push_back(d2);
            edges.push_back({d1, d2});
        }

        vector<int> index(n + 1, -1), low(n + 1, 0), comp(n + 1, -1);
        vector<bool> on_stack(n + 1, false);
        stack<int> st;
        int counter = 0, num_comps = 0;

        for (int s = 1; s <= n; s++){
            if (index[s] != -1) continue;
            // call stack of (node, next neighbour position)
            vector<pair<int, int>> call;
            call.push_back({s, 0});
            index[s] = low[s] = counter++;
            st.push(s);
            on_stack[s] = true;

            while (!call.empty()){
                int v = call.back().first;
                int& pos = call.back().second;
                if (pos < (int)graph[v].size()){
                    int w = graph[v][pos++];
                    if (index[w] == -1){
                        index[w] = low[w] = counter++;
                        st.push(w);
                        on_stack[w] = true;
                        call.push_back({w, 0});
                    } else if (on_stack[w]){
                        low[v] = min(low[v], index[w]);
                    }
                } else {
                    if (low[v] == index[v]){
                        while (true){
                            int w = st.top();
                            st.pop();
                            on_stack[w] = false;
                            comp[w] = num_comps;
                            if (w == v) break;
                        }
                        num_comps++;
                    }
                    call.pop_back();
                    if (!call.empty()){
                        int parent = call.back().first;
                        low[parent] = min(low[parent], low[v]);
                    }
                }
            }
        }

        vector<bool> has_incoming(num_comps, false);
        for (auto& [a, b] : edges){
            if (comp[a] != comp[b]) has_incoming[comp[b]] = true;
        }
        int knocks = 0;
        for (int i = 0; i < num_comps; i++){
            if (!has_incoming[i]) knocks++;
        }
        cout << knocks << "\n";
    }
}
