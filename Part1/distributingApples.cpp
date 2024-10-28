#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

struct Factorial {
    vector<ll> factorial;
    vector<ll> inverseFactorial;
    ll MOD;

    ll modularBinaryExponentiation(ll base, ll exp) {
        ll res = 1;
        while (exp > 0) {
            if (exp % 2 == 1) {
                res = (res * base) % MOD;
            }
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

    Factorial(ll n, ll _modulo) {
        factorial.resize(n + 1);
        inverseFactorial.resize(n + 1);
        MOD = _modulo;

        factorial[0] = 1;
        for (ll i = 1; i <= n; i++) {
            factorial[i] = (i * factorial[i - 1]) % MOD;
        }

        inverseFactorial[n] = modularBinaryExponentiation(factorial[n], MOD - 2);
        for (ll i = n - 1; i >= 0; i--) {
            inverseFactorial[i] = (inverseFactorial[i + 1] * (i + 1)) % MOD;
        }
        inverseFactorial[0] = 1;
    }

    ll factorialOf(ll x) {
        return factorial[x];
    }

    ll invFactorial(ll x) {
        return inverseFactorial[x];
    }

    ll binomialCoefficient(ll a, ll b) {
        if (b > a) return 0; 
        return (((factorial[a] * inverseFactorial[a - b]) % MOD) * inverseFactorial[b]) % MOD;
    }
};

int main() {
    Factorial FC(2*1e6, 1e9 + 7);

    ll n, m;
    cin >> n >> m;
    cout << FC.binomialCoefficient(n + m - 1, n - 1) << "\n";

    return 0;
}
