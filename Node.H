
#ifndef DOUBLE_LINKED_LIST
#define DOUBLE_LINKED_LIST

class Node {
    public :
    int key;
    int value;
    Node* next;
    Node* prev;
    Node() = delete;
    Node(int k, int v, Node* n, Node* p) {
        key = k;
        next = n;
        prev = p;
    }
};


#endif