#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

void add(string s,string remaining,set<string>& result) {
    if (remaining.empty()) {
        result.insert(s);
        return;
    }

    for (int c = 0; c < remaining.length(); c++) {
        string new_s = s + remaining[c];
        string new_remaining = remaining.substr(0, c) + remaining.substr(c + 1);
        add(new_s, new_remaining, result);
    }
}

int main() {
    string s = "";
    string remaining;
    cin >> remaining;
    set<string> result;

    add(s, remaining, result);

    cout << result.size() << "\n";

    for (const string& permutation : result) {
        cout << permutation << "\n";
    }

}