#ifndef AVL_NODE_H
#define AVL_NODE_H

#include "BST_Node.h"

template <class T>
class AVL_Node : public BST_Node<T>
{
private:
	typedef AVL_Node<T> Node;

	int balanceFactor;
	
	Node* RotateLeft()
	{
		Node* parent = (Node*)this->getParent();
		Node* gparent = (Node*)parent->getParent();
		Node* anscestor = (Node*)gparent->getParent();

		gparent->setRight(NULL);

		if (parent->hasLeft())
			gparent->setRight(parent->getLeft());

		if (gparent->hasParent())
			parent->setParent(gparent->getParent());
		else
			parent->setParent(NULL);

		parent->setLeft(gparent);

		if (anscestor)
		{
			anscestor->replaceChild(gparent, parent);
		}

		return parent;
	}
	
	Node* RotateRight()
	{
		Node* parent = (Node*)this->getParent();
		Node* gparent = (Node*)parent->getParent();
		Node* anscestor = (Node*)gparent->getParent();

		gparent->setLeft(NULL);

		if (parent->hasRight())
			gparent->setLeft(parent->getRight());

		if (gparent->hasParent())
			parent->setParent(gparent->getParent());
		else
			parent->setParent(NULL);

		parent->setRight(gparent);

		if (anscestor)
			anscestor->replaceChild(gparent, parent);

		return parent;
	}

public:
	AVL_Node(T val,
		Node* p = NULL,
		Node* lt = NULL,
		Node* rt = NULL)
		: BST_Node(val, p, lt, rt), balanceFactor(0)
	{
		
	}

	void	setLeft(Node* lt)
	{
		if (this)
		{
			this->left = lt;
			if (lt) lt->setParent(this);
		}
	}
	
	void	setRight(Node* rt)
	{
		if (this)
		{
			this->right = rt;
			if (rt) rt->setParent(this);
		}
	}
	
	Node*	getLeft()
	{
		return (Node*)left;
	}

	Node*	getRight()
	{ 
		return (Node*)right;
	}

	int		GetBalanceFactor()
	{
		return balanceFactor;
	}

	void	SetBalanceFactor(int bF)
	{
		balanceFactor = bF;
	}

	Node* Balance()
	{
		Node* newRoot = NULL;

		if (this->hasParent() && this->getParent()->hasParent())
		{
			Node* grandparent = (Node*)this->getParent()->getParent();

			if (grandparent->GetBalanceFactor() < -1)
				newRoot = RotateRight();

			else if (grandparent->GetBalanceFactor() > 1)
				newRoot = RotateLeft();
		}

		return newRoot;
	}
};

#endif
