
template <typename T>
SortedList<T>::SortedList()
	: head(NULL), tail(NULL), count(0), sortedAscending(true)
{

}


template <typename T>
SortedList<T>::~SortedList()
{
	clear();
}

template <typename T>
void SortedList<T>::insert(T value)
{
	if (sortedAscending) {
		insertAscending(value);
	}
	else {
		insertDescending(value);
	}
}

template <typename T>
void SortedList<T>::insertAscending(const T& val)
{
	Node *newNode = new Node(val);
	count++;

	// If this is the first node, this is the head and tail of list
	if (!head)
	{
		head = newNode;
		tail = newNode;
	}

	// Else if there are already some nodes in the list, insert in specified order
	else
	{
		auto temp = head;
		auto previous = head;

		while (temp)
		{
			if (temp->data > val) break;

			previous = temp;
			temp = temp->next;
		}

		if (temp == head)
		{
			newNode->next = head;
			head = newNode;
		}

		else if (!temp)
		{
			tail->next = newNode;
			tail = newNode;
		}

		else
		{
			previous->next = newNode;
			newNode->next = temp;
		}
	}
}

template <typename T>
void SortedList<T>::insertDescending(const T& val)
{
	Node *newNode = new Node(val);
	count++;

	// If this is the first node, this is the head and tail of list
	if (!head)
	{
		head = newNode;
		tail = newNode;
	}

	// Else if there are already some nodes in the list, insert in specified order
	else
	{
		auto temp = head;
		auto previous = head;

		while (temp)
		{
			if (val > temp->data) break;

			previous = temp;
			temp = temp->next;
		}

		if (temp == head)
		{
			newNode->next = head;
			head = newNode;
		}

		else if (!temp)
		{
			tail->next = newNode;
			tail = newNode;
		}

		else
		{
			previous->next = newNode;
			newNode->next = temp;
		}
	}
}

template <typename T>
void SortedList<T>::remove(unsigned int position)
{
	// If list is alreay empty, exit from the function
	if (!head) return;

	// If specified position is out of the range, throw an exception
	if (position < 0 || position > length())
		throw string(
		"\nEXCEPTION Index out of bounds :: remove("
		+ to_string(position) + ")\n");

	// If the first node is to be removed
	if (position == 0)
	{
		auto oldHead = head;				// Save address of the first node
		head = head->next;					// Make second node the new head of list

		delete oldHead;						// Delete old head (using saved address)
		count--;
	}

	// If any node except the first one is to be removed
	else
	{
		// Get address of the node preceding the node to be deleted
		auto previous = operator[](position - 1);

		// Get address of the node to be deleted
		auto node = previous->next;

		// Link preceding node to the node after the one that is to be deleted
		previous->next = node->next;

		// If the node to be deleted is the tail of the list, make preceding node the new tail
		if (node == tail) tail = previous;

		// Delete the node (deallocate memory)
		delete node;
		count--;
	}
}

template <typename T>
void SortedList<T>::clear()
{
	// If list is alreay empty, exit from the function
	if (!head)	return;

	// If there is only one node in list
	if (!head->next)
	{
		delete head;							// Delete the node, and
		count--;
		head = tail = NULL;						// point list's head to NULL to indicate that has nothing
	}

	// If there are more than one nodes
	else
	{
		// Get address of the start of list
		Node *previous, *current = head;

		// While the current node exists
		while (current)
		{
			previous = current;					// Save the address of current node
			current = current->next;			// Move to next node
			delete previous;					// Delete the node at saved address
			count--;
		}

		// Point list's head to NULL to indicate that contains nothing
		head = tail = NULL;
	}
}

template <typename T>
unsigned int SortedList<T>::size()
{
	// Return number of nodes in the list
	return count;
}

template <typename T>
T* SortedList<T>::search(const T& val)
{
	auto temp = head;

	if (!temp)
	{
		return nullptr;
	}

	else while (temp)
	{
		if (temp->data == val){
			return &temp->data;
		}
		else{
			temp = temp->next;
		}
	}

	return nullptr;
}

template <typename T>
T& SortedList<T>::operator[](unsigned int index)
{
	// Check for an out of bonds index
	if (index > size())
		throw out_of_range("Single_List[] index out of bounds");


	auto temp = head;
	for (unsigned int i = 0; i < index; i++)
		temp = temp->next;

	return temp->data;
}

template <typename T>
void SortedList<T>::sort()
{

}

template <typename T>
void SortedList<T>::setAscending(bool ascending)
{
	sortedAscending = ascending;
}

template <typename T>
bool SortedList<T>::isAscending()
{
	return sortedAscending;
}