#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
string const ln = "\n";

vector<vector<int>> adj;
vector<int> topoOrder;
vector<bool> visited;   

void dfs(int node) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
    topoOrder.push_back(node);
}

int main() {
    int n, m;
    cin >> n >> m;
    
    adj.resize(n + 1);      
    visited.resize(n + 1); 
    
    vector<pair<int, int>> edges; 
    
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        edges.push_back({a, b});
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cout << ln;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    
    reverse(topoOrder.begin(), topoOrder.end());
    
    vector<int> position(n + 1); 
    for (int i = 0; i < n; ++i) {
        position[topoOrder[i]] = i;
    }
    
    for (auto& edge : edges) {
        int a = edge.first;
        int b = edge.second;
        
        if (position[a] < position[b]) {
            cout << a << " " << b << ln;
        } else {
            cout << b << " " << a << ln;
        }
    }
    
    return 0;
}
