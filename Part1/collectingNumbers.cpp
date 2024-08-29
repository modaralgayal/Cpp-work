#include <iostream>

using namespace std;

int main () {
    int n;
    cin >> n; 
    long long values[n];
    long long valuePositions[n + 1];
    valuePositions[0] = 0;

    for (int i = 0; i < n; i++) {
        cin >> values[i];            
        valuePositions[values[i]] = i;
    }

    long long rounds = 0;

    for (int i = 0; i <= n; i++) {
        if (valuePositions[i] < valuePositions[i - 1]) {
            rounds += 1;
        } else continue;
    }

    cout << rounds << "\n";

}