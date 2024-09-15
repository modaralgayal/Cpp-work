#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ln "\n"

ll calculateTotal(ll num, const vector<ll>& additionPossibilities) {
    if (num < 0) return 0; 

    string num_str = to_string(num);
    ll total = 0;

    for (int i = 0; i < num_str.size(); i++) {
        total += additionPossibilities[i];
    }

    ll prev = 0;
    for (int i = 0; i < num_str.size(); i++) {
        ll currentNumber = num_str[i] - '0'; 
        ll numsLeft = num_str.size() - i - 1;
        ll below = prev < currentNumber ? currentNumber - 1 : currentNumber;
        
        if (currentNumber != 0) {
            total += below * additionPossibilities[numsLeft];
        }

        if (currentNumber == prev) {
            return total;
        }
        prev = currentNumber;
    }

    return total + 1;
}

int main() {
    ll a, b;
    cin >> a >> b;
    if (a == 0 && b == 0) {
        cout << 1 << ln;
        return 0;
    }

    vector<ll> additionPossibilities(19);
    additionPossibilities[0] = 1;
    ll res = 1;
    for (int i = 1; i < 19; i++) {
        res *= 9;
        additionPossibilities[i] = res;
    }

    ll b_total = calculateTotal(b, additionPossibilities);
    ll a_total = calculateTotal(a - 1, additionPossibilities);

    cout << b_total - a_total << ln;

    return 0;
}
