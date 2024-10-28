#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<pair<int, int> , int> > bookings(n);
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        bookings[i].first.first = a;
        bookings[i].first.second = b;
        bookings[i].second = i;
    }
    sort(bookings.begin(), bookings.end());
    multiset<pair<int, int>> rooms;

    int output[n];                    
    int nextRoomIndex = 1;
    for (const auto& booking : bookings) {
        int entry = booking.first.first;     
        int departure = booking.first.second; 
        int currentBookingIndex = booking.second;  
        auto it = rooms.lower_bound({entry, 0});
        if (it != rooms.begin()) {
            it = rooms.begin();
            if (it->first < entry) { 
                int roomIndex = it->second;
                rooms.erase(it);   
                rooms.insert({departure, roomIndex}); 
                output[currentBookingIndex] = roomIndex;
                continue;
            }
        }
        rooms.insert({departure, nextRoomIndex});
        output[currentBookingIndex] = nextRoomIndex;
        nextRoomIndex++; 
    }
    cout << rooms.size() << "\n";
    for (int i = 0; i < n; ++i) {
        cout << output[i] << " ";
    }
    cout << "\n";
    return 0;
}
