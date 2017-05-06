//#ifndef MAP_HPP
//#define MAP_HPP
//
//#include <ctime>
//#include <stack>
//#include <iostream>
//#include <fstream>
//#include "Word.h"
//
//#define ROT32(x, y) ((x << y) | (x >> (32 - y))) // avoid effor
//
//using std::cout;
//using std::string;
//
//typedef unsigned int uint;
//
//class Map
//{
//public:
//	Map(int size = 250000)
//		: n(0)
//	{
//		N = GetNextPrime(size);
//		cout << N << endl;
//		wordList = new Word*[N];
//
//		for (int i = 0; i < N; i++)
//			wordList[i] = NULL;
//	}
//
//	int				insert(string& wd, const string& mean)
//	{
//		//// Wait till rehashing is complete
//		//while (hashing);
//
//
//		//if (loadFactor() > 0.5f){
//		//	hashing = true;
//		//	rehash();
//		//}
//
//		return  insert(wd, mean, wordList);
//	}
//	bool			update(string& wd, const string& new_mean)
//	{
//		int index = hash(wd);
//
//		Word *existing = wordList[index];
//
//		while (existing != NULL || existing->key != wd)
//			existing = existing->next;
//
//		if (!existing)
//			return false;
//
//		existing->definition = new_mean;
//		return true;
//	}
//	bool			remove(string& wd)
//	{
//		int index = hash(wd);
//
//		if (wordList[index] == NULL)
//			return false;
//
//		if (wordList[index]->key == wd)
//		{
//			Word* hold = wordList[index];
//			wordList[index] = wordList[index]->next;
//			delete hold;
//			return true;
//		}
//		else
//		{
//			Word* iter = wordList[index];
//			while (iter->next != NULL || iter->next->key != wd)
//				iter = iter->next;
//
//			if (iter->next == NULL)
//				return false;
//
//			else
//			{
//				Word* hold = iter->next;
//				iter->next = iter->next->next;
//				delete hold;
//				return true;
//			}
//		}
//
//	}
//	const string	lookUp(string& wd)
//	{
//		int index = hash(wd);
//		Word* temp = wordList[index];
//
//		string value;
//		bool found = false;
//		while (temp != NULL){
//			if (temp->key == wd){
//				found = true;
//				value = temp->definition;
//				break;
//			}
//
//			temp = temp->next;
//		}
//
//		if (found) return value;
//		else return "Not found";
//	}
//
//	Word			getWord()
//	{
//		int index = rand() % N;
//
//		while (wordList[index] == NULL)
//			index = rand() % N;
//
//		return *wordList[index];
//	}
//	Word*			getSequence(const int len)
//	{
//		Word *list = new Word[len];
//
//		for (int i = 0; i < len; i++)
//			list[i] = getWord();
//
//		return list;
//	}
//
//	bool			diskIn(string FILENAME)
//	{
//		ifstream infile(FILENAME);
//		string word, meaning;
//
//		// If the file could not be loaded
//		if (!infile)
//		{
//			cout << "\nError loading data from file: " << FILENAME << endl;
//			cout << "Closing now ..." << endl;
//			return false;
//		}
//
//		// Load data into memory
//		while (!infile.eof())
//		{
//			getline(infile, word);								// Skip a line
//			getline(infile, word);								// Read word/phrase till end of the line
//			getline(infile, meaning, '$');						// Read multilined definition of this word till a '$' is encountered
//
//			insert(word, meaning);								// Insert word into Dictionary
//		}
//
//		return true;
//	}
//
//	int				capacity(){ return N; }
//	int				size(){ return n; }
//	int				collisions()
//	{
//		int count = 0;
//		for (int i = 0; i < N; i++)
//			if (wordList[i] == NULL)
//				continue;
//			else count++;
//
//		
//		return size() - count;
//	}
//	float			loadFactor()
//	{
//		return float(n) / N;
//	}
//private:
//	int				insert(string& wd, const string& mean, Word **list)
//	{
//		if (lookUp(wd) == "Not found")
//		{
//			// Get the index corresponding to this key
//			int index = hash(wd);
//
//			// If no element already exists at this index
//			if (list[index] == NULL){
//				list[index] = new Word(wd, mean);
//				list[index]->next = NULL;
//			}
//			// If an alement already exists at this index, use linear chaining
//			else{
//				Word *existing = list[index];
//				while (existing->next != NULL){
//					existing = existing->next;
//				}
//
//				Word *new_node = new Word(wd, mean);
//				new_node->next = NULL;
//
//				existing->next = new_node;
//				cols++;
//			}
//
//			// Count the node added
//			n++;
//			return index;
//		}
//	}
//	bool			hashing = false;
//	void			rehash()
//	{
//		cout << "Rehashing ...\n";
//		int oldN = N;
//		N = GetNextPrime(N * 2);
//
//		n = 0;
//		cols = 0;
//
//		Word **newList = new Word*[N];
//		for (int i = 0; i < N; i++)
//			newList[i] = NULL;
//
//		for (int i = 0; i < oldN; i++)
//			if (wordList[i] == NULL)
//				continue;
//			else
//			{
//				Word *iter = wordList[i];
//
//				do{
//					insert(wordList[i]->key, wordList[i]->definition, newList);
//					iter = iter->next;
//				} while (iter);
//			}
//
//		delete[] wordList;
//		wordList = newList;
//		hashing = false;
//	}
//
//	uint			murmur(string& key, uint seed = 0) {
//		static const uint c1 = 0xcc9e2d51;
//		static const uint c2 = 0x1b873593;
//		static const uint r1 = 15;
//		static const uint r2 = 13;
//		static const uint m = 5;
//		static const uint n = 0xe6546b64;
//
//		uint hash = seed;
//
//		const int nblocks = key.size() / 4;
//		const uint *blocks = (const uint *)key.c_str();
//		int i;
//		uint k;
//		for (i = 0; i < nblocks; i++) {
//			k = blocks[i];
//			k *= c1;
//			k = ROT32(k, r1);
//			k *= c2;
//
//			hash ^= k;
//			hash = ROT32(hash, r2) * m + n;
//		}
//
//		const uint *tail = (const uint *)(key.c_str() + nblocks * 4);
//		uint k1 = 0;
//
//		switch (key.size() & 3) {
//		case 3:
//			k1 ^= tail[2] << 16;
//		case 2:
//			k1 ^= tail[1] << 8;
//		case 1:
//			k1 ^= tail[0];
//
//			k1 *= c1;
//			k1 = ROT32(k1, r1);
//			k1 *= c2;
//			hash ^= k1;
//		}
//
//		hash ^= key.size();
//		hash ^= (hash >> 16);
//		hash *= 0x85ebca6b;
//		hash ^= (hash >> 13);
//		hash *= 0xc2b2ae35;
//		hash ^= (hash >> 16);
//
//		return hash;
//		return 0;
//	}
//
//	uint			polynomial_hash(string& key, uint seed = 0){
//		uint hash = 0;
//
//		int a = GetNextPrime(rand());
//		int size = key.size();
//		for (int i = 0; i < size; i++)
//			hash += static_cast<int>(key[i])* pow(a, size - i - 1);
//
//		return hash;
//	}
//
//	uint			cyclic_shift_hash(string& key, uint seed = 0)
//	{
//		uint hash = 0;
//		for (int i = 0; i < key.size(); i++)
//		{
//			hash = (hash << 5) | (hash >> 27); // 5-bit cyclic shift
//			hash += (int)key.at(i);
//		}
//
//		return hash;
//	}
//
//	int				hash(string& key)
//	{
//		// Convert key to upper case letters
//		toUpper(key);
//
//		// Polynomial hash
//	//	return compress(polynomial_hash(key));
//
//		// Cyclic shift hash
//	//	return compress(cyclic_shift_hash(key));
//
//		// Murmur hash
//		return compress(murmur(key));
//	}
//
//	int				GetNextPrime(int n)
//	{
//		int i = n;
//		for (; !isPrime(i); i++);
//		return i;
//	}
//	
//	bool			isPrime(int n)
//	{
//		// Check if the current node is prime
//		if (n <= 1)
//			return false;
//		else if (n <= 3)
//			return true;
//		else if (n % 2 == 0 || n % 3 == 0)
//			return false;
//			
//		for (int i = 5; i*i <= n; i += 6)
//			if (n % i == 0 || n % (i + 2) == 0)
//				return false;
//		
//		return true;
//	}
//	
//	int				compress(int value)
//	{
//		// MAD method
//		int a;
//		while (true)
//		{
//			a = 1 + rand() % 100;
//
//			if (a % N != 0)
//				break;
//		}
//		int b = rand() % 100;
//		return abs(a*value + b) % N;
//	}
//
//	void			toUpper(string& str)
//	{
//		for (auto it = str.begin(); it != str.end(); it++)
//		{
//			*it = toupper(*it);
//		}
//	}
//	
//	Word**			wordList;		// Bucket array
//	int				N;				// Capacity
//	int				n;				// Size
//	int				cols;			// Collisions
//};
//
//#endif