#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

// Longest path in a DAG. Successors always have a larger index than their
// predecessor, so processing tasks in index order is a topological order.
// start[j] = latest finish time of any predecessor; the answer is the finish
// time of task n.

int main(){
    int t;
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++){
        int n;
        scanf("%d", &n);
        vector<int> start(n + 1, 0);
        int ans = 0;
        for (int i = 1; i <= n; i++){
            int p, s;
            scanf("%d %d", &p, &s);
            int fin = start[i] + p;
            if (i == n) ans = fin;
            for (int k = 0; k < s; k++){
                int j;
                scanf("%d", &j);
                start[j] = max(start[j], fin);
            }
        }
        printf("Case #%d: %d\n", tc, ans);
    }
}
