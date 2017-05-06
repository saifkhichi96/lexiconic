template <class T>
class BreadthFirstPtr : public Iterator<T>
{
public:
	BreadthFirstPtr(Tree& tree)
		: Iterator(tree)
	{
		if (root)
		traverse(root);
	}

	virtual bool	operator++()
	{
		Node* node = theQueue->front();
		theQueue->pop();
		
		if (node->hasLeft())	theQueue->push(node->getLeft());
		if (node->hasRight())	theQueue->push(node->getRight());

		return theQueue->empty();
	}
protected:
	virtual void	traverse(Node* node)
	{
		theQueue->push(node);
	}
};

