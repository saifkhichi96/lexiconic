#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <iostream>
#include <fstream>
#include <ctime>
#include <stack>

#define ROT32(x, y) ((x << y) | (x >> (32 - y))) // avoid effor

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

typedef unsigned int uint;

template <typename Key, typename Value>
class HashTable
{
	Bucket**table;								// Bucket array
	uint		arraySize;						// Capacity
	uint		recordCount;					// Size
	uint		keyCollisions;					// Collisions

	const float THRESHOLD = 0.85f;				// Load factor should remain above this threshold to minimize collisions
	const uint MIN_SIZE = 10;					// Default size on creation if no size given

	struct Bucket
	{
		Key key;
		Value value;

		Bucket* next;

		Bucket(Key k, Value v)
			: key(k), value(v), next(NULL){	}
	};

public:
			HashTable(uint size = MIN_SIZE);	// Contructor

	uint	hashCode(Key key);					// Maps key on to a numeric value
	uint	insert(Key key, Value value);		// Adds a record
	bool	update(Key key, Value value);		// Updates a record
	bool	remove(Key key);					// Removes a record
	Bucket*	search(Key key);					// Looks up for a record

	bool	diskIn(string FILENAME);			// Reads the whole structure from a text file
	bool	diskOut(string FILENAME);			// Writes the whole structure to a text file

	uint	size();								// Number of stored records
	uint	collisions();						// Number of synonyms
	float	loadFactor();						// Loading factor = size() / collisions()

private:
	void	rehash();							// Rehashing increases Bucket array size to maintain load factor threshold
	uint	compress(uint value);				// Compresses any value to Bucket array range 0 to (N-1).

	uint	hashMurmu(const string& key, uint seed = 0);
	uint	hashPolynomial(const string& key, uint seed = 0);
	uint	hashMultiplicative(const string& key, int a, uint seed = 0);
	uint	hashCyclicShift(const string& key, uint seed = 0);
	
	uint	nextPrime(uint number);				// Gets a prime number equal or greater than given number
	bool	isPrime(uint number);				// Determines if a given number is prime or not
};

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(uint size)
	: recordCount(0), keyCollisions(0)
{
	// Set array size equal to the first prime number at or after the
	// given size value. Choosing a prime number as Bucket array size
	// for the particular hash function implemented.
	arraySize = nextPrime(size);

	// Create array and initialize the buckets
	table = new Bucket*[arraySize];
	for (int i = 0; i < arraySize; i++)
		table[i] = NULL;
}

template <typename Key, typename Value>
uint HashTable<Key, Value>::insert(Key key, Value value)
{
	if (!find(key))								// If this key is not already in the table
	{
		int index = hashCode(key);					// Get the index corresponding to this key

		if (table[index] == NULL){					// If no element already exists at this index
			table[index] = new Bucket(key, value);		// add a new Bucket at this index
			table[index]->next = NULL;
		}
		else										// Else if this index is already occupied (i.e. a collision occurs)
		{
			Bucket *existing = table[index];				// locate the end of chain
			while (existing->next)						// at this index
				existing = existing->next;

			Bucket *new_node = new Bucket(key, value);		// and add the new node at the
			existing->next = new_node;					// end of this chain
			new_node->next = NULL;
			keyCollisions++;										// count this collision
		}

		recordCount++;										// Count the new node added
		return index;								// Return the index of new node
	}
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::update(Key key, Value value)
{
	int index = hashCode(key);

	Bucket *existing = table[index];

	while (existing != NULL || existing->key != key)
		existing = existing->next;

	if (!existing)
		return false;

	existing->value = value;
	return true;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::remove(Key key)
{
	int index = hashCode(key);

	if (table[index] == NULL)
		return false;

	if (table[index]->key == key)
	{
		Bucket* hold = table[index];
		table[index] = table[index]->next;
		delete hold;
		return true;
	}
	else
	{
		Bucket* iter = table[index];
		while (iter->next != NULL || iter->next->key != key)
			iter = iter->next;

		if (iter->next == NULL)
			return false;

		else
		{
			Bucket* hold = iter->next;
			iter->next = iter->next->next;
			delete hold;
			return true;
		}
	}
}

template <typename Key, typename Value>
Bucket*	HashTable<Key, Value>::search(Key key)
{
	int index = hashCode(key);
	Bucket* temp = table[index];

	bool found = false;
	while (temp != NULL)
	{
		if (temp->key == key)
		{
			found = true;
			break;
		}

		temp = temp->next;
	}

	if (found) return temp;
	else return NULL;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::diskIn(string FILENAME)
{
	ifstream infile(FILENAME);

	// If the file could not be loaded
	if (!infile)
	{
		cout << "\nError loading data from file: " << FILENAME << endl;
		cout << "Closing now ..." << endl;
		return false;
	}

	// Load data into memory
	while (!infile.eof())
	{
		Key key;
		Value value;

		getline(infile, key);						// Read key
		//	getline(infile, value);						// Read value

		insert(key, key);							// Insert node into the table
	}

	return true;
}

template <typename Key, typename Value>
int HashTable<Key, Value>::hashCode(Key key)
{
	// Polynomial hash
	//	return compress(hashPolynomial(string(key)));

	// Multiplicative hash
	//	return compress(hashMultiplicative(string(key), 33, 5381));

	// Cyclic shift hash
	//	return compress(hashCyclicShift(string(key)));

	// Murmur hash
	return compress(hashMurmu(string(key)));
}

template <typename Key, typename Value>
int HashTable<Key, Value>::size()
{
	return recordCount;
}

template <typename Key, typename Value>
int HashTable<Key, Value>::collisions()
{
	return keyCollisions;
}

template <typename Key, typename Value>
float HashTable<Key, Value>::loadFactor()
{
	return float(recordCount) / arraySize;
}

template <typename Key, typename Value>
void HashTable<Key, Value>::rehash()
{
	int oldN = arraySize;
	arraySize = nextPrime(arraySize * 2);

	recordCount = 0;
	keyCollisions = 0;

	Word **newList = new Word*[arraySize];
	for (int i = 0; i < arraySize; i++)
		newList[i] = NULL;

	for (int i = 0; i < oldN; i++)
		if (wordList[i] == NULL)
			continue;
		else
		{
			Word *iter = wordList[i];

			do{
				insert(wordList[i]->key, wordList[i]->definition, newList);
				iter = iter->next;
			} while (iter);
		}

	delete[] wordList;
	wordList = newList;
	hashing = false;
}

template <typename Key, typename Value>
uint HashTable<Key, Value>::hashMurmu(const string& key, uint seed) {
	static const uint c1 = 0xcc9e2d51;
	static const uint c2 = 0x1b873593;
	static const uint r1 = 15;
	static const uint r2 = 13;
	static const uint m = 5;
	static const uint recordCount = 0xe6546b64;

	uint hash = seed;

	const int nblocks = key.size() / 4;
	const uint *blocks = (const uint *)key.cStr();
	int i;
	uint k;
	for (i = 0; i < nblocks; i++) {
		k = blocks[i];
		k *= c1;
		k = ROT32(k, r1);
		k *= c2;

		hash ^= k;
		hash = ROT32(hash, r2) * m + recordCount;
	}

	const uint *tail = (const uint *)(key.cStr() + nblocks * 4);
	uint k1 = 0;

	switch (key.size() & 3) {
	case 3:
		k1 ^= tail[2] << 16;
	case 2:
		k1 ^= tail[1] << 8;
	case 1:
		k1 ^= tail[0];

		k1 *= c1;
		k1 = ROT32(k1, r1);
		k1 *= c2;
		hash ^= k1;
	}

	hash ^= key.size();
	hash ^= (hash >> 16);
	hash *= 0x85ebca6b;
	hash ^= (hash >> 13);
	hash *= 0xc2b2ae35;
	hash ^= (hash >> 16);

	return hash;
	return 0;
}

template <typename Key, typename Value>
uint HashTable<Key, Value>::hashPolynomial(const string& key, uint seed)
{
	uint hash = seed;
	int a = nextPrime(rand() % 100);
	int size = key.size();

	for (int i = 0; i < size; i++)
		hash += staticCast<int>(key[i])* pow(a, size - i - 1);

	return hash;
}

template <typename Key, typename Value>
uint HashTable<Key, Value>::hashMultiplicative(const string& key, int a, uint seed)
{
	uint h = seed;
	for (uint i = 0; i < key.length(); ++i)
		h = ((h*a) + key[i]);

	return h;
}

template <typename Key, typename Value>
uint HashTable<Key, Value>::hashCyclicShift(const string& key, uint seed)
{
	uint hash = seed;
	for (int i = 0; i < key.size(); i++)
	{
		hash = (hash << 5) | (hash >> 27); // 5-bit cyclic shift
		hash += (int)key.at(i);
	}

	return hash;
}

template <typename Key, typename Value>
int HashTable<Key, Value>::compress(uint value)
{
	// MAD method
	int a;
	while (true)
	{
		a = 1 + 31;

		if (a % arraySize != 0)
			break;
	}
	int b = 27;
	return (a*value + b) % arraySize;
}

template <typename Key, typename Value>
int HashTable<Key, Value>::nextPrime(uint number)
{
	int i = number;
	for (; !isPrime(i); i++);
	return i;
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::isPrime(uint number)
{
	// Check if the current node is prime
	if (number <= 1)
		return false;
	else if (number <= 3)
		return true;
	else if (number % 2 == 0 || number % 3 == 0)
		return false;

	for (int i = 5; i*i <= number; i += 6)
		if (number % i == 0 || number % (i + 2) == 0)
			return false;

	return true;
}
#endif