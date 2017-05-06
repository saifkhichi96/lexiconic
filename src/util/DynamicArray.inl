
/*
Default constructor, initializes object, and creates an array of given size.
If no size is specified, no array is created.
: parameter: uint sz (size of array to be created, 0 by default)
*/
template <typename T>
DynamicArray<T>::DynamicArray(uint sz)
	: maxElements(sz), noOfElements(0), array(NULL)
{
	if (capacity() != 0)
		array = new T[capacity()];
}

/*
Destructor reclaims memory used by the array
*/
template <typename T>
DynamicArray<T>::~DynamicArray()
{
	if (array) delete[] array;
}

/*
Inserts a new value into the array in the order specified. Order can be either ascending or
descending. If no order is specified, insertions are made in ascending order.
: parameters: T value (new value to be inserted)
bool order (false for ascending, true for descending, false by default)
*/
template <typename T>
void DynamicArray<T>::insert(T value, bool reverse)
{
	// If array has not yet been created, create a new array of unit size
	if (array == NULL || capacity() == 0)
	{
		array = new T[5];
		maxElements = 5;
	}

	// If array is full, double capacity
	else if (isFull())
	{
		doubleCapacity();
	}

	// Insert in ascending order
	if (reverse == false)
	int i = 0;
	for (; i < noOfElements; i++)
		if (array[i] >= value) break;


	if (noOfElements + 1)
		doubleCapacity();

	for (int j = i; j < noOfElements + 1; j++)
		array[j] = array[j + 1];

	array[i] = value;
	
}

/*
Inserts a new value at end of the array.
: parameters: T value (new value to be inserted)
*/
template <typename T>
void DynamicArray<T>::append(T value)
{
	// If array has not yet been created, create a new array of unit size
	if (array == NULL || capacity() == 0)
	{
		array = new T[5];
		maxElements = 5;
	}

	// If array is full, double capacity
	else if (isFull())
	{
		doubleCapacity();
	}

	array[noOfElements++] = value;
}

/*
Deletes everything in the array. Does not affect capacity which remains same
as was before clearing the array.
*/
template <typename T>
void DynamicArray<T>::clear()
{
	if (array) delete[] array;
	noOfElements = 0;
}

/*
Removes the element at the given index.
: parameter: uint index (location of element in the array)
*/
template <typename T>
void DynamicArray<T>::remove(unsigned int index)
{
	// Check that index is within the boundaries of array
	if (index < 0 || index >= size())
		throw out_of_range("DynamicArray index out of range");

	// Move all elements after the element to delete one step back
	for (int i = index; i < noOfElements; i++)
		array[i] = array[i + 1];

	// Down-count the element that has been removed
	noOfElements--;
}

/*
Returns the number of elements in the array
*/
template <typename T>
uint DynamicArray<T>::size()
{
	return noOfElements;
}

/*
Returns maximum number of elements that the array can currently hold
*/
template <typename T>
uint DynamicArray<T>::capacity()
{
	return maxElements;
}

/*
Searches for an element in the array and returns its index
*/
template <typename T>
T* DynamicArray<T>::search(const T& value)
{
	uint low = 0;
	uint high = noOfElements;

	while (low <= high)
	{
		uint mid = (low + high) / 2;

		if (array[mid] == value)
			return &array[mid];

		else if (array[mid] < value)
			low = mid + 1;

		else if (array[mid] > value)
			high = mid - 1;
	}

	return NULL;
}

/*
Checks if the array is full.
*/
template <typename T>
bool DynamicArray<T>::isFull()
{
	if (noOfElements >= maxElements)
		return true;

	else
		return false;
}

/*
Doubles the size of the array
*/
template <typename T>
void DynamicArray<T>::doubleCapacity()
{
	T* temporary = new T[maxElements * 2];

	for (int i = 0; i < maxElements; i++)
		temporary[i] = array[i];

	delete[] array;
	array = temporary;
	maxElements *= 2;
}

/*
Returns reference to the node at given index
*/
template <typename T>
T& DynamicArray<T>::operator[](uint index)
{
	// Check that index is within the boundaries of array
	if (index < 0 || index >= size())
		throw out_of_range("DynamicArray index out of range");

	return array[index];
}