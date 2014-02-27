#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
template<typename T> 
class LinkedList {
private:
	class Node { 
	 public:
		T data; 
		Node *next;
		Node(const T &data) {
			this->data = data;
			this->next = nullptr;
		}
		friend class iterator;
		friend class LinkedList;
	};
	Node *start; 
	Node *end_node;
	int length; 
public: 
	class iterator { 
	 private:
		Node *ptr; 
	 public:
	 	using value_type = T; 
	 	using iterator_category = std::forward_iterator_tag;
		iterator(Node *data) { 
			ptr = data;
		}
		bool operator==(iterator &that) { 
			return this->ptr == that.ptr;
		}
		bool operator!=(iterator &that) { 
			return this->ptr != that.ptr;
		}
		iterator& operator++() { 
			ptr = ptr->next;
			return *this;
		}
		iterator operator++(int k) { 
			ptr = ptr->next;
			return iterator(ptr);
		}
		T& operator*() { 
			return ptr->data;
		}
		T* operator->() { 
			return &(ptr->data);
		}
	};
	LinkedList() { 
		start = end_node = nullptr;
		length = 0;
	} 
	void push_back(const Node &obj) { 
		if ( length == 0) { 
			start = new Node(obj); 
			end_node = start; 
			end_node->next = nullptr; 
			length++;
			return;
		}
		Node *x = new Node(obj);
		end_node->next = x;
		end_node = x;
		length++;
	}
	void push_front(const Node &obj) { 
		if ( length == 0) { 
			start = new Node(obj); 
			end_node = start; 
			end_node->next = nullptr; 
			length++;
			return;
		}
		Node *x = new Node(obj);
		x->next = start; 
		start = x;
		length++;
	}
	iterator begin() { 
		return iterator(start);
	}
	iterator end() { 
		return iterator(nullptr);
	}
	~LinkedList() { 
		Node *x = start; 
		while (x != nullptr) { 
			Node *y = x->next; 
			delete x;
			x = y;
		}
	}
};
#endif