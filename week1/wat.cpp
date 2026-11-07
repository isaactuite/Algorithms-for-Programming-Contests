#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>


using namespace std;

vector<long long> extract_ints(const string& s) {
    vector<long long> nums;
    for (size_t i = 0; i < s.size(); ) {
        if (isdigit(static_cast<unsigned char>(s[i]))) {
            long long n = 0;
            while (i < s.size() && isdigit(static_cast<unsigned char>(s[i])))
                n = n * 10 + (s[i++] - '0');
            nums.push_back(n);
        } else {
            ++i;
        }
    }
    return nums;
}

char toSymbol(const string& w) {
    if (w == "plus")  return '+';
    if (w == "minus") return '-';
    if (w == "times") return '*';
    if (w == "tothepowerof")   return '^';
    return '?';
}

vector<char> extract_ops(const string& s) {
    vector<char> ops;
    for (size_t i = 0; i < s.size(); ) {
        if (isalpha(static_cast<unsigned char>(s[i]))) {
            size_t start = i;
            while (i < s.size() && isalpha(static_cast<unsigned char>(s[i])))
                ++i;
            ops.push_back(toSymbol(s.substr(start, i - start)));
        } else {
            ++i;
        }
    }
    return ops;
}


int perform_op(int a, int b, char op){
    if (op == '+') return a+b;
    if (op == '-') return a-b;
    if (op == '*') return a*b;
    if (op == '^') return pow(a, b);
    return a;
}

int main(){
    int t;
    cin >> t;

    for (int i = 0; i<t; i++){
        string m;
        cin >> m;
        
        vector<long long> integers = extract_ints(m);
        if (integers.size() == 1) {
            cout << "Case #" << i+1 << ": " << integers[0]<< endl;
            continue;
        }
        vector<char> operators = extract_ops(m);

        int current = integers[0];
        for (int j = 1; j < integers.size(); j++){
            current = perform_op(current, integers[j], operators[j-1]);
        }

        cout << "Case #" << i+1 << ": " << current<< endl;

    }


    return 0;
}