#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main () {
    ll n = 1e6+10;
    ll mod = 1e9+7;
    vector<vector<ll>> table(n, vector<ll>(8, 0));
    for (int i = 0; i < 8; i++) 
        table[0][i] = 1;
    

    for (int i = 1; i < n; i++) {  
        for (int j = 0; j < 8; j++) {
            
            
            if (j == 0 || j == 2 || j == 3 || j == 4 || j == 5) {
                ll sumOfPossibilities = table[i-1][0] + table[i-1][1] + table[i-1][3] + table[i-1][4] + table[i-1][5]; 
                table[i][j] = sumOfPossibilities % mod;  
            } else {
                
                ll sumOfPossibilities = table[i-1][2] + table[i-1][6] + table[i-1][7]; 
                table[i][j] = sumOfPossibilities % mod;  
            }
        }
    }

    int t;
    cin >> t;
    vector<int> tests(t);
    for (int i = 0; i < t; i++) {
        cin >> tests[i]; 
    }
    for (int i = 0; i < t; i++) {
        cout << (table[tests[i] - 1][2] + table[tests[i] - 1][6]) % mod << "\n";
    }

    return 0;
}
