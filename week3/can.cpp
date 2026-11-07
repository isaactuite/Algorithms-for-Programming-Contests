#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int w = 0; w<t; w++){
        int n;
        cin >> n;

        vector<vector<int>> adj(n + 1);
        vector<int> deg(n + 1, 0);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[u]++; deg[v]++;
        }

        if (n == 1) {
            cout << "Case #" << w+1 << " " << 1 << endl;
            continue;
        }

        vector<int> leaves;

        for (int i = 1; i <= n; i++){
            if (deg[i] == 1) {
                leaves.push_back(i);
            }
        }

        int remaining = n;
        int rounds = 0;

        while (remaining > 2) {

            remaining -= leaves.size();

            vector<int> next;
            for (int leaf : leaves) {
                for (int nb : adj[leaf]) {
                    if (--deg[nb] == 1){
                        next.push_back(nb);
                    }
                }
            }

            leaves = next;
            rounds++;
        }

        int center = leaves[0];

        for (int c : leaves){
            center = min(center, c);
        }

        cout << "Case #" <<w+1<< ": " <<center<<endl;
    }
}