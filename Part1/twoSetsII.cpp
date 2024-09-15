#include <iostream>
#include <vector>
using namespace std;
 
int main() {
    long long n;
    cin >> n; 
    long long sumOfVals = (n * (n + 1)) / 2;
    if (sumOfVals%2 != 0) {
        cout << 0 << "\n";
    }
    vector<long long> previous(sumOfVals/2 + 1);
    fill(previous.begin(), previous.end(), 0);
    previous[0] = 1;
 
    for (long long i = 1; i <= n; i++) {
        for (long long j = sumOfVals/2; j >= i; j--) {
            previous[j] = (previous[j] + previous[j - i]) % 1000000007;
        }
    }

    long long inverse = 500000004;
    if (sumOfVals%2 == 0) {
        cout << ((previous[sumOfVals/2]) * inverse) % 1000000007 << "\n";
    }
}