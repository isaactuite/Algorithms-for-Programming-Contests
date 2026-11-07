#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main(){
    string entin = "entin";
    string entin_r = "ierende";
    string enten = "enten";
    string enten_r = "ierende";
    string ent = "ent";
    string ent_r = "ierender";

    int t;
    cin >> t;
    for (int i = 0; i<t; i++){
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard rest of the line
        cout << "Case #" << i+1 << ":\n";

        for (int j = 0; j<n; j++){
            string m;
            getline(cin, m);

            size_t found1 = m.find(entin);
            while (found1 !=string::npos){
                m.replace(found1, 5, entin_r);
                found1 = m.find(entin);
            }
            size_t found2 = m.find(enten);
            while (found2 !=string::npos){
                m.replace(found2, 5, enten_r);
                found2 = m.find(enten);
            }
            size_t found3 = m.find(ent);
            while (found3 !=string::npos){
                m.replace(found3, 3, ent_r);
                found3 = m.find(ent);
            }
            cout << m << endl;
        }
    }

    return 0;
}