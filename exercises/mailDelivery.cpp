#include <iostream>
#include <vector>
#include <set>
#include <stack>

using namespace std;

typedef long long ll;
string const ln = "\n";

void dfs(vector<set<ll>>& graph, vector<bool>& visited, ll at) {
    visited[at] = true;
    for (ll next : graph[at]) {
        if (!visited[next]) {
            dfs(graph, visited, next);
        }
    }
}

ll findGraphs(vector<set<ll>>& graph, vector<ll>& connectable, ll n) {
    vector<bool> visited(n + 1, false); 
    ll count = 0;
    
    for (ll i = 1; i <= n; i++) {  
        if (!visited[i] && !graph[i].empty()) {
            count++;
            connectable.push_back(i); 
            dfs(graph, visited, i);
        }
    }
    return count;
}

int main() {
    ll n, m;
    cin >> n >> m;  
    vector<set<ll>> graph(n + 1);  
    vector<ll> result;
    stack<ll> stack;

    for (ll i = 0; i < m; i++) {
        ll u, v;
        cin >> u >> v;  
        graph[u].insert(v);
        graph[v].insert(u);
    }

    bool possible = true;
    for (int i = 1; i <= n; i++) { 
        if (graph[i].size() % 2 != 0) {
            possible = false;
            break;
        }
    }

    vector<ll> connectable;
    if (findGraphs(graph, connectable, n) != 1) {
        possible = false;
    }

    if (!possible) {
        cout << "IMPOSSIBLE" << ln;
        return 0; 
    }

    stack.push(1); 
    while (!stack.empty()) {
        int x = stack.top();
        if (!graph[x].empty()) {
            ll destination = *graph[x].begin();
            graph[x].erase(graph[x].begin());  
            graph[destination].erase(x);       
            stack.push(destination);          
        } else {
            result.push_back(x);
            stack.pop();
        }
    }

    if (result.size() != m+1) {
        cout << "IMPOSSIBLE" << ln;
        return 0;
    }

    cout << ln;
    for (auto val : result) {
        cout << val << " ";
    }
    cout << ln;

    return 0;
}
