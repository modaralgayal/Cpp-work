#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
string const ln = "\n";

int main() {
    int n;
    scanf("%d", &n);

    while (n--) {
        int p;
        cin >> p;
        vector<int> powers;
        for (int j = 2; j * j <= p; j++) {
            if (p % j == 0) {
                int count = 0; 
                while (p % j == 0) {
                    count++;
                    p /= j;
                }
                powers.push_back(count);  
            }
        }

        if (p != 1) {
            powers.push_back(1);  
        }
        int divisors = 1;
        for (int val : powers) {
            divisors *= (val + 1);
        }

        cout << divisors << ln;  
    }

}
