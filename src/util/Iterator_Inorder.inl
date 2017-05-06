template <class T>
class InOrderPtr : public Iterator<T>
{
public:
	bool	init(Tree& tree)
	{
		root = tree.GetRoot();
		goLeft(root);
		return theStack->empty();
	}

	bool	operator++()
	{
		if (!theStack->empty())
		{
			auto temp = theStack->top()->getRight();
			theStack->pop();
			if (temp)
				goLeft(temp);
		}

		return theStack->empty();
	}

	Node*		operator*()
	{
		return theStack->top();
	}

	bool	end()
	{
		return theStack->empty();
	}

private:
	bool	goLeft(Node* node)
	{
		while (node)
		{
			theStack->push(node);
			node = node->getLeft();
		}

		return theStack->empty();
	}
};

