#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
string const ln = "\n";
typedef long long ll;

vector<ll> buildSuffixArray(const string &s) {
    ll  n = s.size();
    vector<ll> suffixArray(n), ranks(n), tempRanks(n);

    for (ll i = 0; i < n; i++) {
        suffixArray[i] = i;
        ranks[i] = s[i];
    }

    for (ll k = 1; k < n; k *= 2) {
        auto suffixCompare = [&](ll i, ll j) {
            if (ranks[i] != ranks[j]) return ranks[i] < ranks[j];
            ll rank_i_k = (i + k < n) ? ranks[i + k] : -1;
            ll rank_j_k = (j + k < n) ? ranks[j + k] : -1;
            return rank_i_k < rank_j_k;
        };

        sort(suffixArray.begin(), suffixArray.end(), suffixCompare);

        tempRanks[suffixArray[0]] = 0;
        for (ll i = 1; i < n; i++) {
            tempRanks[suffixArray[i]] = tempRanks[suffixArray[i - 1]] + (suffixCompare(suffixArray[i - 1], suffixArray[i]) ? 1 : 0);
        }
        ranks = tempRanks;
    }

    return suffixArray;
}

vector<ll> buildLCPArray(const string &s, const vector<ll> &suffixArray) {
    ll n = s.size();
    vector<ll > lcp(n, 0), rank(n, 0);

    for (ll i = 0; i < n; i++) {
        rank[suffixArray[i]] = i;
    }

    ll h = 0; 
    for (ll i = 0; i < n; i++) {
        if (rank[i] > 0) {
            ll j = suffixArray[rank[i] - 1]; 
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) {
                h++;
            }
            lcp[rank[i]] = h; 
            if (h > 0) {
                h--; 
            }
        }
    }

    return lcp;
}

ll countDistinctSubstrings(const string &s, const vector<ll> &suffixArray, const vector<ll> &lcpArray) {
    ll n = s.size();
    ll distinctCount = 0;

    for (ll i = 0; i < n; i++) {
        distinctCount += (n - suffixArray[i]) - lcpArray[i];
    }

    return distinctCount;
}

int main() {
    string text;
    cin >> text;

    vector<ll> suffixArray = buildSuffixArray(text);
    vector<ll> lcpArray = buildLCPArray(text, suffixArray);
    ll distinctSubstringCount = countDistinctSubstrings(text, suffixArray, lcpArray);


    cout << distinctSubstringCount << ln;

    return 0;
}
