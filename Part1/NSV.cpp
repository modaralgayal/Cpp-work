#include <iostream>
#include <vector>
#include <stack>

using namespace std;
#define ln "\n"

int main () {
    int n; 
    cin >> n;
    
    vector<int> values(n);
    vector<int> results(n, -1);

    stack<int> maxHeap;

    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }


    for (int j = 0; j < n; j++) {
        while (!maxHeap.empty() && values[maxHeap.top()] >= values[j]) {
            maxHeap.pop();
        }
        if (maxHeap.empty()) {
            results[j] = 0; 
        } else {
            results[j] = maxHeap.top() + 1;
        }

        maxHeap.push(j);
    }

    for (const auto& index : results) {
        cout << index << " ";
    }
    cout << ln;

    return 0;
}
