#include <iostream>

using namespace std;

int main(){
    int t;
    long long m;
    long long c = 299792458;

    cin >> t;
    
    for (int i = 0; i<t; i++){
        cin >> m;
        long long result = m * c * c;
        cout << "Case #" << i+1 << ": " << result << endl;
    }

    return 0;
}