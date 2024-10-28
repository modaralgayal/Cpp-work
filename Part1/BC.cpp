#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
// tässä käytetään Fermat's little Teoria.
struct Factorial {
    vector<ll> factorial;
    vector<ll> inverseFactorial;
    int MOD;

    ll modularBinaryExponentiation(int base, int exp) {
        if (exp == 0) {
            return 1;
        }
        ll res = modularBinaryExponentiation(base, exp / 2);
        res = (res * res) % MOD;
        if (exp % 2 == 1) {
            res = (res * base) % MOD; 
        }
        return res;
    }

    Factorial(int n, int _modulo) {
        factorial.resize(n + 1);
        inverseFactorial.resize(n + 1);
        MOD = _modulo;

        factorial[0] = 1;
        for (int i = 1; i <= n; i++) {
            factorial[i] = (i * factorial[i - 1]) % MOD;
        }

        inverseFactorial[n] = modularBinaryExponentiation(factorial[n], MOD - 2);
        for (int i = n - 1; i >= 0; i--) {
            inverseFactorial[i] = (inverseFactorial[i + 1] * (i + 1)) % MOD;
        }
        inverseFactorial[0] = 1;
    }

    int factorialOf(int x) {
        return factorial[x];
    }

    int invFactorial(int x) {
        return inverseFactorial[x];
    }

    int binomialCoefficient(int a, int b) {
        if (b > a) return 0; 
        return (((factorial[a] * inverseFactorial[a - b]) % MOD) * inverseFactorial[b]) % MOD;
    }
};

int main() {
    ll n;
    cin >> n;

    Factorial FC(1e6, 1e9 + 7);

    while (n--) {
        ll a, b;
        cin >> a >> b;
        cout << FC.binomialCoefficient(a, b) << "\n";
    }

    return 0;
}
