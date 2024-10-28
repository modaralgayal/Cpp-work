#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef long long ll;
const ll INF = 1e18;
const int MOD = 1e9 + 7;

void dijkstra(vector<vector<pair<ll, ll>>> &graph, vector<ll> &dist, vector<ll> &routes, vector<ll> &min_ways, vector<ll> &max_ways) {
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;  
    
    dist[1] = 0;          
    routes[1] = 1;      
    min_ways[1] = 0;     
    max_ways[1] = 0;      
    pq.push({0, 1});  

    while (!pq.empty()) {
        ll d = pq.top().first;
        ll u = pq.top().second; 
        pq.pop();

        if (d > dist[u]) continue; 

        for (auto edge : graph[u]) {
            ll v = edge.first;  
            ll weight = edge.second; 

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                routes[v] = routes[u];
                min_ways[v] = min_ways[u] + 1;
                max_ways[v] = max_ways[u] + 1; 
                pq.push({dist[v], v}); 
            } 
            else if (dist[v] == dist[u] + weight) {
                routes[v] = (routes[v] + routes[u]) % MOD; 
                min_ways[v] = min(min_ways[v], min_ways[u] + 1);
                max_ways[v] = max(max_ways[v], max_ways[u] + 1);
            }
        }
    }
}

int main() {
    ll n, m;
    cin >> n >> m;  
    vector<vector<pair<ll, ll>>> graph(n + 1); 
    vector<ll> dist(n + 1, INF);  
    vector<ll> routes(n + 1, 0);
    vector<ll> min_ways(n + 1, INF);
    vector<ll> max_ways(n + 1, 0);

    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;  
        graph[u].push_back({v, w});
    }

    dijkstra(graph, dist, routes, min_ways, max_ways);  

    cout << dist[n] << " " << routes[n] << " " << (min_ways[n] == INF ? -1 : min_ways[n]) << " " << max_ways[n] << endl;

    return 0;
}
