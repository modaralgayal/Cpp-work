#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
string const ln = "\n";

vector<int> buildSuffixArray(const string &s) {
    int n = s.length();
    vector<int> suffixArray(n), ranks(n), tempRanks(n);

    for (int i = 0; i < n; i++) {
        suffixArray[i] = i;
        ranks[i] = s[i]; 
    }

    for (int k = 1; k < n; k *= 2) {
        auto suffixCompare = [&](int i, int j) {
            if (ranks[i] != ranks[j]) return ranks[i] < ranks[j];
            int rank_i_k = (i + k < n) ? ranks[i + k] : -1;
            int rank_j_k = (j + k < n) ? ranks[j + k] : -1;
            return rank_i_k < rank_j_k;
        };

        sort(suffixArray.begin(), suffixArray.end(), suffixCompare);

        tempRanks[suffixArray[0]] = 0;
        for (int i = 1; i < n; i++) {
            tempRanks[suffixArray[i]] = tempRanks[suffixArray[i - 1]] + (suffixCompare(suffixArray[i - 1], suffixArray[i]) ? 1 : 0);
        }
        ranks = tempRanks;
    }

    return suffixArray;
}


int lowerBound(const string &s, const string &pattern, const vector<int> &suffixArray) {
    int n = s.length();
    int m = pattern.length();
    int low = 0, high = n;

    while (low < high) {
        int mid = (low + high) / 2;
        string suffix = s.substr(suffixArray[mid], m);
        if (suffix < pattern) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

int upperBound(const string &s, const string &pattern, const vector<int> &suffixArray) {
    int n = s.length();
    int m = pattern.length();
    int low = 0, high = n;

    while (low < high) {
        int mid = (low + high) / 2;
        string suffix = s.substr(suffixArray[mid], m);
        if (suffix <= pattern) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

int countOccurrences(const string &s, const string &pattern, const vector<int> &suffixArray) {
    int lower = lowerBound(s, pattern, suffixArray);
    int upper = upperBound(s, pattern, suffixArray);

    return upper - lower;
}

int main() {
    string text;
    cin >> text;   
    int n;
    cin >> n;      

    vector<string> queries(n);
    for (int i = 0; i < n; i++) {
        cin >> queries[i];
    }

    vector<int> suffixArray = buildSuffixArray(text);

    for (int i = 0; i < n; i++) {
        cout << countOccurrences(text, queries[i], suffixArray) << ln;
    }

    return 0;
}
