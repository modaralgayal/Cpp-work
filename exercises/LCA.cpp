#include <iostream>
#include <vector>

using namespace std;

typedef long long ll; 
string const ln = "\n";
ll n, q;
vector<ll> depth;
vector<vector<ll>> companyTree;
vector<vector<ll>> ancestor;

void dfs(ll a, ll LOG) {
    for (auto const k : companyTree[a]) {
        depth[k] = depth[a] + 1;
        ancestor[k][0] = a; 
        for (int j = 1; j <= LOG; j++) {
            if (ancestor[k][j-1] != -1)
                ancestor[k][j] = ancestor[ancestor[k][j-1]][j-1];
        }
        dfs(k, LOG);  
    }
}

ll LCA(ll a, ll b, ll LOG) {
    if (depth[a] < depth[b]) {
        swap(a, b);
    }

    ll k = depth[a] - depth[b];  
    for (int j = LOG; j >= 0; j--) {
        if (k & (1 << j)) {
            a = ancestor[a][j]; 
        }
    }
    if (a == b) {
        return a;
    }

    for (int j = LOG; j >= 0; j--) {
        if (ancestor[a][j] != ancestor[b][j]) {
            a = ancestor[a][j];
            b = ancestor[b][j];
        }
    }
    return ancestor[a][0]; 
}

int main() {
    cin >> n >> q;

    ll LOG = 0;
    while ((1 << (LOG + 1)) <= n) {
        LOG++;
    }

    depth.resize(n, 0); 
    companyTree.resize(n); 
    ancestor.resize(n, vector<ll>(LOG + 1, -1));

    for (ll i = 2; i <= n; i++) {
        ll boss;
        cin >> boss;
        boss--; 
        companyTree[boss].push_back(i - 1);
    }

    dfs(0, LOG); 
    cout << ln;
    for (int i = 0; i < q; i++) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--; 
        cout << LCA(a, b, LOG) + 1 << endl; 
    }

    return 0;
}