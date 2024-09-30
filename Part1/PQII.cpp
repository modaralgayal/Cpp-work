#include <cmath>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using ll = long long;
string const ln = "\n";

void readGraph(ll n, vector<ll>& next, vector<vector<ll>>& before) {
    for (ll p = 0; p < n; p++) {
        cin >> next[p];
        next[p]--; 
        before[next[p]].push_back(p);  
    }
}

void detectCycles(ll n, vector<ll>& next, vector<ll>& cycle_id, vector<map<ll, ll>>& cycles) {
    for (ll p = 0; p < n; p++) {
        if (cycle_id[p] != -2) continue;  

        vector<ll> path{p};
        ll at = p;

        while (cycle_id[next[at]] == -2) {
            at = next[at];
            cycle_id[at] = -3; 
            path.push_back(at);
        }

        map<ll, ll> cycle;
        bool in_cycle = false;
        for (ll i : path) {
            if (i == next[at]) {
                in_cycle = true;  
            }
            if (in_cycle) {
                cycle[i] = cycle.size();  
            }
            if (in_cycle) {
                cycle_id[i] = cycles.size();  
            } else {
                cycle_id[i] = -1;  
            }
        }
        cycles.push_back(cycle);
    }
}

void bfsDistances(ll n, vector<ll>& next, vector<ll>& cycle_id, vector<ll>& cyc_dist, vector<vector<ll>>& before) {
    for (ll p = 0; p < n; p++) {
        if (cycle_id[next[p]] == -1 || cycle_id[p] != -1){ continue;}
        cyc_dist[p] = 1;
        vector<ll> stack(before[p]);
        while (!stack.empty()) {
            ll current = stack.back();
            stack.pop_back();
            cyc_dist[current] = cyc_dist[next[current]] + 1;
            stack.insert(stack.end(), before[current].begin(), before[current].end());
        }
    }
}

void setupBinaryLifting(ll n, vector<ll>& next,vector<vector<ll>>& pow2_ends, ll max_log) {
    for (ll p = 0; p < n; p++) {
        pow2_ends[p][0] = next[p]; 
    }

    for (ll i = 1; i <= max_log; i++) {
        for (ll p = 0; p < n; p++) {
            pow2_ends[p][i] = pow2_ends[pow2_ends[p][i - 1]][i - 1];
        }
    }
}

ll advance(ll place, ll dist, ll log2, const vector<vector<ll>>& pow2_ends) {
    for (ll pow = log2; pow >= 0; pow--) {
        if ((dist & (1ll << pow)) != 0) {
            place = pow2_ends[place][pow];
        }
    }
    return place;
}

void processQueries(ll q, ll log2, ll n, vector<ll>& cycle_id, vector<ll>& cyc_dist, vector<ll>& next, vector<vector<ll>>& pow2_ends, vector<map<ll, ll>>& cycles) {
    for (ll i = 0; i < q; i++) {
        ll u, v;
        cin >> u >> v;
        u--; v--;

        if (cycle_id[pow2_ends[u][log2]] != cycle_id[pow2_ends[v][log2]]) {
            cout << -1 << ln; 
            continue;
        }
        

        if (cycle_id[u] != -1 || cycle_id[v] != -1) {  
            if (cycle_id[u] != -1 && cycle_id[v] == -1) {
                cout << -1 << ln; 
                continue;
            }

            ll distance = cyc_dist[u];
            ll u_cycle_node = advance(u, cyc_dist[u], log2, pow2_ends);

            map<ll, ll>& cyc = cycles[cycle_id[u_cycle_node]];
            ll u_idx = cyc[u_cycle_node]; 
            ll v_idx = cyc[v];  
            ll diff = (u_idx <= v_idx) ? v_idx - u_idx : cyc.size() - (u_idx - v_idx);
            cout << distance + diff << ln;
        } else {
            if (cyc_dist[v] > cyc_dist[u]) {
                cout << -1 << ln; 
                continue;
            }

            ll diff = cyc_dist[u] - cyc_dist[v];
            if (advance(u, diff, log2, pow2_ends) == v) {
                cout << diff << '\n';
            } else {
                cout << -1 << '\n';
            }
        }
    }
}

int main() {
    ll n, q;
    cin >> n >> q;

    vector<ll> next(n);
    vector<vector<ll>> before(n);
    readGraph(n, next, before);

    vector<ll> cycle_id(n, -2); 
    vector<map<ll, ll>> cycles;  
    detectCycles(n, next, cycle_id, cycles);

    vector<ll> cyc_dist(n, 0);
    bfsDistances(n, next, cycle_id, cyc_dist, before);

    ll max_log = static_cast<ll>(ceil(log2(n)));
    vector<vector<ll>> pow2_ends(n, vector<ll>(max_log + 1));
    setupBinaryLifting(n, next, pow2_ends, max_log);

    processQueries(q, max_log, n, cycle_id, cyc_dist, next, pow2_ends, cycles);

    return 0;
}