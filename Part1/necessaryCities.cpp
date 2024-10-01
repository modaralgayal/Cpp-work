#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
string const ln = "\n";

vector<vector<ll>> graph; 

void dfs(ll at, vector<ll>& disc, vector<ll>& low, vector<ll>& parent, set<ll>& articulationPoints, ll& time, bool isRoot) {
    disc[at] = time;
    low[at] = time;
    time++;
    
    ll children = 0;

    for (auto val : graph[at]) {
        if (disc[val] == -1) {
            parent[val] = at;
            children++;
            dfs(val, disc, low, parent, articulationPoints, time, false);

            low[at] = min(low[at], low[val]);

            if (!isRoot && low[val] >= disc[at]) {
                articulationPoints.insert(at);
            }
        } else if (val != parent[at]) { 
            low[at] = min(low[at], disc[val]);
        }
    }

    if (isRoot && children > 1) {
        articulationPoints.insert(at);
    }
}

int main() {
    ll n, m;
    cin >> n >> m; 

    graph.resize(n + 1); 
    vector<ll> disc(n + 1, -1);
    vector<ll> low(n + 1, -1);
    vector<ll> parent(n + 1, -1);
    set<ll> articulationPoints; 

    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    ll time = 0; 
    for (ll i = 1; i <= n; i++) {
        if (disc[i] == -1) {
            dfs(i, disc, low, parent, articulationPoints, time, true);
        }
    }

    cout << articulationPoints.size() << ln;
    for (auto city : articulationPoints)
        {
            cout << city << " ";
    }

    cout << ln;

    return 0; 
}
