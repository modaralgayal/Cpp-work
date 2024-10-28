#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;
string const ln = "\n";
vector<vector<int>> tree; 
vector<int> degree;
int n;

void dfs (int node, int prev) {
    degree[node] = 1; 
    for (auto child : tree[node]) {
        if (child == prev) continue; 
        dfs(child, node);
        degree[node] += degree[child];
    } 
}


int getCentroid (int node, int prev) {

    for (auto child : tree[node]) {
        if (child == prev) continue;  
        if (degree[child] > n / 2) {
            return getCentroid(child, node);
        }
    }

    return node;
}

int main() {
    cin >> n;  
    tree.resize(n+1);
    degree.resize(n+1);
    
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    
    dfs(1, 0); 
    cout << getCentroid(1, 0) << ln; 
  
    return 0;
}
