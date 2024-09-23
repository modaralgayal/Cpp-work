#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
#define ln "\n";

ll n;
void change(vector<ll> &tree, ll k, ll x,ll p) {
    k += p; 
    tree[k] = x;
    for (k /= 2; k >= 1; k /= 2) {
        tree[k] = tree[2 * k] + tree[2 * k + 1]; 
    }
}

ll find(vector<ll> &tree, ll k,ll p) {
    ll left = 0;
    ll i = 1;
    while (i < p) {
        if (left + tree[2 * i] >= k) {
            i = 2 * i;
        } else {
            left += tree[2 * i];
            i = 2 * i + 1;
        }
    }
    return i - p;
}

int main() {
    cin >> n;
    ll p2Length = 1;
    for (int j = 0; j < n; j++) {
        if (p2Length < n) {
            p2Length *= 2;
        }
    }
    // this way i can get the optimal size for the segment tree, the smallest 2nd power, this is inspired from the internet.
    vector<ll> tree(4*n, 0);
    vector<ll> arr(n);
    for (ll i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (ll i = p2Length; i < 4*n; i++) {
        tree[i] = 1;
    }

    for (ll i = p2Length - 1; i > 0; i--) {
        tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    vector<ll> indexes(n);
    for (ll i = 0; i < n; i++) {
        cin >> indexes[i];
    }

    for (ll i = 0; i < n; i++) {
        ll pos = indexes[i];  
        ll elementIdx = find(tree, pos, p2Length);
        cout << arr[elementIdx] << " "; 
        change(tree, elementIdx, 0, p2Length);
    }

    return 0;
}
