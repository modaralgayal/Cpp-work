#include <iostream>
#include <string>

using namespace std;
typedef long long ll;
string const ln = "\n";

// artikkeli ratkaisusta on https://cp-algorithms.com/string/lyndon_factorization.html
int main() {
    string arr;
    cin >> arr;
    string lynStr = arr + arr;
    ll n = lynStr.size();     
    int i = 0, ans = 0;       
    while (i < n / 2) {       
        ans = i;              
        int j = i + 1, k = i; 
        while (j < n && lynStr[k] <= lynStr[j]) {
            if (lynStr[k] < lynStr[j]) {
                k = i;
                j++;
            } else {
                k++;
                j++;
            }
        }
        while (i <= k) {
            i += j - k;
        }
    }

    cout << lynStr.substr(ans, arr.size()) << ln;
    return 0;
}
