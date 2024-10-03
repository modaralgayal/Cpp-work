#include <iostream>
#include <vector>
#include <cstring>


using namespace std;
string const ln = "\n";
// Code inpired by usaco guide Chapter 14.3
int n;
vector<vector<int>> tree;
vector<int> max1;
vector<int> max2;
vector<int> child;

void dfs(int node, int prev) {
    max1[node] = 0;
    max2[node] = 0;
    for (auto x : tree[node]) {
        if (x == prev) continue;
        dfs(x, node);
        if (max1[x] + 1 > max1[node]) {
            max2[node] = max1[node];
            max1[node] = max1[x] + 1;
            child[node] = x;
        } else if (max1[x] + 1 > max2[node]) {
            max2[node] = max1[x] + 1;
        }
    }
}


void dfs2 (int node, int prev) {
    for (auto const x : tree[node]) {
        if (x == prev) continue;
        if (child[node] == x) {
            if (max1[x] < max2[node] + 1) {
                max2[x] = max1[x];
                max1[x] = max2[node] + 1;
                child[x] = node;
            } else {
                max2[x] = max(max2[x], max2[node] + 1);
            }
        } else {
            max2[x] = max1[x];
            max1[x] = max1[node] + 1;
            child[x] = node;
        }
        dfs2(x, node);
    }
}


int main() {
    cin >> n;
    tree.resize(n + 1);
    max1.resize(n + 1, 0); 
    max2.resize(n + 1, 0);  
    child.resize(n + 1, 0);
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

	dfs(1, -1);
	dfs2(1, -1);

    for (int i = 1; i <= n; i++) {
        cout << max1[i] << " ";
    }
    cout << ln;

    return 0;
}
