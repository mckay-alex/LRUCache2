#include <LRUCache.h>
#include <iostream>
#include <unordered_map>
#include "Node.H"


LRUCache::LRUCache(int size) {
    if (size <= 0) {
        throw std::invalid_argument("capacity must be positive");
        return;
    }
    LRUCache::SIZE = size;
    Head = new Node(-1, -1, nullptr, nullptr);
    Tail = new Node(-1, -1, nullptr, nullptr);
    Head->next = Tail;
    Tail->prev = Head;
}

LRUCache::~LRUCache() {
    Node* curr = Head;
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }  
}


void LRUCache::detach(Node* node) {
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = nullptr;
    node->prev = nullptr;
}

void LRUCache::insertAtHead(Node* node, Node* head) {
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
}

void LRUCache:: deleteLastNode(Node*& lastNode) {
    detach(lastNode);
    delete lastNode;
    lastNode = nullptr;
}


int LRUCache::get(int key) {
    if (MapCache.count(key) == 0) {return -1;}
    Node* LRUNode = MapCache.at(key);

    detach(LRUNode);
    insertAtHead(LRUNode, Head);
    return LRUNode->value;
}


void LRUCache::put(int key, int value) {
    if (MapCache.count(key) == 0) {
        Node* newNode = new Node(key, value, nullptr, nullptr);
        insertAtHead(newNode, Head);
        MapCache[key] = newNode;
    } else { // node already exists
        Node* node = MapCache.at(key);
        node->value = value;
        detach(node);
        insertAtHead(node, Head);
        return;
    }

     if (MapCache.size() > SIZE) {
        Node* lastNode = Tail->prev;
        if (lastNode == Head) {return;}
        MapCache.erase(lastNode->key);
        deleteLastNode(lastNode);
     }
}