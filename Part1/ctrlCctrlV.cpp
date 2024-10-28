#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
 
using namespace std;
 
struct node {
    node *left, *right;
    int weight, size;
    char value;
    node(char v) {
        left = right = NULL;
        weight = rand();
        size = 1; 
        value = v;     
    }
};
 
int size(node *treap) {
    if (treap == NULL) return 0;
    return treap->size;
}
 
void updateSize(node *treap) {
    if (treap != NULL) {
        treap->size = size(treap->left) + size(treap->right) + 1;
    }
}
 
void split(node *treap, node *&left, node *&right, int k) {
    if (treap == NULL) {
        left = right = NULL;
    } else {
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
    if (left == NULL) treap = right;
    else if (right == NULL) treap = left;
    else {
        if (left->weight < right->weight) {
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
    if (treap == NULL) return;
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
        a--; b--;
 
        node *left = NULL, *mid = NULL, *right = NULL;
 
        split(treap, left, right, b + 1);
        split(left, left, mid, a);         
        merge(treap, left, right);
        merge(treap, treap, mid);
    }
    
    print(treap);
    cout << "\n";
 
    return 0;
}