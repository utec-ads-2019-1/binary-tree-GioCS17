#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include<stack>

template <typename T> 
class Iterator {
    private:
        Node<T> *current;
	stack<Node<T>*> sfront;
	stack<Node<T>*> sback;
    public:
        Iterator() {
		this->current=nullptr;
        }

	void fillStackRecursive(Node<T>*node){
		if(node->left)
			fillStackRecursive(node->left);
		sfront.push(node);
		if(node->right)
			fillStackRecursive(node->right);
	}
        Iterator(Node<T> *node) {
		fillStackRecursive(node);
		while(!sfront.empty()){
			sback.push(sfront.top());
			sfront.pop();
		}
		sfront.push(sback.top());
		sback.pop();
		this->current=sfront.top();
        }

        Iterator<T> operator=(Iterator<T> other) {         
		this->current=other->current;
        }

        bool operator!=(Iterator<T> other) {
		return this->current!=other.current;
        }

        Iterator<T> operator++() {
		if(sback.empty()){
			this->current=nullptr;
			return (*this);
		}
		sfront.push(sback.top());
		sback.pop();
		this->current=sfront.top();
		return (*this);
        }

        Iterator<T> operator--() {
		if(sfront.empty()){
			this->current=nullptr;
			return (*this);
		}
		sback.push(sfront.top());
		sfront.pop();
		this->current=sback.top();
		return (*this);
        }

        T operator*() {
		if(!this->current)
			throw runtime_error("Valor de iterador es null\n");
		return this->current->data;
        }
};

#endif
