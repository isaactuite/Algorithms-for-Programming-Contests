#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

// Bidirectional BFS over permutations of 0..n-1. Each permutation is mapped
// to its rank in [0, n!) (Lehmer code), so the visited/distance tables are
// plain char arrays of size n! (at most 3.6 MB each) instead of hash maps.

int n;
int fact[11];

int perm_rank(const int* v){
    int r = 0, used = 0;
    for (int i = 0; i < n; i++){
        // number of unused values smaller than v[i]
        int smaller = v[i] - __builtin_popcount(used & ((1 << v[i]) - 1));
        r += smaller * fact[n - 1 - i];
        used |= 1 << v[i];
    }
    return r;
}

void perm_unrank(int r, int* v){
    int used = 0;
    for (int i = 0; i < n; i++){
        int k = r / fact[n - 1 - i];
        r %= fact[n - 1 - i];
        // pick the k-th unused value
        for (int x = 0; x < n; x++){
            if (used & (1 << x)) continue;
            if (k-- == 0){
                v[i] = x;
                used |= 1 << x;
                break;
            }
        }
    }
}

int main(){
    cin >> n;
    fact[0] = 1;
    for (int i = 1; i <= 10; i++) fact[i] = fact[i - 1] * i;

    int start[10], target[10];
    for (int i = 0; i < n; i++){
        cin >> start[i];
        start[i]--;
        target[i] = i;
    }

    int start_r = perm_rank(start), target_r = perm_rank(target);
    if (start_r == target_r){
        cout << 0 << endl;
        return 0;
    }

    vector<signed char> dist_f(fact[n], -1), dist_b(fact[n], -1);
    dist_f[start_r] = 0;
    dist_b[target_r] = 0;
    vector<int> frontier_f = {start_r}, frontier_b = {target_r};
    int depth_f = 0, depth_b = 0;

    // forward:  a b c d -> c a d b
    // backward: a b c d -> b d a c   (inverse of the forward move)
    static const int fwd[4] = {2, 0, 3, 1};
    static const int bwd[4] = {1, 3, 0, 2};

    while (!frontier_f.empty() && !frontier_b.empty()){
        // expand the smaller side, one whole level at a time
        bool forward = frontier_f.size() <= frontier_b.size();
        vector<int>& frontier = forward ? frontier_f : frontier_b;
        vector<signed char>& mine = forward ? dist_f : dist_b;
        vector<signed char>& other = forward ? dist_b : dist_f;
        int& depth = forward ? depth_f : depth_b;
        const int* order = forward ? fwd : bwd;

        int best = INT_MAX;
        vector<int> next_frontier;
        int v[10], out[10];

        for (int r : frontier){
            perm_unrank(r, v);
            for (int a = 0; a <= n; a++){
                for (int b = 0; a + b <= n; b++){
                    for (int c = 0; a + b + c <= n; c++){
                        int d = n - a - b - c;
                        int st[4] = {0, a, a + b, a + b + c};
                        int len[4] = {a, b, c, d};
                        int k = 0;
                        for (int p = 0; p < 4; p++){
                            int part = order[p];
                            for (int i = 0; i < len[part]; i++) out[k++] = v[st[part] + i];
                        }
                        int h = perm_rank(out);
                        if (mine[h] != -1) continue;
                        mine[h] = depth + 1;
                        next_frontier.push_back(h);
                        if (other[h] != -1) best = min(best, depth + 1 + other[h]);
                    }
                }
            }
        }

        if (best != INT_MAX){
            cout << best << endl;
            return 0;
        }
        frontier.swap(next_frontier);
        depth++;
    }
}
