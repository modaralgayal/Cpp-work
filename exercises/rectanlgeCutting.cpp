#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int main () { 
    int a, b;
    cin >> a >> b;

    vector<vector<int>> table(a + 1, vector<int>(b + 1, 10000000));

    for (int i = 0; i <= a; i++) {
        for (int j = 0; j <= b; j++) {
            if (i == j) {
                table[i][j] = 0;
            } 
            else {
                for (int k = 1; k < j; k++) {
                    table[i][j] = min(table[i][j], table[i][k] + table[i][j - k] + 1);
                }
                for (int k = 1; k < i; k++) {
                    table[i][j] = min(table[i][j], table[k][j] + table[i - k][j] + 1);
                }
            }

        }
    }

    cout << "Table contents:\n";
    for (int i = 0; i <= a; i++) {
        for (int j = 0; j <= b; j++) {
            cout << table[i][j] << " ";
        }
        cout << "\n"; // Move to the next row
    }

    cout << table[a][b] << "\n";
}
