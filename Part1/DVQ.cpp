#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

using namespace std;
typedef long long ll;

#define ln "\n"

struct Query {
    ll a, b, i, result;
    Query(ll a, ll b, ll i): a(a), b(b), i(i), result(0) {}
    bool operator<(const Query &other) const {  
        return b < other.b;
    }
};

void change(vector<ll>& tree, ll idx, ll val, ll n) {
    idx += n;  
    tree[idx] = val;
    for (idx /= 2; idx >= 1; idx /= 2) {
        tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
    }
}

ll getSum(vector<ll>& tree, ll a, ll b, ll p) {
    a += p; b += p;
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
}

int main() {
    ll n, q;
    cin >> n >> q;
    vector<ll> values(n);   
    ll treeSize = 1;

    while (treeSize < n) treeSize *= 2;
    vector<ll> tree(treeSize * 2, 0); 
    map<ll, ll> compression;

    for (ll i = 0; i < n; i++) {
        cin >> values[i];
    }
    vector<Query> queries;

    for (int i = 0; i < q; i++) {
        ll a, b;
        cin >> a >> b;
        queries.push_back(Query(a - 1, b - 1, i)); 
    }

    sort(queries.begin(), queries.end());

    ll QueryOrder = 0;
    for (int i = 0; i < n; i++) {
        if (compression.count(values[i])) {
            change(tree, compression[values[i]], 0, treeSize); 
        }
        compression[values[i]] = i;  
        change(tree, i, 1, treeSize);  

        while (QueryOrder < q && queries[QueryOrder].b == i) {
            queries[QueryOrder].result = getSum(tree, queries[QueryOrder].a, queries[QueryOrder].b, treeSize);
            QueryOrder++;
        }
    }

    sort(queries.begin(), queries.end(), [](const Query &x, const Query &y) {
        return x.i < y.i; 
    });

    for (const auto& query : queries) {
        cout << query.result << ln;
    }

    return 0;
}
