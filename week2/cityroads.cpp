#include <iostream>
#include <unordered_map>
#include <vector>


using namespace std;




bool contains_cycle(unordered_map<int, vector<int>>){

}

int main(){
    int t;

    cin >> t;

    for (int i = 0; i<t; i++){
        int n, m, l;
        cin >>n >>m >>l;
        unordered_map<int, vector<int>> graph;
        vector<vector<int>> input_order;
        for (int j = 1; j<=m; j++){
            int a, b;
            cin >>a >> b;
            graph[a].push_back(b);
        }

        if (top_sort(graph)){
            cout << "Case #" << i+1 << ": no" << endl;
            continue;
        }

        for (int j = 1; j<=l; j++){
            int a, b;
            cin >>a >> b;
            input_order.push_back({a, b});
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        
    }
}