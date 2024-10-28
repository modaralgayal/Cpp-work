#include <iostream>
#include <vector>
 
using namespace std;
typedef long long ll;
#define ln "\n";
 
 
 
int main() {
    ll n, q;
    cin >> n >> q;
    vector<ll> tree(2*n,0);
 
    for (ll i = 0; i < n; i++) {
        cin >> tree[n + i];
    }
    
    for (ll i = n-1; i > 0; i--) {
        tree[i] = tree[i*2] + tree[i*2 + 1];
    }
 
    vector<vector<ll>> queries(q);
    for (ll i = 0; i < q; i++) {
        vector<ll> query(3);
        for (int j = 0; j < 3; j++) {
            cin >> query[j];
        }
        queries[i] = query;
    }
 
 
 
    auto change = [&](ll k, ll u) {
        k--;
        k += n;
        tree[k] = u;
        for (k /= 2; k >= 1; k /= 2) {
            tree[k] = tree[2 * k] + tree[2 * k + 1];
        }
    };
 
    auto getSum = [&](ll a, ll b) {
        a--; b--;
        a += n;
        b += n;
        ll s = 0;
        while (a <= b) {
            if (a % 2 == 1) {
                s += tree[a++];
            }
            if (b % 2 == 0) {
                s += tree[b--];
            }
            a /= 2; b /= 2;
        }
        return s;
    };
 
    for (int i = 0; i < q; i++) {
        if (queries[i][0] == 1) {
            change(queries[i][1],queries[i][2]);
        } else if (queries[i][0] == 2) {
            cout << getSum(queries[i][1],queries[i][2]) << ln; 
        } else {
            cout << "Wrong Type number" << ln;
        }
    }
 
}