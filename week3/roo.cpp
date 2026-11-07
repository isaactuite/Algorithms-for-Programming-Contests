#include <iostream>
#include <vector>
using namespace std;

// The map lists every (room, station) pair sorted by room number. The number
// of lines with room <= x is the sum over stations of the overlap of [u, v]
// with [1, x]. The answer for line r is the smallest x with count(x) >= r.

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++){
        int s, f;
        cin >> s >> f;
        vector<long long> u(s), v(s);
        for (int i = 0; i < s; i++) cin >> u[i] >> v[i];

        auto count_upto = [&](long long x){
            long long total = 0;
            for (int i = 0; i < s; i++){
                if (x >= u[i]) total += min(x, v[i]) - u[i] + 1;
            }
            return total;
        };

        cout << "Case #" << tc << ":\n";
        for (int i = 0; i < f; i++){
            long long r;
            cin >> r;
            long long lo = 1, hi = 2147483647LL;
            while (lo < hi){
                long long mid = lo + (hi - lo) / 2;
                if (count_upto(mid) >= r) hi = mid;
                else lo = mid + 1;
            }
            cout << lo << "\n";
        }
    }
}
