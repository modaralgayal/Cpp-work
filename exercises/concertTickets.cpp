#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    int n,m;
    cin >> n >> m;

    vector<int> tickets(n);
    vector<int> customers(m);
    set<pair<long, long>> ticketsPos;

    for (int i = 0; i < n; i++)
    {
        cin >> tickets[i];
        ticketsPos.insert({tickets[i],i});
    }
    for (int i = 0; i < m; i++) {
        cin >> customers[i];
    }
    for (int i = 0; i < m; i++) {
        auto possibleTicket = ticketsPos.lower_bound({customers[i]+1,0});
        if (possibleTicket == ticketsPos.begin()) {
            cout << -1 << "\n";
        }
        else {
            possibleTicket--;
            cout << (*possibleTicket).first << "\n";
            ticketsPos.erase(possibleTicket);
        }
    }

}
