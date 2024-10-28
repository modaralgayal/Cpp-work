#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
string const ln = "\n";

int main() {
    int n; 
    cin >> n; 

    if (n == 0) { 
        cout << 0 << ln; 
        return 0;
    }

    vector<int> values(1e6 + 1, 0); 
    int maxGCD = 0;

    for (int i = 0; i < n; i++) {
        int val;
        cin >> val; 
        values[val]++; 
        if (val > maxGCD) maxGCD = val;
    }

    for (int i = maxGCD; i >= 1; i--) {
        int matching = 0;
        for (int jump = i; jump <= maxGCD; jump += i) { 
            matching += values[jump];
        }
        if (matching > 1) {
            cout << i << ln; 
            return 0; 
        }
    }

    cout << 1 << ln; 
    return 0;
}
