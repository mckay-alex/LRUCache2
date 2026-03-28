LRUCache implementation in C++

The LRU Cache is a data structure that:

Stores fixed number of key-value pairs
Removes least recently used item when capacity exceeded
Allows quick access and updates
This implementation combines:

Hash Map (unordered_map) O(1) lookup
Doubly Linked List O(1) insertion/removal
How it functions:

The hash map stores key for fast access
The doubly linked list maintains usage order:
Most recently used at the front/head
Least recently used at the back/tail
On every get or put:
The accessed node is moved to the front
When capacity is exceeded:
The node at the back is removed (least recently used node)
Example Usage (in cpp file) :

LRUCache cache(2);

cache.put(1, 1); cache.put(2, 2);

cache.get(1); // returns 1

cache.put(3, 3); // evicts key 2

cache.get(2); // returns -1 (not found)
