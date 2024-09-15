#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main() {
    long long n, k;
    cin >> n >> k;

    vector<long long> values(n); 
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }
    multiset<vector<long long>> distinctVals;
    map<long long, long long> freq; 
    long long j = 0;
    long long validArrays = 0;
    for (int i = 0; i < n; i++) {
        freq[values[i]]++; 
        while (freq.size() > k) {
            freq[values[j]]--;  
            if (freq[values[j]] == 0) {
                freq.erase(values[j]);
            }
            j++; 
        }

        validArrays += (i - j + 1);
    }

    //for (const auto& subset : distinctVals) {
    //    for (const auto& elem : subset) {
    //        cout << elem << " ";
    //    }
    //    cout << "\n";
    // }

    cout << validArrays << " ";

    return 0;
}
