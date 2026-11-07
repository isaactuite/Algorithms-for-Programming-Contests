#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>

using namespace std;

int main(){

    int n,m;
    int count = 1;
    while (cin>>n>>m){
        if (count != 1){
            cout << "\n";
            
        }
        count++;

        priority_queue<tuple<int, int, string, int>,
               vector<tuple<int, int, string, int>>,
               greater<>> students;
        for (int i = 0; i<m; i++){
            string s;
            int t, e;

            cin >> s;
            cin>>t>>e;
            
            students.emplace(t, -e, s, t);
        }
        for (int i = 0; i < n; i++) {
            auto [clk, ne, name, t] = students.top();
            students.pop();
            cout << name << " " << clk << "\n";
            students.emplace(clk+t, ne, name, t);
        }

    }
}