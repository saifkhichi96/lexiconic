#ifndef BST_H
#define BST_H

#include "BST_Node.h"

template <class T>
class InOrderPtr;

template <class T>
class PreOrderPtr;

template <class T>
class PostOrderPtr;

template <class T>
class BST
{
private:
	typedef BST_Node<T> Node;
protected:
	Node*	root;
	int		nodeCount;

	void	DeleteTree(Node* tree)
	{
		if (tree)
		{
			if (tree->hasLeft())	DeleteTree(tree->getLeft());
			if (tree->hasRight())	DeleteTree(tree->getRight());
			delete tree;
			nodeCount--;
			cout << nodeCount << " nodes remaining\n";
		}
	}

	Node*	Find(Node* node, const T& val)
	{
		if (node)
		{
			if (val == node->getData()) return node;

			else if (val < node->getData())
				return Find(node->getLeft(), val);
			else
				return Find(node->getRight(), val);
		}

		else return NULL;
	}

	Node*	GetMin(Node* node)
	{
		if (node)
		{
			auto temp = node;
			while (temp->hasLeft())
				temp = temp->getLeft();

			return temp;
		}
	}

	Node*	GetMax(Node* node)
	{
		if (node)
		{
			auto temp = node;
			while (temp->hasRight())
				temp = temp->getRight();

			return temp;
		}
	}

	void	DeletePredecessor(Node* current)
	{
		auto max = GetMax(current->getLeft());

		if (max == current->getLeft())
		{
			max->setRight(current->getRight());

			if (current->hasParent())
			{
				current->getParent()->replaceChild(current, max);
				max->setRight(current->getRight());
			}
			else
			{
				root = max;
				max->setParent(NULL);
			}
		}
		else
		{
			max->getParent()->removeChild(max);

			max->setRight(current->getRight());

			if (max->hasLeft())
			{
				auto min = GetMin(max->getLeft());
				min->setLeft(current->getLeft());
			}
			else
				max->setLeft(current->getLeft());

			if (current->hasParent())
				current->getParent()->replaceChild(current, max);
			else
			{
				root = max;
				max->setParent(NULL);
			}
		}

		delete current;
		nodeCount--;
	}

	void	DeleteSuccessor(Node* current)
	{
		auto min = GetMin(current->getRight());

		if (min == current->getRight())
		{
			min->setLeft(current->getLeft());

			if (current->hasParent())
			{
				current->getParent()->replaceChild(current, min);
				min->setLeft(current->getLeft());
			}
			else
			{
				root = min;
				min->setParent(NULL);
			}
		}
		else
		{
			min->getParent()->removeChild(min);

			min->setLeft(current->getLeft());

			if (min->hasRight())
			{
				auto max = GetMax(min->getRight());
				max->setRight(current->getRight());
			}
			else
				min->setRight(current->getRight());
			

			if (current->hasParent())
				current->getParent()->replaceChild(current, min);
			else
			{
				root = min;
				min->setParent(NULL);
			}
		}

		delete current;
		nodeCount--;
	}

public:
	BST()
		: root(NULL), nodeCount(0)
	{

	}

	~BST()
	{
		DeleteTree();
	}

	virtual void	Insert(T val)
	{
		// If this is the first node, make it the root of tree
		if (!root) root = new Node(val);

		// Otherwise
		else
		{
			// Get a pointer to root's address
			auto current = root;

			// For every node in the tree
			while (true)
			{
				// If new value is less than value of current node
				if (val < current->getData())
				{
					// If no left child, add new left child
					if (!current->getLeft()){
						current->setLeft(new Node(val, current));
						break;
					}

					// Else move to left child node
					else	current = current->getLeft();
				}

				// If new value is greater than value of current node
				else if (val > current->getData())
				{
					// If no right child, add new right child
					if (!current->getRight()){
						current->setRight(new Node(val, current));
						break;
					}

					// Else move to right child node
					else	current = current->getRight();
				}

				else return;
			}
		}
		nodeCount++;
	}

	virtual void	Delete(T val)
	{
		auto temp = Find(val);

		if (temp != NULL)
		{
			// If no children
			if (!temp->hasLeft() && !temp->hasRight())
			{
				if (temp->getParent())
				{
					temp->getParent()->removeChild(temp);
				}
				else
				{
					root = NULL;
				}

				delete temp;
				nodeCount--;
			}
			
			// If both children
			else if (temp->hasLeft() && temp->hasRight())
			{
				if (rand() % 2)
					DeletePredecessor(temp);
				else
					DeleteSuccessor(temp);
			}

			// If left children only
			else if (temp->hasLeft() && !temp->hasRight())
			{
				if (temp->getParent())
				{
					temp->getParent()->replaceChild(temp, temp->getLeft());
				}
				else
				{
					root = temp->getLeft();
					temp->getLeft()->setParent(NULL);
				}
				delete temp;
				nodeCount--;
			}

			// If right children only
			else if (!temp->hasLeft() && temp->hasRight())
			{
				if (temp->getParent())
				{
					temp->getParent()->replaceChild(temp, temp->getRight());
				}
				else
				{
					root = temp->getRight();
					temp->getRight()->setParent(NULL);
				}
				delete temp;
				nodeCount--;
			}

		}

		cout << nodeCount << " nodes remaining\n";
	}

	void	DeleteTree()
	{
		DeleteTree(root);
		root = NULL;
	}

	int		Size()
	{
		return nodeCount;
	}

	Node*	GetRoot()
	{
		return root;
	}
	
	Node*	Find(const T& val)
	{
		return Find(root, val);
	}

	virtual void Display(void(*function)(BST<T>*), BST<T> *tree)
	{
		function(tree);
	}

	InOrderPtr<T> iterator_inorder()
	{
		InOrderPtr<T> itr;

		itr.init(*this);

		return itr;
	}

	PreOrderPtr<T> iterator_preorder()
	{
		PreOrderPtr<T> itr;

		itr.init(*this);

		return itr;
	}

	PostOrderPtr<T> iterator_postorder()
	{
		PostOrderPtr<T> itr;

		itr.init(*this);

		return itr;
	}
};

#endif // !BST_H