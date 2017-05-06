#ifndef NODE_H
#define NODE_H

#include <iostream>

template <class T>
class BST_Node
{
public:
	BST_Node(T val,
		BST_Node* p = NULL,
		BST_Node* lt = NULL,
		BST_Node* rt = NULL)
		: parent(p), left(lt), right(rt), data(val)
	{

	}

	void	setLeft(BST_Node* child)
	{
		this->left = child;
		if (child)
			child->parent = this;
	}

	void	setRight(BST_Node* child)
	{
		this->right = child;
		if (child)
			child->parent = this;
	}

	void	setParent(BST_Node* parent)
	{
		this->parent = parent;
	}

	BST_Node*	getLeft()
	{
		if (hasLeft())
			return left;

		else return NULL;
	}

	BST_Node*	getRight()
	{
		if (hasRight())
			return right;

		else return NULL;
	}

	BST_Node*	getParent()
	{
		if (hasParent())
			return parent;

		else return NULL;
	}

	void	removeChild(BST_Node* child)
	{
		if (this->hasLeft() && child == getLeft())
			this->left = NULL;

		else if (this->hasRight() && child == getRight())
			this->right = NULL;
	}

	void	replaceChild(BST_Node* existing, BST_Node* child)
	{
		if (this)
		{
			if (this->hasLeft() && existing == this->getLeft())
			{
				this->setLeft(child);
			}
			else if (this->hasRight() && existing == this->getRight())
			{
				this->setRight(child);
			}
		}
	}

	bool	hasLeft()
	{
		if (this && left) return true;
		else return false;
	}

	bool	hasRight()
	{
		if (this && right) return true;
		else return false;
	}

	bool	hasParent()
	{
		if (this && parent) return true;
		else return false;
	}

	bool	isInternal()
	{
		if (hasParent() && (hasLeft() || hasRight()))
			return true;

		else return false;
	}

	bool	isExternal()
	{
		return !isInternal();
	}

	T&		getData()
	{
		return data;
	}

	void	setData(T value)
	{
		data = value;
	}

protected:
			T	data;
	BST_Node*	parent;
	BST_Node*	left;
	BST_Node*	right;
};

#endif