#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <tuple>
#include <numeric>
using namespace std;

vector<int> p;
int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }

int main(){
    int t;
    unordered_map<int, vector<pair<int, int>>> graph;
    priority_queue<tuple<long long, int, int>> pq;
    cin >> t;

    for (int i = 0; i<t; i++){
        int n,m;
        cin >>n>>m;
        p.assign(n + 1, 0);
        iota(p.begin(), p.end(), 0);
        for (int j = 0; j<m; j++){
            int a,b,c;
            cin >>a>>b>>c;
            pq.push({c,a,b});
            
            
        }
        long long count = 0;
        while (!pq.empty()){
            tuple<long long, int, int>top = pq.top();
            int a = get<1>(top), b = get<2>(top);
            int ra = find(a), rb = find(b);
            if (ra == rb) {
                count += get<0>(top);
            } else {
                p[ra] = rb;
            }

            pq.pop();

        }

        cout << "Case #" << i+1<<": "<<count<<endl;

    }
}