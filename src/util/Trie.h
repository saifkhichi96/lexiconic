#pragma once
#include "ListSingle.h"
#include <fstream>
#include <vector>
using namespace std;

class Trie
{
private:
	class Node
	{
	private:
		typedef Single_List<Node> Nodes;

		char	data;
		Nodes	children;
		Node*	parent;
	public:
		Node(char _d, Node* _p = NULL)
			: data(_d), parent(_p)
		{

		}

		char getData()
		{
			return data;
		}

		void addChild(char child)
		{
			children.insert_ascending(Node(child, this));
		}

		bool hasChild(char child)
		{
			if (children.find(Node(child)))
				return true;
			else return false;
		}

		Node& getChild(char child)
		{
			if (hasChild(child))
				return children.find(Node(child))->data;
		}

		Node& getParent()
		{
			return *this->parent;
		}

		Nodes* getChildren()
		{
			return &children;
		}

		int childCount()
		{
			return children.length();
		}

		bool operator == (Node& n)
		{
			return this->data == n.data;
		}
		bool operator >= (Node& n)
		{
			return this->data >= n.data;
		}
		bool operator <= (Node& n)
		{
			return this->data <= n.data;
		}
		bool operator > (Node& n)
		{
			return this->data > n.data;
		}
		bool operator < (Node& n)
		{
			return this->data < n.data;
		}
	};

	Node root;
public:
	Trie()
		: root(' '){

	}

	void insert(string word)
	{
		Node* iter = &root;

		for (char c : word)
		{
			if (!iter->hasChild(c))
				iter->addChild(c);

			iter = &iter->getChild(c);
		}
	}

	void loadFromFile(const string& filename)
	{
		ifstream infile(filename);

		if (!infile)
			return;

		while (!infile.eof())
		{
			string word;
			infile >> word;
			insert(word);
		}
	}

	vector<string> MatchPrefix(string& prefix)
	{
		Node* iter = &root;

		bool flag = true;
		for (char c : prefix)
		{
			if (iter->hasChild(c)){
				iter = &iter->getChild(c);
			}
			else{
				flag = false;
				break;
			}
		}

		vector<string> words;

		if (iter)
		{
			Node* hold = iter;

			string text = "";
			inorder(hold, text, words);
		}

		prefix.pop_back();
		vector<string> temp;
		for (string s : words)
			temp.push_back(prefix + s);

		return temp;
	}

	void inorder(Node* root, string& str, vector<string> & elements)
	{
		if (&root->getParent() == getRoot())
			str.clear();

		str.push_back(root->getData());

		if (root->childCount() > 0)
		{
			auto children = root->getChildren();
			for (int i = 0; i < children->length(); i++)
				inorder(&children->operator[](i)->data, str, elements);
		}
		else
		{
			elements.push_back(str);
			auto iter = root;
			while (iter->childCount() <= 1)
			{
				str.pop_back();
				iter = &iter->getParent();
			}
		}
	}

	Node* getRoot()
	{
		return &root;
	}
};