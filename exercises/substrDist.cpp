#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
typedef long long ll;

const ll MAX = 1e5 + 5;
ll gap, stringLength;
string str;
vector<ll> suffixArray(MAX), temp(MAX), position(MAX), longestCommonPrefix(MAX);
// artikkeli täst ratkaisusta https://www.geeksforgeeks.org/cses-solutions-substring-distribution/ 
void buildSuffixArray() {
    for (int i = 0; i < stringLength; i++)
        suffixArray[i] = i, position[i] = str[i];

    for (gap = 1;; gap *= 2) {
        auto compare = [&](int x, int y) {
            if (position[x] != position[y])
                return position[x] < position[y];
            x += gap;
            y += gap;
            return (x < stringLength && y < stringLength) ? position[x] < position[y] : x > y;
        };

        sort(suffixArray.begin(), suffixArray.begin() + stringLength, compare);

        for (int i = 0; i < stringLength - 1; i++)
            temp[i + 1] = temp[i] + compare(suffixArray[i], suffixArray[i + 1]);
        for (int i = 0; i < stringLength; i++)
            position[suffixArray[i]] = temp[i];

        if (temp[stringLength - 1] == stringLength - 1)
            break;
    }
}

void buildLCPArray() {
    for (int i = 0, k = 0; i < stringLength; i++) {
        if (position[i] != stringLength - 1) {
            int j = suffixArray[position[i] + 1];
            while (str[i + k] == str[j + k])
                k++;
            longestCommonPrefix[position[i]] = k;
            if (k) k--; 
        }
    }
}

int main() {
    cin >> str;
    stringLength = str.size();
    
    vector<ll> prefixes(stringLength + 2);  
    buildSuffixArray(); 
    buildLCPArray();     

    ll previous = 0;
    for (ll i = 0; i < stringLength; i++) {
        prefixes[previous + 1]++;
        prefixes[stringLength - suffixArray[i] + 1]--;
        previous = longestCommonPrefix[i];
    }

    vector<ll> results(stringLength + 1);
    for (ll i = 1; i <= stringLength; i++) {
        results[i] = prefixes[i];
        prefixes[i + 1] += prefixes[i];
    }

    for (ll i = 1; i <= stringLength; i++) {
        cout << results[i] << " ";
    }
    cout << endl;

    return 0;
}
