#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long n;
    cin >> n; 
    vector<long long> values(n);
    vector<vector<long long>> table(n, vector<long long>(n));
    long long sumOfVals = 0;
    
    for (int i = 0; i < n; i++) {
        cin >> values[i];
        table[i][i] = values[i]; 
        sumOfVals += values[i];   
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            table[i][j] = max(values[i] - table[i + 1][j], values[j] - table[i][j - 1]);
        }
    }

    //for (int i = 0; i < n; i++) {
    //    for (int j = 0; j < n; j++) {
    //        cout << table[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    cout << (sumOfVals + table[0][n-1]) / 2 << endl;

    return 0;
}
