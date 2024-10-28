#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

ll count(ll n) {
    if (n == 0)
        return 0;
    ll x = 0;
    while ((1LL << (x + 1)) <= n) {
        x++;
    }
    return (x * (1LL << (x - 1))) + (n - (1LL << x) + 1) + count(n - (1LL << x));
}

int main() {
    ll n;
    cin >> n;
    ll res = count(n);
    cout << res << "\n";
    return 0;
}
