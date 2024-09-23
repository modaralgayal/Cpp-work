#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
#define ln "\n";

ll n;
ll findSmallestEqual(vector<ll> &tree, ll room, ll a, ll b, ll node) {
    if (a == b) {
        tree[node] -= room;
        return a;
    } else {
        ll mid = (a + b) / 2;
        ll res; 
        if (tree[2*node] >= room) {
            res = findSmallestEqual(tree, room, a, mid, 2*node);
        } else {
            res = findSmallestEqual(tree, room,  mid + 1, b, 2*node + 1);
        }
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
        return res;
    }
}

void build(vector<ll> &tree, vector<ll> &rooms, ll a = 0, ll b = n-1, ll node = 1) {
    if (a == b) {
        tree[node] = rooms[a];
    } else {
        ll mid = (a+b) / 2;

        build(tree, rooms, a, mid, 2*node);
        build(tree, rooms, mid + 1, b, 2*node + 1);

        tree[node] = max(tree[2*node], tree[2*node + 1]);
    }
}


int main() {
    ll q;
    cin >> n >> q;
    vector<ll> rooms(n); 
    vector<ll> requiredRooms(q); 
    vector<ll> tree(4*n);  

    for (ll i = 0; i < n; i++) {
        cin >> rooms[i];
    }

    for (ll i = 0; i < q; i++) {
        cin >> requiredRooms[i];
    }

    build(tree, rooms);

    cout << ln;

    for (ll i = 0; i < q; i++) {
        ll roomSize = requiredRooms[i];

        if (tree[1] >= roomSize) { 
            ll index = findSmallestEqual(tree, roomSize, 0, n - 1, 1);  
            cout <<  index + 1 << " ";
        } else {
            cout << 0 << " "; 
        }
    }
    cout << endl;

    return 0;
}
