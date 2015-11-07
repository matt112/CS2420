/*
 * AVL.h
 *
 *  Created on: Nov 7, 2015
 *      Author: matt
 */

#ifndef AVL_H_
#define AVL_H_

class AVL {
private:
	struct Node{
		int data;
		Node* left;
		Node* right;
		int height;

		Node(int d): data(d), left(nullptr), right(nullptr), height(1){};
	};

	int size;
	Node* root;

public:
	AVL();
	virtual ~AVL();
	void destroy(Node* root);
	void insert(int data);
	Node* insert(Node* &root, int data);
	/*void remove();
	Node* leftRotate();
	Node* rightRotate();
	bool search();
	void display();*/
	void preorder();
	void preorder(Node* &root);
	int balance(Node* root);

};

#endif /* AVL_H_ */