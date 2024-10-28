#include <iostream>
#include <vector>
#include <set>

using namespace std;
typedef pair<int,bool> pint;
string const ln = "\n";

int main () {
    int n;
    cin >> n;
    vector<int> prufNodes(n - 2);
    vector<int> degrees(n + 1, 0);
    set<int> uncheckedNodes;

    for (int i = 1; i <= n; i++) {
        uncheckedNodes.insert(i);
    }

    for (int i = 0; i < n - 2; i++) {
        cin >> prufNodes[i];
        degrees[prufNodes[i]]++;
        if (uncheckedNodes.count(prufNodes[i])) {
            uncheckedNodes.erase(prufNodes[i]);
        }
    }

    for (int i = 0; i < n - 2; i++) {
        int leaf = *uncheckedNodes.begin();
        uncheckedNodes.erase(leaf);
        cout << leaf << " " << prufNodes[i] << ln;

        degrees[prufNodes[i]]--;
        if (degrees[prufNodes[i]] == 0) {
            uncheckedNodes.insert(prufNodes[i]);
        }
    }

    int node1 = *uncheckedNodes.begin();
    uncheckedNodes.erase(uncheckedNodes.begin());
    int node2 = *uncheckedNodes.begin();
    cout << node1 << " " << node2 << ln;

    return 0;
}
