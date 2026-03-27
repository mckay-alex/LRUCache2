#include <unordered_map>
#include "Node.H"

#ifndef LRU_CACHE
#define LRU_CACHE



class LRUCache {
    public :
        std::unordered_map<int, Node*> MapCache;
        Node* Head; // this is start of doubly linked list
        Node* Tail;
        int SIZE;
        
        LRUCache() = delete;
        LRUCache(int size) {};
        


        int get(int key) {};
        void put (int key, int value) {};
    
    private:
        // Helpers
        void detach(Node* node) {};
        void insertAtHead(Node* node, Node* head) {};
        void deleteLastNode(Node*& lastNode) {}
};


#endif