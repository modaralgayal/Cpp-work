#include <iostream>

using namespace std;

int main() {
    long long n;
    cin >> n;
    long long t[n];
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    long long ans = 0;
    for (long long p = 1; p < n; p++) {
        if (t[p - 1] > t[p]) {
            ans += t[p - 1] - t[p];
            t[p] = t[p - 1];
        }
    }

    cout << ans << " ";
}