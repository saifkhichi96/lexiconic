#ifndef ITERATOR_H
#define ITERATOR_H

#include <stack>
using std::stack;

template <class T>
class Iterator
{
protected:
	typedef  BST<T>			Tree;
	typedef	 BST_Node<T>	Node;

	Node*			root;
	stack<Node*>*	theStack;
public:
	Iterator()
		: root(NULL)
	{
		theStack = new stack<Node*>();
	}

	virtual  bool	init(Tree&)	= 0;
	virtual  bool	operator++()= 0;
	virtual  bool	end()		= 0;
	virtual	Node*	operator*() = 0;

	friend class BST<T>;
};

#include "Iterator_Inorder.inl"
#include "Iterator_Preorder.inl"
#include "Iterator_Postorder.inl"

#endif // !ITERATOR_H