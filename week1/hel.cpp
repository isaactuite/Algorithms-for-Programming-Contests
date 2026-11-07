#include <iostream>
#include <string>

using namespace std;

int main(){
    int t;
    cin >> t;
    string s;
    for (int i = 0; i<t; i++){
        cin >> s;
        cout << "Case #" << i+1 << ": Hello " << s << "!\n";
    }
    return 0;
}