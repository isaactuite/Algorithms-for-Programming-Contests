#include <iostream>
#include <vector>
using namespace std;

// Union-find over alliances. After applying all the rules, every alliance has
// at most one "enemy alliance" (rule 4: everyone who hates z is allied). So
// each root stores one representative of its enemy alliance. When two
// alliances merge, their enemy alliances must merge too (rules 5 + 4), which
// we handle with an explicit worklist instead of recursion.

vector<int> parent, sz, enemy;

int find(int x){
    while (parent[x] != x){
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void unite(int a, int b){
    vector<pair<int, int>> work = {{a, b}};
    while (!work.empty()){
        auto [x, y] = work.back();
        work.pop_back();
        int rx = find(x), ry = find(y);
        if (rx == ry) continue;
        if (sz[rx] < sz[ry]) swap(rx, ry);
        int ex = enemy[rx], ey = enemy[ry];
        parent[ry] = rx;
        sz[rx] += sz[ry];
        if (ex == -1) enemy[rx] = ey;
        else if (ey != -1) work.push_back({ex, ey});
    }
}

void hate(int x, int y){
    int rx = find(x), ry = find(y);
    int ex = enemy[rx], ey = enemy[ry];
    if (ex == -1) enemy[rx] = y;
    if (ey == -1) enemy[ry] = x;
    if (ex != -1) unite(ex, y);   // common enemy x -> allied
    if (ey != -1) unite(ey, x);   // common enemy y -> allied
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    for (int i = 1; i <= t; i++){
        int n, m;
        cin >> n >> m;
        parent.assign(n + 1, 0);
        sz.assign(n + 1, 1);
        enemy.assign(n + 1, -1);
        for (int v = 0; v <= n; v++) parent[v] = v;

        for (int j = 0; j < m; j++){
            char r; int x, y;
            cin >> r >> x >> y;
            if (r == 'F') unite(x, y);
            else          hate(x, y);
        }

        int count = sz[find(1)];
        cout << "Case #" << i << (2 * count > n ? ": yes" : ": no") << "\n";
    }
}
