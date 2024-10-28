#include <iostream>
#include <map>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>


using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;

int main() {
    long n, k;
    cin >> n >> k;

    indexed_set values;
    for (long i = 1; i <= n; ++i) {
        values.insert(i);
    }

    long index = 0;
    while (!values.empty()) {
        index %= values.size();
        int removeThis = (index + k)% values.size();
        index = removeThis;
        auto nextOne = values.find_by_order(removeThis);
        cout << *nextOne << " ";
        values.erase(nextOne);
    }
    
    cout << endl;
    return 0;
}
