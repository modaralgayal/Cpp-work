#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef long long ll;
#define ln "\n"

int main () {
    ll n;
    ll t;
    cin >> n >> t;
    vector<int> times(n);

    for (int i = 0; i < n; i++) {
        cin >> times[i];
    }

    ll lowestTime = 0;
    ll highestTime = 1e18;
    ll result = 1e18;
    ll bigNum = 1e9;

    while (lowestTime <= highestTime) {
        ll middle = (lowestTime + highestTime) / 2;
        ll products = 0;
        for (int i = 0; i < n; i++) {
            products += min(middle/times[i], bigNum);
        }

        if (products >= t) {
            if (middle < result) {
                result = middle;
            }
            highestTime = middle - 1;
        } else {
            lowestTime = middle + 1;
        }
    }

    cout << result << ln;

}