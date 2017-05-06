#ifndef AVL_H
#define AVL_H

#include "BST.h"
#include "AVL_Node.h"

template <class T>
class AVL : public BST<T>
{
	typedef AVL_Node < T > Node;

public:
	Node* Insert(Node* node, const T value)
	{
		if (!node)
		{
			node = new Node(value);
			return node;
		}

		else if (value < node->getData())
			if (node->hasLeft())
			{
				return Insert(node->getLeft(), value);
			}
			else
			{
				node->setLeft(new Node(value));
				return node->getLeft();
			}

		else if (value > node->getData())
			if (node->hasRight())
			{
				return Insert(node->getRight(), value);
			}
			else
			{
				node->setRight(new Node(value));
				return node->getRight();
			}

		return NULL;
	}

	void Insert(T value)
	{
		Node* node = Insert((Node*)root, value);
		if (root == NULL) root = node;
		if (node)
		{
			nodeCount++;
			RestoreBalance(value);

			while (root->hasParent())
				root = root->getParent();

			RestoreBalance(value);
		}
		cout << "Nodes: " << nodeCount << endl;
	}
	
	void RestoreBalance(const T& value)
	{
		Node* iterator = (Node*)root;		// Starting from the root, visit each
		while (iterator->getData() != value)// node that in path from root to the
		{
			ComputeBF(iterator);			// newly inserted node and recompute
			if (iterator->GetBalanceFactor() < -1)
			{
				iterator->getLeft()->getLeft()->Balance();
				break;
			}
			else if (iterator->GetBalanceFactor() > 1)
			{
				iterator->getRight()->getRight()->Balance();
				break;
			}

			if (value < iterator->getData())// balance factors of each
				iterator = iterator->getLeft();
			else
				iterator = iterator->getRight();
		}
	}

	void ComputeBF(Node* node)
	{
		node->SetBalanceFactor(Height(node->getRight()) - Height(node->getLeft()));
	}

	int	Height(Node* node)
	{
		if (!node)
			return -1;

		if (!node->hasLeft() && !node->hasRight())
			return 0;

		int leftDepth = Height(node->getLeft());
		int rightDepth = Height(node->getRight());

		return leftDepth > rightDepth ? 
			leftDepth + 1 :
			rightDepth + 1;
	}

	Node* GetRoot()
	{
		return static_cast< Node* > (root);
	}
};

#endif