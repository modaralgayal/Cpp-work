#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

/*Just keep adding them and compare it to normal iteration,
 until a number doesnt match, then it found the smallest non possible*/

long long add(vector<int>& remaining) {
    long long sums = 0;
    for (size_t i = 0; i < remaining.size(); ++i) {
        if (sums + 1<remaining[i]) {
            break;
        } else sums += remaining[i];
    }
    return sums + 1;
}

int main() {
    long long n;
    vector<int> values;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        values.push_back(val);
    }
    sort(values.begin(), values.end());

    long long smallest = add(values);

    cout << smallest;

}