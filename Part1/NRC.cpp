#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <vector>
#include <utility>
#include <algorithm>  

using namespace __gnu_pbds;
using namespace std;
typedef long long ll;
#define ln "\n"
typedef pair<ll, ll> pll;

typedef tree<pll,null_type,less<pll>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;;

int main() {
    ll n;
    cin >> n;
    
    vector<pair<pll, ll>> values(n);
    vector<ll> helper_1(n);
    vector<ll> helper_2(n);

    indexed_set contained_in;
    indexed_set containing;

    for (int i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        values[i] = {{a, b}, i};
    }

    sort(values.begin(), values.end(), [](const pair<pll, ll>& a, const pair<pll, ll>& b) {
        if (a.first.first == b.first.first) return a.first.second > b.first.second;
        return a.first.first < b.first.first;
    });
    
    cout << ln;
    for (int i = n - 1; i >= 0; i--) {
        ll current_second = values[i].first.second;
        containing.insert({current_second, -1*i});
        helper_1[values[i].second] = 
            containing.order_of_key({current_second, -1*i});
        
    }

    cout << ln;
    for (auto const& val : helper_1) {
        cout << val << " ";
    }   
    
    for (int i = 0; i < n; i++) {
        ll current_second = values[i].first.second;
        contained_in.insert({current_second, -1*i});        
        helper_2[values[i].second] = 
            contained_in.size() - contained_in.order_of_key({current_second, -1*i}) - 1;
    }

    cout << ln;
    for (auto const& val : helper_2) {
        cout << val << " ";
    }
    

    return 0;
}
