#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
string const ln = "\n";

vector<pair<int, int>> ans; 
vector<pair<int, int>> *graph; 
bool *visited, *checked; 
int *discTime, *minDiscoveryTime;
int discovered = 0;


void dfs(int node = 1, int parent = -1) {
    visited[node] = true;
    discovered++;
    discTime[node] = discovered;
    minDiscoveryTime[node] = discovered;

    for (auto &i : graph[node]) { 
        int neighbor = i.first;
        int edge_index = i.second;

        if (neighbor == parent) continue;

        if (!checked[edge_index]) {
            ans.push_back({node, neighbor});
            checked[edge_index] = true; 
        }

        if (visited[neighbor]) {
            minDiscoveryTime[node] = min(minDiscoveryTime[node], discTime[neighbor]);
        } else {
            dfs(neighbor, node);

            minDiscoveryTime[node] = min(minDiscoveryTime[node], minDiscoveryTime[neighbor]);

            if (minDiscoveryTime[neighbor] > discTime[node]) {
                cout << "IMPOSSIBLE" << ln;
                exit(0);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    graph = new vector<pair<int, int>>[n + 1]; 
    visited = new bool[n + 1](); 
    checked = new bool[m](); 
    discTime = new int[n + 1]();
    minDiscoveryTime = new int[n + 1](); 

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back({v, i});
        graph[v].push_back({u, i});
    }

    dfs();

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cout << "IMPOSSIBLE" << ln;
            return 0;
        }
    }

    for (const auto &edge : ans) {
        cout << edge.first << " " << edge.second << ln;
    }

    return 0;
}
