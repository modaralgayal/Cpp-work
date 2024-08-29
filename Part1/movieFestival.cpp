#include <iostream>
#include <vector>
#include <utility> 
#include <algorithm>
 
using namespace std;
 
/*Find the earliest finishing,
then the send second earliest finishing in 
which the beginning doesnt overlap, that way we find the most
amount of intervals.*/ 
 
int main () {
    long long n;
    cin >> n;
    vector<pair<long long, long long>> vektori;
    
 
    for (int i = 0; i < n; i++) {
        long long a, b;
        cin >> a >> b;
        vektori.push_back(make_pair(a, b));
    }
 
        sort(vektori.begin(), vektori.end(), [](const pair<long long, long long>& a, const pair<long long, long long>& b) {
        return a.second < b.second;
    });
 
    long long earliestFinishing = -1, watchableMovies = 0;
    for (const auto& p : vektori) {
        if (earliestFinishing <= p.first) {
            earliestFinishing = p.second;
            watchableMovies += 1;
        }
    }
 
    cout << watchableMovies << " ";
}