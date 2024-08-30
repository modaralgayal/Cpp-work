#include <iostream>
#include <vector>

using namespace std;


int main() {
    int n;
    cin >> n;

    vector<int> values(n);
    vector<bool> removed(n, false); 

    for (int i = 0; i < n; ++i) {
        values[i] = i + 1;
    }

    vector<int> custom_values;
    int c = 0;
    int count = 0; 

    while (count < n) {
        int skip = 0;
        while (skip < 2) {
            if (!removed[c]) {
                ++skip;
            }
            c = (c + 1) % n;
        }
        c = (c - 1 + n) % n;
        removed[c] = true;
        custom_values.push_back(values[c]);
        ++count;
        c = (c + 1) % n;
    }

     for (int i = 0; i < n; ++i) {
        cout << custom_values[i] << " ";
    }
}