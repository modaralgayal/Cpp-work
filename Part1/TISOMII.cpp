#include <iostream>
#include <vector>
#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;

map<vector<ll>, ll> LN_ids; 
ll lvl = 0; 
vector<ll> centroid1; 
vector<ll> centroid2; 
vector<vector<ll>> degree1, degree2;

ll findID(ll node, ll parent, const vector<vector<ll>>& tree) {
    vector<ll> leafNodes;
    
    for (ll neighbor : tree[node]) {
        if (neighbor != parent) {
            leafNodes.push_back(findID(neighbor, node, tree));
        }
    }
    
    sort(leafNodes.begin(), leafNodes.end());

    if (LN_ids.count(leafNodes) == 0) {
        LN_ids[leafNodes] = lvl++;
    }
    
    return LN_ids[leafNodes];
}

void dfs(ll node, ll prev, const vector<vector<ll>>& tree, vector<vector<ll>>& degree, ll sumId) {
    ll childNodes = 0; 
    for (auto child : tree[node]) {
        if (child == prev) continue;
        dfs(child, node, tree, degree, sumId); 
        childNodes += degree[sumId][child] + 1;
    }
    degree[sumId][node] = childNodes; 
}

void getCentroid(ll node, ll prev, ll n, vector<vector<ll>>& degree, const vector<vector<ll>>& tree, int sumId) {
    bool center = true;

    for (auto child : tree[node]) {
        if (child == prev) continue;
        getCentroid(child, node, n, degree, tree, sumId);
        
        if (degree[sumId][child] + 1 > n / 2) {
            center = false; 
        }
    }

    if (n - degree[sumId][node] - 1 > (n / 2)) {
        center = false; 
    }

    if (center) {
        if (sumId == 0) {
            centroid1.push_back(node);
        } else {
            centroid2.push_back(node);
        }
    }
}

int main() {
    ll tests;
    scanf("%lld", &tests);
    
    while (tests--) {
        ll n;
        scanf("%lld", &n);
        
        LN_ids.clear();
        lvl = 0;
        centroid1.clear();
        centroid2.clear();
        
        vector<vector<ll>> tree1(n + 1);
        vector<vector<ll>> tree2(n + 1);
        
        for (ll i = 0; i < n - 1; i++) {
            ll a, b;
            scanf("%lld %lld", &a, &b);
            tree1[a].push_back(b);
            tree1[b].push_back(a);
        }

        for (ll j = 0; j < n - 1; j++) {
            ll a, b;
            scanf("%lld %lld", &a, &b);
            tree2[a].push_back(b);
            tree2[b].push_back(a);
        }

        degree1.assign(2, vector<ll>(n + 1, 0)); 
        degree2.assign(2, vector<ll>(n + 1, 0)); 
        
        dfs(1, -1, tree1, degree1, 0);
        dfs(1, -1, tree2, degree2, 1); 
        
        getCentroid(1, -1, n, degree1, tree1, 0);
        getCentroid(1, -1, n, degree2, tree2, 1);

        bool isIsomorphic = false;

        for (auto c1 : centroid1) {
            for (auto c2 : centroid2) {
                if (findID(c1, -1, tree1) == findID(c2, -1, tree2)) {
                    isIsomorphic = true;
                    break;
                }
            }
            if (isIsomorphic) break;
        }

        if (isIsomorphic) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}
