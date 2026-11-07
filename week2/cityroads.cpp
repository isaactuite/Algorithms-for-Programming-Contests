#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>



using namespace std;



void compute_in_degree(unordered_map<int, int>& in_degree){
    
}


vector<int> top_sort(unordered_map<int, vector<int>> graph, int n){
    unordered_map<int, int> in_degree;
    vector<int> top_order;
    for (const auto& [key, value] : graph){
        for (int j = 0; j<value.size(); j++){
            in_degree[value[j]]++;
        }
    }

    queue<int> q;
    for (int i = 1; i<=n; i++){
        if (in_degree[i] == 0){
            q.push(i);
        }
    }

    while (!q.empty()){
        int curr = q.front();
        q.pop();
        top_order.push_back(curr);

        for (int neighbour : graph[curr]){
            in_degree[neighbour]--;
            if (in_degree[neighbour] == 0) {
                q.push(neighbour);
            }
        }

    }

    if (top_order.size() != n) {
        return {}; // Return empty vector indicating failure
    }
    return top_order;
}

int main(){
    int t;

    cin >> t;

    for (int i = 0; i<t; i++){
        int n, m, l;
        cin >>n >>m >>l;

        unordered_map<int, vector<int>> graph;
        vector<vector<int>> input_order;
        unordered_map<int, int> in_degree;
        

        for (int j = 1; j<=m; j++){
            int a, b;
            cin >>a >> b;
            graph[a].push_back(b);
        }
        for (int j = 1; j<=l; j++){
            int a, b;
            cin >>a >> b;
            input_order.push_back({a, b});
        }
        vector<int> top_order = top_sort(graph, n);
        if (top_order.empty()){
            cout << "Case #" << i+1 << ": no\n";
            continue;
        }

        
        cout << "Case #" << i+1 << ": yes\n";
        for (int j = 0; j<input_order.size(); j++){
            for (int k = 0; k<top_order.size(); k++){
                if (input_order[j][0] == top_order[k]){
                    cout << input_order[j][0] << " " << input_order[j][1] << endl;
                    break;
                }
                if (input_order[j][1] == top_order[k]){
                    cout << input_order[j][1] << " " << input_order[j][0] << endl;
                    break;
                }
            }
        }

        
    }
}