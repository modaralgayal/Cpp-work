#include <iostream>
#include <string>
#include <vector> 

using namespace std;

int main() {
    string findInHere;
    string pattern;
    
    cin >> findInHere >> pattern;

    int patternLen = pattern.size();
    string connected = pattern + "$" + findInHere;
    int n = connected.size();
    vector<int> Z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            Z[i] = min(r - i + 1, Z[i - l]);
        }
        while (i + Z[i] < n && connected[Z[i]] == connected[i + Z[i]]) {
            Z[i]++; 
        }
        if (i + Z[i] - 1 > r) {
            l = i;
            r = i + Z[i] - 1;
        }
    }
    int patternCount = 0;
    for (int i = patternLen + 1; i < n; i++) {
        if (Z[i] == patternLen) {
            patternCount++;
        }
    }

    cout << patternCount << endl;

    return 0;
}
