#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
#define ln "\n";
typedef long long ll;


int main () {
    ll n;
    ll t;
    cin >> n >> t;
    vector<int> values(n);
    int maxVal = 0;

    for (int i = 0; i < n; i++) {
        cin >> values[i];
        maxVal = max(maxVal,values[i]);
    }

    ll lowestTime = maxVal;
    ll highestTime = 1e18;
    ll result = 1e18;


    while (lowestTime <= highestTime) {
        ll middle = (lowestTime + highestTime) / 2;
        ll arrays = 1;
        ll sum = 0;

        for (int i = 0; i < n; i++) {
            if (sum + values[i] > middle)
            {
                //tässä asetan summa nollaksi, menen "seuraavalle" listalle
                sum = 0;
                arrays += 1;
            }
            sum += values[i];
        }

        if (arrays > t) {
            lowestTime = middle + 1;
        } else {
            if (middle < result)
            {
                result = middle;
            }
            highestTime = middle - 1;
        }
    }

    cout << result << ln;

}