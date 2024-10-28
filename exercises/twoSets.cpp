#include <iostream>
#include <vector>

using namespace std;

int main () {
    long long val;
    cin >> val;
    long long total = (val * (val + 1)) / 2;

    vector<long long> values;

    if ( total % 2 == 1 ) {
        cout << "NO" << "\n";
        return 0;
    } else {
        cout << "YES" << "\n";
    }

    for (int i = 1; i <= val; i++) {
        values.push_back(i);
    }

    long long halfAmount = total / 2;

    vector<long long> firstList;
    vector<long long> secondList;

    
     while (halfAmount >= 0 && !values.empty()) {
        long long num = values.back(); 
        values.pop_back(); 

        if (num <= halfAmount) {
            firstList.push_back(num);
            halfAmount -= num; 
        } else {
            secondList.push_back(num); 
        }
    }

    cout << firstList.size() << "\n";
    for (const auto& num : firstList) {
        cout << num << " ";
    }
    cout << "\n";
    
    cout << secondList.size() << "\n";
    for (const auto& num : secondList) {
        cout << num << " ";
    }
    cout << "\n";


}