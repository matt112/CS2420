/* TEsting!!!
 * AVL.cpp
 * another etest!!!!!
 *  Created on: Nov 7, 2015
 *      Author: matt
 */

#include "AVL.h"
#include <iostream>
#include <iomanip>

using namespace std;

AVL::AVL() {
	root = nullptr;
	size = 0;
}

AVL::~AVL() {
	destroy(root);
}

void AVL::destroy(Node* root) {
	if (root) {
		destroy(root->left);
		destroy(root->right);
		delete root;
		root = nullptr;
	}
}

void AVL::insert(int data) {
	cout << "Inserting " << data << endl;
	insert(root, data);
}

AVL::Node* AVL::insert(Node* &root, int data) {
	if (root == nullptr) {
		size++;
		return root = new Node(data);
	}
	if (data < root->data)
		root->left = insert(root->left, data);
	else if (data > root->data)
		root->right = insert(root->right, data);
	else
		cout << "Duplicate data is not allowed" << endl;

	rebalance(root);

	root->height = max(root->left, root->right) + 1;   // update height
	return root;
}

void AVL::remove(int data) {
	cout << "Removing " << data << " from the tree" << endl;
	remove(root, data);
}

AVL::Node* AVL::remove(Node* &root, int data) {
	if (root == nullptr) {
		cout << data << " is not in the tree. Nothing to remove" << endl;
	} else if (data < root->data) {
		root->left = remove(root->left, data);

		// Make sure the tree still maintains AVL property after removing an element
		rebalance(root);
		root->height = max(root->left, root->right) + 1;   // update height
	} else if (data > root->data) {
		root->right = remove(root->right, data);
		// Make sure the tree still maintains AVL property after removing an element
		rebalance(root);
		root->height = max(root->left, root->right) + 1;   // update height
	} else { //found data to remove
			 //case 1: data to be deleted is a leaf node
		if (root->left == nullptr && root->right == nullptr) {
			delete root;
			root = nullptr;
			size--;
		}

		//case 2: data to be delete has only one child
		else if (root->left == nullptr)   // Node has a right child
				{
			Node* temp = root;
			root = root->right;
			delete temp;
			size--;
		} else if (root->right == nullptr)   // Node has a left child
				{
			Node* temp = root;
			root = root->left;
			delete temp;
			size--;
		}

		//case 3: data to be delete has two children
		else {
			Node* temp = findMin(root->right);
			root->data = temp->data;
			remove(root->right, temp->data);
		}
	}

	return root;
}

AVL::Node* AVL::leftrotate(Node* root) {
	Node* newroot = root->right;
	root->right = newroot->left;
	newroot->left = root;

	root->height = max(root->left, root->right) + 1;
	newroot->height = max(newroot->left, newroot->right) + 1;

	return newroot;
}

AVL::Node* AVL::rightrotate(Node* root) {
	Node* newroot = root->left;
	root->left = newroot->right;
	newroot->right = root;

	root->height = max(root->left, root->right) + 1;
	newroot->height = max(newroot->left, newroot->right) + 1;

	return newroot;
}

bool AVL::search(int data) {
	return search(root, data);
}

bool AVL::search(Node* root, int data) {
	if (root == nullptr)
		return false;
	else if (root->data == data)
		return true;
	else if (data < root->data)
		return search(root->left, data);
	else
		return search(root->right, data);
}

void AVL::preorder() {
	cout << "Preorder Print: ";
	preorder(root);
	cout << endl;
}

void AVL::preorder(Node* root) {
	if (root) {
		cout << root->data << " ";
		preorder(root->left);
		preorder(root->right);
	}
}

void AVL::inorder() {
	cout << "Inorder Print: ";
	inorder(root);
	cout << endl;
}

void AVL::inorder(Node* root) {
	if (root) {
		inorder(root->left);
		cout << root->data << " ";
		inorder(root->right);
	}
}

void AVL::postorder() {
	cout << "Postorder print: ";
	postorder(root);
	cout << endl;
}

void AVL::postorder(Node* root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		cout << root->data << " ";
	}
}

int AVL::balance(Node* root) {
	return height(root->left) - height(root->right);
}

int AVL::getsize() {
	return size;
}

int AVL::height(Node* root) {
	if (root == nullptr)
		return 0;
	else
		return root->height;
}

int AVL::max(Node* left, Node* right) {
	return (height(left) > height(right)) ? height(left) : height(right);
}

void AVL::print() {
	if (root) {
		print(root, 0);
	} else
		cout << "Tree is empty. Nothing to print." << endl;
}

void AVL::print(Node* root, int depth) {
	cout << setw(4 * depth) << "";

	if (root) {
		if (root->left == nullptr && root->right == nullptr) {
			cout << root->data << " [leaf]" << endl;
		} else {
			cout << root->data << endl;
			print(root->left, depth + 1);
			print(root->right, depth + 1);
		}
	} else {
		cout << "[Empty]" << endl;
	}
}

AVL::Node* AVL::findMin(Node* root) {
	if (root->left != nullptr) {
		findMin(root->left);
	}
	return root;
}

void AVL::rebalance(Node* &root) {
	int bal = balance(root); // if negative balance, right subtree is heavy. if positive balance, left subtree is heavy
	cout << "Balance of Node " << root->data << " is " << bal << endl;
	if (bal > 1) {  // left heavy
		if (balance(root->left) > 0) { // double left heavy -> single right rotation
			cout << "Single right rotation" << endl;
			root = rightrotate(root);
		} else { // double rotation
			cout << "Double Left Right Rotation" << endl;
			root->left = leftrotate(root->left);
			root = rightrotate(root);
		}
	} else if (bal < -1) { // right heavy
		if (balance(root->right) < 0) { // double right heavy -> single left rotation
			cout << "Single left rotation" << endl;
			root = leftrotate(root);
		} else { // double rotation
			cout << "Double Right Left Rotation" << endl;
			root->right = rightrotate(root->right);
			root = leftrotate(root);
		}
	} else
		cout << root->data << " is balanced" << endl;
}
