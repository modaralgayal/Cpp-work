#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <unordered_set>
 
using namespace std;
 
vector<int> buildSuffixArray(const string &s) {
    int n = s.size();
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
 
class SegmentTree {
public:
    SegmentTree(const vector<int> &data) {
        n = data.size();
        tree.resize(4 * n);
        buildTree(data, 0, 0, n - 1);
    }
 
    void buildTree(const vector<int> &data, int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            buildTree(data, 2 * node + 1, start, mid);
            buildTree(data, 2 * node + 2, mid + 1, end);
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }
 
    int rangeMinQuery(int l, int r) {
        return rangeMinQueryUtil(0, 0, n - 1, l, r);
    }
 
private:
    int n;
    vector<int> tree;
 
    int rangeMinQueryUtil(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return INT_MAX;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return min(rangeMinQueryUtil(2 * node + 1, start, mid, l, r),
                   rangeMinQueryUtil(2 * node + 2, mid + 1, end, l, r));
    }
};
 
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
 
    unordered_set<char> presentChars(text.begin(), text.end());
    unordered_map<string, int> results;
    
    for (auto &query : queries) {
        vector<int> occurrences;

        if (presentChars.find(query[0]) == presentChars.end()) {
            cout << -1 << "\n";
            results[query] = -1;
            continue;
        }
 
        if (results.find(query) != results.end()) {
            if (results[query] == -1) {
                cout << -1 << "\n";
                continue;
            }
            cout << (results[query] + 1) << "\n"; 
            continue;
        }
 
        int low = 0, high = text.length();
 
        while (low < high) {
            int mid = (low + high) / 2;
            string suffix = text.substr(suffixArray[mid], query.length());
            if (suffix < query) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
 
        int start = low;
        high = text.length();
 
        while (low < high) {
            int mid = (low + high) / 2;
            string suffix = text.substr(suffixArray[mid], query.length());
            if (suffix <= query) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
 
        int end = low;
 
        for (int j = start; j < end; ++j) {
            occurrences.push_back(suffixArray[j]);
        }
        if (!occurrences.empty()) {
            SegmentTree segmentTree(occurrences);
            int minIndex = segmentTree.rangeMinQuery(0, occurrences.size() - 1);
            results[query] = minIndex;
            cout << (minIndex + 1) << "\n";             
        } else {
            results[query] = -1;
            cout << -1 << "\n"; 
        }
    }
 
}