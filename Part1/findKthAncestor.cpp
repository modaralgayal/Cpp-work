#include <iostream>
#include <vector>

using namespace std;
typedef long long ll; 
string const ln = "\n";
ll n, q;

int main () {
    cin >> n >> q;
    
    ll LOG = 0;
    while((1 << (LOG + 1)) <= n) {
        LOG++;
    }

    vector<ll> values(n);  
    vector<pair<ll, ll>> queries(q); 
    
    for (int i = 1; i < n; i++) {
        cin >> values[i]; 
        values[i]--;  
    }

    for (int i = 0; i < q; i++) {
        ll a, k;
        cin >> a >> k;
        a--;  
        queries[i] = {a, k};
    }

    vector<vector<ll>> companyTree(n, vector<ll>(LOG + 1, -1));

    for (int i = 1; i < n; i++) {
        companyTree[i][0] = values[i]; 
    }

    for (int j = 1; j <= LOG; j++) {
        for (int i = 0; i < n; i++) {
            if (companyTree[i][j-1] != -1) {
                companyTree[i][j] = companyTree[companyTree[i][j-1]][j-1];
            }
        }
    }

    for (const auto& query : queries) {
        ll a = query.first;
        ll k = query.second;

        for (int i = 0; i <= LOG; i++) {
            if (k & (1 << i)) { 
                a = companyTree[a][i];
                if (a == -1) break; 
            }
        }

        cout << (a == -1 ? -1 : a + 1) << ln;
    }

    return 0;
}
