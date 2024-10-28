#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;
typedef long long ll;
string const ln = "\n";

const ll MAX = 1e12; 

int main() {
    ll n, m; 
    cin >> n >> m;
    
    vector<vector<pair<ll, ll>>> graph(n+1);
    vector<ll> fullPrice(n+1);  
    vector<ll> discount(n+1);   
    
    priority_queue< 
    pair<ll, pair<ll,bool>>, 
    vector<pair<ll, pair<ll,bool>>>, 
    greater<pair<ll, pair<ll,bool>>>
    > pq;

    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});  
    }

    for(ll i = 1; i <= n; ++i) {
        fullPrice[i] = MAX; 
        discount[i] = MAX;
    }

    fullPrice[1] = 0;
    discount[1] = 0;

    pq.push({0, {1, false}}); 
    
    while (!pq.empty()) {
        ll cost = pq.top().first;
        ll dest = pq.top().second.first;
        bool flag = pq.top().second.second; 
        pq.pop();

        if (flag) {
            if (discount[dest] < cost) continue;
        } else { 
            if (fullPrice[dest] < cost) continue;
        }

        for (auto const& trip : graph[dest]) {
            ll v = trip.first, c = trip.second;
            if (!flag) {  
                if (fullPrice[v] > c + cost) {
                    fullPrice[v] = c + cost;
                    pq.push({c + cost, {v, false}}); 
                } 
                if (discount[v] > cost + (c / 2)) { 
                    discount[v] = cost + (c / 2);
                    pq.push({cost + (c / 2), {v, true}});  
                } 
            } else {  
                if (discount[v] > cost + c) {
                    discount[v] = cost + c;
                    pq.push({cost + c, {v, true}});
                }
            }
        }
    }
    
    cout << ln;
    //for (auto e : discount) {
    //    cout << e << " ";
    //} 
    cout << discount[n] << ln;
    
    return 0;
}
