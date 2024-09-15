#include <iostream> 
#include <vector>
#include <algorithm>

using namespace std;
#define ln "\n"
typedef long long ll;

int main () {
    ll n;
    cin >> n;
    vector<ll> sticks(n);
    ll sum = 0;

    for (int i = 0; i < n; i++) {
        cin >> sticks[i];
        sum += sticks[i];
    }
    sort(sticks.begin(), sticks.end());
    ll lp = sticks[n / 2];
    ll totalCost = 0;

    for (int j = 0; j < n; j++) {
        totalCost += abs(lp - sticks[j]);
    }

    cout << totalCost << ln;

}