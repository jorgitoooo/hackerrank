#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : protected Cache {
    void add_node_to_front(Node *n_node)
		{
        if(n_node)
				{
            if(head)
						{
                head->prev = n_node;
                head = n_node;
            }
						else
						{
                head = tail = n_node;
            }
            mp.insert(make_pair(n_node->key, n_node));
        }
    }
    void remove_tail()
		{
        if(tail)
				{
            mp.erase(tail->key);
            Node *tmp = tail;
            
            if(tail == head) tail = head = nullptr;
            else tail = tail->prev;

            delete tmp;
        }
    }

public:
    LRUCache(int capacity)
		{
        cp = capacity;
    }

    void set(int key, int value)
		{
        if(cp <= 0) return;
        if(!head && !tail && mp.size() == 0)
				{
            Node *n_node = new Node(key, value);
            add_node_to_front(n_node);
        }
				else
				{
            // Node is not mapped
            if(mp.find(key) == mp.end())
						{
                Node *n_node = new Node(nullptr, head, key, value);
                if(mp.size() < cp)
								{
                    add_node_to_front(n_node);
                }
								else
								{
                    remove_tail();
                    add_node_to_front(n_node);
                }
            }
						else
						{
                Node *n_node = mp[key];
                n_node->value = value;
                // Remove node from it's current position
                if(n_node->prev) n_node->prev->next = n_node->next;
                if(n_node->next) n_node->next->prev = n_node->prev;
                // Place node at front
                n_node->next = head;
                n_node->prev = nullptr;
                head->prev = n_node;
                head = n_node;
            }
        }
    }

    int get(int key)
		{
        return mp.find(key) != mp.end() ? mp[key]->value : -1;
    }
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}

