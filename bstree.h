#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h"

template<typename T>
class Iterator;

template <typename T> 
class BSTree {
    private:
        Node<T> *root;
	unsigned int sizet;
	Iterator<T> itr;

    public:
	template<class>
	friend class Iterator;
        BSTree() : root(nullptr),sizet(0){}

        bool find(T data){ 
		Node<T> *tmp=this->root;
		if(!root)
			return false;
		
		while(tmp){
			if(tmp->data==data)
				return true;
			else if(tmp->data>data)
				tmp=tmp->left;
			else
				tmp=tmp->right;

		}
		return false;
		
        } 

        bool insert(T data) {
		if(find(data))
			return false;
		if(root){
			Node<T>* tmp=this->root;
			while(tmp){
				if(tmp->data>data){
					if(tmp->left==nullptr)
						break;
					tmp=tmp->left;
				}
				else{
					if(tmp->right==nullptr)
						break;
					tmp=tmp->right;
				}
			}
			Node<T>*nuevo=new Node<T>;
			nuevo->data=data;
			nuevo->left=nuevo->right=nullptr;
			nuevo->parent=tmp;
			if(tmp->data>data)
				tmp->left=nuevo;
			else
				tmp->right=nuevo;
		}
		else{
			this->root=new Node<T>;
			this->root->data=data;
			this->root->left=this->root->right=this->root->parent=nullptr;
		}

		sizet++;
		return true;
        }

	void deleteNodeZeroChild(Node<T>*&tmp,Node<T>*&dad){
		if(dad){
			if(dad->left==tmp)
				dad->left=nullptr;
			else
				dad->right=nullptr;
		}
		else
			this->root=nullptr;
		delete tmp;
	}
	void deleteNodeOneChild(Node<T>* &tmp,Node<T>*&dad){
		if(dad){
			if(tmp->left && dad->left==tmp){
				dad->left=tmp->left;
				tmp->left->parent=dad;
			}
			else if(tmp->left && dad->right==tmp){
				dad->right=tmp->left;
				tmp->left->parent=dad;
			}
			else if(tmp->right && dad->left==tmp){
				dad->left=tmp->right;
				tmp->right->parent=dad;
			}
			else{
				dad->right=tmp->right;
				tmp->right->parent=dad;
			}
		}
		else{
			if(root->left)
				root=root->left;
			else
				root=root->right;
			root->parent=nullptr;
		}
		delete tmp;
	}
        bool remove(T data){
		if(!find(data))
			return false;
		Node<T>* tmp=this->root;
		Node<T>* dad=nullptr;
		while(tmp){
			if(tmp->data==data){
				int cont=0;
				if(tmp->left)
					cont++;
				if(tmp->right)
					cont++;
				if(cont==0)
					deleteNodeZeroChild(tmp,dad);
				
				else if(cont==1)
					deleteNodeOneChild(tmp,dad);
				
				else{
					Node<T>* tmp2=dad=tmp;
					tmp2=tmp2->left;
					while(tmp2->right){
						dad=tmp2;
						tmp2=tmp2->right;
					}
					tmp->data=tmp2->data;
					cont=0;
					if(tmp2->right)
						cont++;
					if(tmp2->left)
						cont++;
					if(cont==0)
						deleteNodeZeroChild(tmp2,dad);
				
					else if(cont==1)
						deleteNodeOneChild(tmp2,dad);
				}
				sizet--;
				return true;
			}
			else{
				dad=tmp;
			       	if(tmp->data>data)
					tmp=tmp->left;
				else
					tmp=tmp->right;
			}
		}
		// Falta un return
        }

        unsigned int size() {
		return sizet;
        }

	void recursivePre(Node<T>* node,int caso){
		switch(caso){
			case 1:
				cout<<node->data<<endl;
				if(node->left)
					recursivePre(node->left,1);
				if(node->right)
					recursivePre(node->right,1);
				break;
			case 2:
				if(node->left)
					recursivePre(node->left,2);
				cout<<node->data<<endl;
				if(node->right)
					recursivePre(node->right,2);
				break;
			case 3:
				if(node->left)
					recursivePre(node->left,3);
				if(node->right)
					recursivePre(node->right,3);
				cout<<node->data<<endl;
				break;
			default:
				throw runtime_error("Ingreso a opcion invalidad\n");
		}
	}
        void traversePreOrder() {
		if(root){
			recursivePre(root,1);
			return;
		}
		cout<<"No hay elementos en el arbol"<<endl;
        }

        void traverseInOrder() {
		if(root){
			recursivePre(root,2);
			return;
		}
		cout<<"No hay elementos en el arbol"<<endl;
        }

        void traversePostOrder() {
		if(root){
			recursivePre(root,3);
			return;
		}
		cout<<"No hay elementos en el arbol"<<endl;
        }

        Iterator<T> begin() {
		if(!this->root)
			return Iterator<T>();

		return Iterator<T>(this->root);
        }

        Iterator<T> end() { 
		return Iterator<T>();
        }

	void deleteall(Node<T>* node){
		// Si node es null? 
		if(node->left)
			deleteall(node->left);
		if(node->right)
			deleteall(node->right);
		delete node;
	}
        ~BSTree() {
		deleteall(this->root);
		this->root=nullptr;
        }
};

#endif
