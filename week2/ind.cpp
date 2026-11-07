#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Kahn's algorithm: a cycle means "recheck hints"; if the queue ever holds
// more than one node the order is not unique, so "missing hints".
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++){
        int n, h;
        cin >> n >> h;
        vector<vector<int>> graph(n + 1);
        vector<int> in_degree(n + 1, 0);
        for (int i = 0; i < h; i++){
            int a, b;
            cin >> a >> b;
            graph[a].push_back(b);
            in_degree[b]++;
        }

        queue<int> q;
        for (int i = 1; i <= n; i++){
            if (in_degree[i] == 0) q.push(i);
        }

        vector<int> order;
        bool unique = true;
        while (!q.empty()){
            if (q.size() > 1) unique = false;
            int curr = q.front();
            q.pop();
            order.push_back(curr);
            for (int next : graph[curr]){
                if (--in_degree[next] == 0) q.push(next);
            }
        }

        cout << "Case #" << tc << ": ";
        if ((int)order.size() != n){
            cout << "recheck hints\n";
        } else if (!unique){
            cout << "missing hints\n";
        } else {
            for (int i = 0; i < n; i++){
                if (i) cout << " ";
                cout << order[i];
            }
            cout << "\n";
        }
    }
}
