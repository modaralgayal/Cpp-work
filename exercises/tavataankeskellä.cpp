#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;
typedef long long ll;
#define ln "\n"

vector<ll> calcSubsets(const vector<ll>& arr) {
    vector<ll> subsetSums;
    ll size = arr.size();
    int total = 1 << size;  


    for (int j = 0; j < total; j++) {
        ll sum = 0; 
        for (int i = 0; i < size; i++) {
            if (j & (1 << i)) {
                sum += arr[i];
            }
        }
        subsetSums.push_back(sum);
    }
    return subsetSums;
}

int main () {
    ll n, k;
    cin >> n >> k;
    vector<ll> values(n);
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }
    
    ll mid = n / 2;

    vector<ll> left = calcSubsets(vector<ll>(values.begin(), values.begin() + mid));
    vector<ll> right = calcSubsets(vector<ll>(values.begin() + mid, values.end()));

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    ll result = 0;

    for (ll leftVal : left) {
        auto low = lower_bound(right.begin(), right.end(), k - leftVal);
        auto high = upper_bound(right.begin(), right.end(), k - leftVal);
        ll start = low - right.begin();
        ll end = high - right.begin();
        result += end - start;

    }

    cout << result << endl;
}
