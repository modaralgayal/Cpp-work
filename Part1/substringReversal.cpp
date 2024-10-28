#include <iostream>
#include <cstdlib>

using namespace std;

struct node {
    node *left, *right;
    int weight, size;
    char value;   
    bool reverse;
    
    node(char v) {
        left = right = NULL;
        weight = rand();
        size = 1;
        value = v;
        reverse = false;
    }
};

int size(node *treap) {
    return treap ? treap->size : 0;
}

void updateSize(node *treap) {
    if (treap) {
        treap->size = size(treap->left) + size(treap->right) + 1;
    }
}

void push(node *treap) {
    if (treap && treap->reverse) {
        swap(treap->left, treap->right);
        if (treap->left) treap->left->reverse ^= true;
        if (treap->right) treap->right->reverse ^= true;
        treap->reverse = false;
    }
}

void split(node *treap, node *&left, node *&right, int k) {
    if (!treap) {
        left = right = NULL;
    } else {
        push(treap);  
        
        if (size(treap->left) < k) {
            split(treap->right, treap->right, right, k - size(treap->left) - 1);
            left = treap;
        } else {
            split(treap->left, left, treap->left, k);
            right = treap;
        }
        updateSize(treap);
    }
}

void merge(node *&treap, node *left, node *right) {
    push(left);
    push(right);
    if (!left) treap = right;
    else if (!right) treap = left;
    else {
        if (left->weight > right->weight) {
            merge(left->right, left->right, right);
            treap = left;
        } else {
            merge(right->left, left, right->left);
            treap = right;
        }
        updateSize(treap);
    }
}

void print(node *treap) {
    if (!treap) return;
    push(treap);
    print(treap->left);
    cout << treap->value;
    print(treap->right);
}

int main() {
    int n, q, a, b;
    string text;
    cin >> n >> q;
    cin >> text;
    node *treap = NULL;

    for (int i = 0; i < n; i++) {
        node *newNode = new node(text[i]);
        merge(treap, treap, newNode); 
    }

    while (q--) {
        cin >> a >> b;
        a--; 
        b--;
        node *left = NULL, *mid = NULL, *right = NULL;
        split(treap, left, right, b + 1);    
        split(left, left, mid, a);            
        if (mid) mid->reverse ^= true;
        merge(left, left, mid);
        merge(treap, left, right);
    }

    print(treap);
    cout << "\n";

    return 0;
}
