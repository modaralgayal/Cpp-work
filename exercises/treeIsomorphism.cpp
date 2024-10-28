#include <iostream>
#include <vector>
#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;
string const ln = "\n";
typedef long long ll;
map<vector<ll>,ll> LN_ids;
ll lvl = 0;

ll dfs(ll node, ll parent, const vector<vector<int>>& tree) {
    ll leaves = 0;
    vector<ll> leafNodes;

    for (int neighbor : tree[node]) {
        if (neighbor != parent) { 
            leafNodes.push_back(dfs(neighbor, node, tree));
            leaves++; 
        }
    }
    sort(leafNodes.begin(), leafNodes.end());

    if (leaves==0) {
        return 1;
    } else {
        if (LN_ids.count(leafNodes) == 0) {
            LN_ids[leafNodes]=lvl++;
        }
        return LN_ids[leafNodes];
    }

}

int main() {
    ll tests;
    scanf("%lld", &tests);
    while (tests--) {
        int n;
        scanf("%d", &n); 

        vector<vector<int>> tree1(n + 1);
        vector<vector<int>> tree2(n + 1);

        for (int i = 0; i < n - 1; i++) {
            int a, b;
            scanf("%d %d", &a, &b); 
            tree1[a].push_back(b);
            tree1[b].push_back(a);
        }

        for (int j = 0; j < n - 1; j++) {
            int a, b;
            scanf("%d %d", &a, &b);  
            tree2[a].push_back(b);
            tree2[b].push_back(a);
        }

        ll sum1 = dfs(1, -1, tree1); 
        ll sum2 = dfs(1, -1, tree2);
        if (sum1 == sum2) {
            printf("YES\n");
        } else {
            printf("NO\n"); 
        }
    }
    return 0;
}
