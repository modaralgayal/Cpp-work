#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
#define ln "\n";

int main() {
    ll n;
    cin >> n;
    
    vector<ll> values(n); 
    vector<ll> longest; 

    for (ll i = 0; i < n; i++) {
        cin >> values[i];
    }
    
    longest.push_back(values[0]);

    for (ll i = 1; i < n; i++) {

        if (values[i] > longest.back()) {
            longest.push_back(values[i]);
        } else {

            ll a = 0;
            ll b = longest.size() - 1;
            
            while (a < b) {
                ll mid = a + (b - a) / 2;
                if (longest[mid] < values[i]) {
                    a = mid + 1;
                } else {
                    b = mid;
                }
            }
            longest[a] = values[i]; 
        }
    }

    cout << longest.size() << "\n"; 
}
