#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll; 
ll n, q;
vector<ll> depth;
vector<vector<ll>> companyTree;
vector<vector<ll>> ancestor;

void dfs(ll node, ll parent, ll LOG) {
    ancestor[node][0] = parent;  
    for (int j = 1; j <= LOG; j++) {
        if (ancestor[node][j - 1] != -1) {
            ancestor[node][j] = ancestor[ancestor[node][j - 1]][j - 1];
        }
    }
    
    for (auto const& k : companyTree[node]) {
        if (k != parent) {  
            depth[k] = depth[node] + 1;  
            dfs(k, node, LOG);  
        }
    }
}

ll LCA(ll a, ll b, ll LOG) {
    if (depth[a] < depth[b]) {
        swap(a, b); 
    }

    for (int j = LOG; j >= 0; j--) {
        if (depth[a] - (1 << j) >= depth[b]) {
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
    scanf("%lld %lld", &n, &q);

    ll LOG = 0;
    while ((1 << (LOG + 1)) <= n) {
        LOG++;
    }

    depth.resize(n, 0);  
    companyTree.resize(n);
    ancestor.resize(n, vector<ll>(LOG + 1, -1)); 

    ll a, b;
    for (ll i = 1; i < n; i++) {
        scanf("%lld %lld", &a, &b);
        a--; 
        b--; 
        companyTree[a].push_back(b); 
        companyTree[b].push_back(a);  
    }

    dfs(0, -1, LOG);

    ll n, m;
    for (int i = 0; i < q; i++) {
        scanf("%lld %lld", &n, &m);
        n--;  
        m--; 
        printf("%lld\n", depth[n] + depth[m] - 2 * depth[LCA(n, m, LOG)]);
    }

    return 0;
}
