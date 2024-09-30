#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
string const ln = "\n";

int main() {
    ll n, q;
    cin >> n >> q;

    ll LOG = 0;
    while ((1LL << LOG) <= 1e9) {
        LOG++;
    }

    vector<vector<ll>> anc(LOG + 1, vector<ll>(n + 1, -1));

    for (ll i = 1; i <= n; i++) {
        cin >> anc[0][i];  
    }

    for (ll i = 1; i <= LOG; i++) {
        for (ll j = 1; j <= n; j++) {
            if (anc[i-1][j] != -1) {
                anc[i][j] = anc[i-1][anc[i-1][j]];
            }
        }
    }
    vector<ll> results;
    while (q--) {
        ll x, k;
        cin >> x >> k;
        for (ll j = 0; j <= LOG && x != -1; j++) {
            if (k & (1LL << j)) {
                x = anc[j][x]; 
            }
        }
        results.push_back(x); 
    }


    for (auto val : results) {
        cout << val << ln;
    }

    return 0;
}
