#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
string const ln = "\n";
typedef long long ll;

ll n;
vector<vector<ll>> tree;
vector<ll> subTreeSize;
vector<ll> subTreeDist;
vector<ll> result;

void dfs(ll node, ll prev) {
    subTreeSize[node] = 1;
    for (ll x : tree[node]) {
        if (x == prev) continue;
        dfs(x, node);
        subTreeSize[node] += subTreeSize[x];
        subTreeDist[node] += subTreeDist[x] + subTreeSize[x];
    }
}

void dfs2(ll node, ll prev) {
    result[node] = result[prev] - subTreeSize[node] + n - subTreeSize[node];  
    for (ll x : tree[node]) {
        if (x == prev) continue;
        dfs2(x, node);  
    }
}

int main() {
    cin >> n;
    tree.resize(n + 1);
    subTreeDist.resize(n + 1, 0); 
    subTreeSize.resize(n + 1, 0);  
    result.resize(n + 1, 0);
    for (ll i = 1; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    dfs(1, -1);
    result[1] = subTreeDist[1];
    for (ll x : tree[1]) {
        dfs2(x, 1);
    }

    for (ll i = 1; i <= n; i++) {
        cout << result[i] << " ";  
    }
    cout << ln;

    return 0;
}
