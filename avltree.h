
#include <list>
#include <set>
#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include <limits>

using namespace std;

template <typename T> class avl_node;
template <typename T> class avl_tree;

template <typename T>
class avl_tree{
public:

	//CONSTRUCTOR
	avl_tree(){
		root = nullptr;
	}

	//DESTRUCTOR
	~avl_tree(){
		if (root){
			del(root);
		}
	}

	avl_tree(const avl_tree& tree){

		if (tree->root == nullptr){
			root = nullptr;
			return;
		}

		else{
			root = new avl_node(tree->root->data);
			if (tree->root->left){
				root->left = copyN(tree->root->left)
			}
			if (tree->root->right){
				root->right = copyN(tree->root->right)
			}
		}
	}

	//copy helper function
	avl_node<T>* copyN(const avl_node<T> *parent){
		avl_node<T>* node = new avl_node();

		if (parent){
			node->data = parent->data;
			node->height = parent->height;
			if (parent->left){
				node->left = copyN(parent->left);
			}
			if (parent->right){
				node->left = copyN(parent->left);
			}

		}
		else{
			node = nullptr;
		}
		return node;
	}


	//Delete helper function
	void del(const avl_node<T> *parent) {
		if (parent->left){
			del(parent->left);
		}
		if (parent->right){
			del(parent->right);
		}
		delete parent;
	}



	int getHeight(avl_node<T>* treeNode){
		if (treeNode){
			return treeNode->height;
		}
		else{
			return 0;
		}
	}

	void setHeight(avl_node<T>* treeNode){
		int heightL = getHeight(treeNode->left);
		int heightR = getHeight(treeNode->right);
		if (heightL > heightR){
			treeNode->height = heightL + 1;
		}
		else{
			treeNode->height = heightR + 1;
		}
	}

	int balanceFactor(avl_node<T>* treeNode){
		return getHeight(treeNode->right) - getHeight(treeNode->left);
	}



	//rotateRight 
	avl_node<T>* rotateRight(avl_node<T>* &root){

		avl_node<T> * node;

		if (root == nullptr){
			return nullptr;
		}
		else if (root->left == nullptr){
			return nullptr;
		}
		else{
			node = root->left;
			root->left = node->right;
			node->right = root;
			root = node;
			setHeight(root);
			setHeight(node);
			return node;
		}
	}


	//rotateLeft
	avl_node<T>* rotateLeft(avl_node<T>* &root){

		avl_node<T> * node;

		if (root == nullptr){
			return nullptr;
		}
		else if (root->right == nullptr){
			return nullptr;
		}
		else{
			node = root->right;
			root->right = node->left;
			node->left = root;
			root = node;
			setHeight(root);
			setHeight(node);
			return node;
		}
	}



	//doubleLeft 
	avl_node<T>* doubleLeft(avl_node<T>* &root){
		avl_node<T> * node;
		if (root == nullptr){
			return nullptr;
		}
		else if (root->right == nullptr){
			return nullptr;
		}
		else{

			node = root;
			node->right = rotateRight(node->right);
			node = rotateLeft(node);
			return node;
		}
	}


	//double right
	avl_node<T>* doubleRight(avl_node<T>* &root){
		avl_node<T> * node;
		if (root == nullptr){
			return nullptr;
		}
		else if (root->left == nullptr){
			return nullptr;
		}
		else{

			node = root;
			node->left = rotateLeft(node->left);
			node = rotateRight(node);
			return node;
		}
	}

	avl_node<T>* balance(avl_node<T>* treeNode){
		int balanceF = balanceFactor(treeNode);


		if (balanceF < -1){
			if (balanceFactor(treeNode->right) > 0){
				treeNode = rotateLeft(treeNode);
			}
			else{
				treeNode = doubleRight(treeNode);
			}
		}
		else if (balanceF == 0){
			return treeNode;
		}
		else if (balanceF > 1){
			if (balanceFactor(treeNode->left) > 0){
				treeNode = rotateRight(treeNode);
			}
			else{
				treeNode = doubleLeft(treeNode);
			}
		}

		return treeNode;
	}
	bool insert(int value) {
		if (insertNode(this->root, value)) {
			return true;
		}
		else {
			return false;
		}
	}

	avl_node<T>* insertNode(avl_node<T> *root, T value)

	{
		if (root == nullptr){
			root = new avl_node<T>();
			root->data = value;
			root->right = root->left = nullptr;
			return root;
		}

		else if (value < root->data){
			root->left = insertNode(root->left, value);
			root = balance(root);
		}
		else if (value > root->data){
			root->right = insertNode(root->right, value);
			root = balance(root);
		}
		else {
			return nullptr;
		}
		return root;
	}

	avl_node<T>* root;				//there is only one root, declare outside of class?
	bool find(const T& value)const {
		avl_node<T>* node = root;
		while (node){
			if (node->data == value){
				return true;
			}
			else if (value > node->data){
				node = node->right;
			}
			else{
				node = node->left;
			}
			return false;
		}
	}

};


//NODE CLASS
template<typename T>
class avl_node{

public:
	T data;
	int height;
	avl_node* left;
	avl_node* right;
	//Default Constructor
	avl_node(){
		data = NULL;
		height = 0;
		left = nullptr;
		right = nullptr;
	}

	//constructor with given value
	avl_node(T number){
		data = number;
		height = 0;
		left = nullptr;
		right = nullptr;
	}

	//Copy Constructor				???????
	avl_node(const avl_node<T>& node){
		if (node->data){
			data = this->data;
			height = this->height;
			left = this->left;
			right = this->right;
		}
	}
};