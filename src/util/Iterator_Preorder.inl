template <class T>
class PreOrderPtr : public Iterator<T>
{
public:
	bool	init(Tree& tree)
	{
		root = tree.GetRoot();
		if (root)
			theStack->push(root);
		return theStack->empty();
	}

	bool	operator++()
	{
		Node *current = theStack->top();
		Node *next = current->getLeft();

		if (next)
		{
			theStack->push(next);
			return true;
		}
		while (!theStack->empty())
		{
			current = theStack->top();
			theStack->pop();
			next = current->getRight();

			if (next)
			{
				theStack->push(next);
				return true;
			}

		}
		return false;
	}

	Node*		operator*()
	{
		return theStack->top();
	}

	bool	end()
	{
		return theStack->empty();
	}
};