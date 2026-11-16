#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Cities are sorted by luxury class (a_1 <= a_2 <= ... <= a_n), so "all
// intermediate airports have class <= l" means "intermediates come from a
// prefix of the city indices". Floyd-Warshall adds intermediate vertices in
// index order, so after adding the last city of class <= l, d[x][y] is the
// answer to every query with limit l. Queries are answered offline, grouped by l.

static const int INF = 1e9;
static int d[500][500];

int main(){
    int t;
    if (scanf("%d", &t) != 1) return 0;
    for (int tc = 1; tc <= t; tc++){
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);
        vector<int> a(n);
        for (auto &x : a) scanf("%d", &x);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) d[i][j] = (i == j) ? 0 : INF;
        for (int i = 0; i < m; i++){
            int x, y, c;
            scanf("%d %d %d", &x, &y, &c);
            x--; y--;
            if (c < d[x][y]) d[x][y] = c;
        }
        vector<vector<int>> byLimit(201);
        vector<int> qx(k), qy(k);
        for (int i = 0; i < k; i++){
            int l;
            scanf("%d %d %d", &qx[i], &qy[i], &l);
            qx[i]--; qy[i]--;
            byLimit[l].push_back(i);
        }
        vector<int> res(k);
        int next = 0; // cities [0, next) already added as intermediates
        for (int l = 0; l <= 200; l++){
            while (next < n && a[next] <= l){
                int v = next++;
                for (int i = 0; i < n; i++){
                    if (d[i][v] >= INF) continue;
                    int div = d[i][v];
                    for (int j = 0; j < n; j++){
                        if (d[v][j] >= INF) continue;
                        int nd = div + d[v][j];
                        if (nd < d[i][j]) d[i][j] = nd;
                    }
                }
            }
            for (int q : byLimit[l]) res[q] = d[qx[q]][qy[q]];
        }
        string out = "Case #" + to_string(tc) + ":";
        for (int i = 0; i < k; i++){
            out += ' ';
            if (res[i] >= INF) out += "impossible";
            else out += to_string(res[i]);
        }
        puts(out.c_str());
    }
}
