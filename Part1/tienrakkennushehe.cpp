#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

ll n;

void dfs(vector<vector<ll>>& graph, vector<bool>& visited, ll at) {
    visited[at] = true;
    for (ll next : graph[at]) {
        if (!visited[next]) {
            dfs(graph, visited, next);
        }
    }
}


ll findGraphs(vector<vector<ll>>& graph, vector<ll>& connectable) {
    vector<bool> visited(n, false); 
    ll count = 0;
    
    for (ll i = 0; i < n; i++) {
        if (!visited[i]) {
            count++;
            connectable.push_back(i);
            dfs(graph, visited, i);

        }
    }
    
    return count;
}

int main() {
    ll m; 
    cin >> n >> m;
    
    vector<vector<ll>> graph(n);
    vector<ll> connectable;

    for (ll i = 0; i < m; i++) {
        ll a, b;
        cin >> a >> b;
        a--; b--; 
        
        graph[a].push_back(b);  
        graph[b].push_back(a);
    }

    ll result = findGraphs(graph, connectable);
    
    cout << result - 1 << endl;

    for (ll i = 1; i < result; i++) {
        cout << connectable[i-1] + 1 << " " << connectable[i] + 1 << endl;
    }
    
    return 0;
}