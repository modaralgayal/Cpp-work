#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
string const ln = "\n";

// nää oli hauskoja tehdä
int main () {
    ll tests;
    cin >> tests;


    while (tests--) {
        ll n;
        cin >> n;
        vector<ll> values(n);
        ll xorSum = 0;
        for (ll i = 0; i < n; i++) {
            ll pile;
            cin >> pile;
            if (i%2 == 0) continue;
            xorSum ^= pile;
        }
        if (xorSum != 0) {
            cout << "first" << ln;
        } else {
            cout << "second" << ln;
        }
    }
}