#include <LRUCache.h>
#include <iostream>
#include <unordered_map>
#include "Node.H"


LRUCache::LRUCache(int size) {
    if (size <= 0) {
        std::cout << "please give positive size" << std::endl;
        return;
    }
    LRUCache::SIZE = size;
    Head = nullptr;
    Tail = nullptr;
}


void detach (Node*& node) {
    if (node->next == nullptr && node->prev == nullptr) {return;}// single node case)
    if (node->prev == nullptr) { // Head Case
        node->next->prev = nullptr;
        node->next = nullptr;
        return;
    } else if (node->next == nullptr) { // Tail Case
        node->prev->next = nullptr;
        node->prev = nullptr;
        return;
    }

    node->next->prev = node->prev;
    node->prev->next = node->next;
}

void detachTail(Node*& tail, bool toDelete) {
    if (tail->next == nullptr && tail->prev == nullptr) { // tail is only node case
        if (toDelete == true) {
            delete tail;
            tail = nullptr;
            return;
        } else {
            return;
        }
   } 

    tail->prev = nullptr;
    tail->prev->next = nullptr;
    if (toDelete == true) {
        Node* newTail = tail->prev;
        delete tail;
        tail = nullptr;
        tail = newTail;
    }
}

void insertAtHead(Node*& node, Node*& head) {
    node->next = head;
    node->prev = nullptr;
    head->prev = node;
    head = node;
}

int LRUCache::get(int key) {
    if (MapCache.count(key) == 0) {return -1;}
    Node* gotNode = MapCache.at(key);
    
    if (gotNode == Head) {
        return gotNode->value;
    } else if (gotNode == Tail) {
        if (MapCache.size() == 1) {
            return gotNode->value;
        } else {
            detachTail(Tail, false);
            insertAtHead(gotNode, Head);
            return gotNode->value;
        }      
    } else {
        detach(gotNode);
        insertAtHead(gotNode, Head);
        return gotNode->value;
    }
}


void LRUCache::put(int key, int value) {
    Node* LRUNode;
    if (MapCache.count(key) == 0) {
        LRUNode = new Node(key, value, nullptr, nullptr);
    } else {
        LRUNode = MapCache.at(key);
        LRUNode->value = value;
        if (LRUNode == Head) {return;} // covers head and size 1 cache
        else if (LRUNode == Tail) { // covers tail and size 2 cache
            detachTail(Tail, false);
            insertAtHead(LRUNode, Head);
            return;
        }

        detach(LRUNode); 
        insertAtHead(LRUNode, Head);
        return;
    }
  
    if (MapCache.size() == 0) {
        Head = LRUNode;
        Tail = Head;
        MapCache[key] = LRUNode;
    } else {
        LRUNode->next = Head;
        LRUNode->prev = nullptr;
        Head->prev = LRUNode;
        Head = LRUNode;
        MapCache[key] = LRUNode;

        if (MapCache.size() > SIZE) {
            Node* oldTail = Tail;
            MapCache.erase(Tail->key);
            detachTail(Tail, true); 
            Tail = oldTail;
            
        }
    }
}