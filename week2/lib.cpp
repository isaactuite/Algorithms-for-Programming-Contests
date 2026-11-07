#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// BFS from every package to keep along dependency edges; if any reached
// package is marked for removal there is a conflict.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++){
        int N, K, R, D;
        cin >> N >> K >> R >> D;

        vector<int> keep(K);
        for (int i = 0; i < K; i++) cin >> keep[i];

        vector<bool> removed(N + 1, false);
        for (int i = 0; i < R; i++){
            int r;
            cin >> r;
            removed[r] = true;
        }

        vector<vector<int>> deps(N + 1);
        for (int i = 0; i < D; i++){
            int u, d;
            cin >> u >> d;
            deps[u].push_back(d);
        }

        vector<bool> visited(N + 1, false);
        queue<int> q;
        for (int k : keep){
            if (!visited[k]){
                visited[k] = true;
                q.push(k);
            }
        }

        bool conflict = false;
        while (!q.empty() && !conflict){
            int curr = q.front();
            q.pop();
            if (removed[curr]){
                conflict = true;
                break;
            }
            for (int d : deps[curr]){
                if (!visited[d]){
                    visited[d] = true;
                    q.push(d);
                }
            }
        }

        cout << "Case #" << tc << ": " << (conflict ? "conflict" : "ok") << "\n";
    }
}
