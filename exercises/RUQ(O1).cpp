#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
string const ln = "\n";

struct SegmentTree {
    vector<ll> tree, lazy;
    ll n;

    SegmentTree(const vector<ll>& arr) {
        n = arr.size();
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    void build(const vector<ll>& arr, ll node, ll start, ll end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            ll mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void updateRange(ll l, ll r, ll value) {
        updateRange(0, 0, n - 1, l - 1, r - 1, value); 
    }

    void updateRange(ll node, ll start, ll end, ll l, ll r, ll value) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (start > end || start > r || end < l) {
            return;
        }

        if (start >= l && end <= r) {
            tree[node] += (end - start + 1) * value;
            if (start != end) {
                lazy[2 * node + 1] += value;
                lazy[2 * node + 2] += value;
            }
            return;
        }

        ll mid = (start + end) / 2;
        updateRange(2 * node + 1, start, mid, l, r, value);
        updateRange(2 * node + 2, mid + 1, end, l, r, value);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    ll query(ll index) {
        return find(0, 0, n - 1, index - 1); 
    }

    ll find(ll node, ll start, ll end, ll idx) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (start == end) {
            return tree[node];
        }

        ll mid = (start + end) / 2;
        if (idx <= mid) {
            return find(2 * node + 1, start, mid, idx);
        } else {
            return find(2 * node + 2, mid + 1, end, idx);
        }
    }
};

int main() {
    ll n, p;
    cin >> n >> p;
    vector<ll> arr(n);
    vector<ll> res;

    for (ll i = 0; i < n; i++) {
        cin >> arr[i];
    }

    SegmentTree segTree(arr); 

    for (ll i = 0; i < p; i++) {
        ll type;
        cin >> type;

        if (type == 1) {
            ll a, b, x;
            cin >> a >> b >> x;
            segTree.updateRange(a, b, x);  
        } else if (type == 2) {
            ll k;
            cin >> k;
            res.push_back(segTree.query(k));  
        }
    }

    cout << ln;
    for (auto const &val : res) {
        cout << val << ln;
    }

    return 0;
}
