#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string pattern;
    cin >> pattern;
    int patternLen = pattern.size();
    vector<int> Z(patternLen, 0);
    int l = 0, r = 0;
    for (int i = 1; i < patternLen; i++) {
        if (i <= r) {
            Z[i] = min(r - i + 1, Z[i - l]);
        }
        while (i + Z[i] < patternLen && pattern[Z[i]] == pattern[i + Z[i]]) {
            Z[i]++; 
        }
        if (i + Z[i] - 1 > r) {
            l = i;
            r = i + Z[i] - 1;
        }
    }

    for (int i = patternLen - 1; i >= 1; i--) {
        if (Z[i] == patternLen - i) {
            cout << Z[i] << " "; 
        }
    }

    return 0;
}
