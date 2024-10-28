#include <iostream>
#include <vector>
#include <utility>

using namespace std;

string const ln = "\n";
vector<pair<int, int>> ans; 
vector<pair<int, int>> *graph; 
bool *degree; 
int *visited; 
int discovered = 0; 

void dfs(int node, int parent = -1) {
    visited[node] = ++discovered;

    for (int i = 0; i < graph[node].size(); i++) {
        int neighbor = graph[node][i].first; 
        int edge_index = graph[node][i].second; 

        
        if (neighbor == parent) continue;

        if (!visited[neighbor]) {
            dfs(neighbor, node); 
            if (degree[neighbor]) {
                ans[edge_index] = {node, neighbor}; 
                degree[node] ^= true; 
            } else {
                ans[edge_index] = {neighbor, node}; 
                degree[neighbor]  ^= true; 
            }
        } else if (visited[neighbor] < visited[node]) {
            degree[node] = !degree[node]; 
            ans[edge_index] = {node, neighbor}; 
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    graph = new vector<pair<int, int>>[n + 1]; 
    visited = new int[n + 1](); 
    degree = new bool[n + 1](); 
    ans.resize(m); 
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back({v, i}); 
        graph[v].push_back({u, i});
    }

    fill(degree + 1, degree + n + 1, true);

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    
    bool evenDegree = true;
    for (int i = 1; i <= n; i++) {
        if (!degree[i]) {
            evenDegree = false; 
            break; 
        }
    }

    cout << ln;
    if (evenDegree) {
        for (const auto &edge : ans) {
            cout << edge.first << " " << edge.second << ln;
        }
    } else {
        cout << "IMPOSSIBLE" << ln; 
    }

    return 0;
}
