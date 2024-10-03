#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n;
vector<vector<int>> tree;
int maxDist = 0;
int farthestNode = 0;

void dfs(int node, int prev, int dist, vector<int>& distance) {
    distance[node] = dist;
    if (dist > maxDist) {
        maxDist = dist;
        farthestNode = node;
    }
    for (auto next : tree[node]) {
        if (next != prev) {
            dfs(next, node, dist + 1, distance);
        }
    }
}

int main() {
    cin >> n;

    tree.resize(n + 1);

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    vector<int> distance1(n + 1, -1);
    maxDist = 0;
    dfs(1, -1, 0, distance1); 


    vector<int> distance2(n + 1, -1);
    maxDist = 0;
    dfs(farthestNode, -1, 0, distance2); 

    cout << maxDist << endl;

    return 0;
}
