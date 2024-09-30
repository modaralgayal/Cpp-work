#include <iostream>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;
typedef long long ll;
const ll MAX = 5*1e4 + 1;
bitset<MAX> ans[MAX];  
vector<ll> adj[MAX];  

int main() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> graph(m); 
    queue<ll> q;
    vector<ll> indeg(n + 1, 0);
    
    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        graph[i] = {a, b}; 
    }

    
    for (ll i = 0; i < m; i++) {
        ll u = graph[i][0], v = graph[i][1];
        adj[v].push_back(u);  
        indeg[u]++;  
    }


    for (ll i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            ans[i].set(i);  
            q.push(i);  
        }
    }

    while (!q.empty()) {
        ll u = q.front();
        q.pop();

        for (ll v : adj[u]) {
            ans[v] |= ans[u];  
            indeg[v]--;  
            if (indeg[v] == 0) { 
                ans[v].set(v); 
                q.push(v);
            }
        }
    }

    for (ll i = 1; i <= n; i++) {
        cout << ans[i].count() << " "; 
    }
    cout << endl;

    return 0;
}
