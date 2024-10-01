#include <iostream>
#include <vector>
#include <queue>
#include <utility> 
 
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
string const ln = "\n";
 
vector<vector<ll>> graph; 
 
void dfs(ll at, vector<ll>& disc, vector<ll>& low, vector<ll>& parent, vector<pll>& bridges, ll& time) {
    disc[at] = time;
    low[at] = time;
    time++;
    for (auto val : graph[at]) {
        if (disc[val] == -1) {
            parent[val] = at;
            dfs(val, disc, low, parent, bridges, time);
            low[at] = min(low[at], low[val]);
 
            if (low[val] > disc[at]) {
                bridges.push_back({at, val});
            }
        }
        else if (val != parent[at]) {
            low[at] = min(low[at], disc[val]);
        }
    }
}
 
int main() {
    ll n, m;
    cin >> n >> m; 
 
    graph.resize(n + 1); 
    vector<ll> disc(n + 1, -1);
    vector<ll> low(n + 1, -1);
    vector<ll> parent(n + 1, -1);
    vector<pll> bridges;
 
    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
 
    for (ll i = 1; i <= n; i++) {
        if (disc[i] == -1) {
            ll time = 0; 
            dfs(i, disc, low, parent, bridges, time);
        }
    }
 
    cout << bridges.size() << ln;
    for (auto it : bridges)
        cout << it.first << " " << it.second << ln;
 
    return 0; 
}