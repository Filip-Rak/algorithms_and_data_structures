#include <iostream>
#include <vector>

namespace Tree 
{
	struct Node {
		char character;
		Node* left;
		Node* right;

		Node(char character, Node* left = nullptr, Node* right = nullptr) :
			character(character), left(left), right(right) {}

		Node(Node* left = nullptr, Node* right = nullptr) :
			left(left), right(right), character(NULL) {}
	};

	void insert(Node*& root, char c)
	{
		if (!root)
			root = new Node(c);

		else if (c < root->character)
			insert(root->left, c);
		else if (c >= root->character)
			insert(root->right, c);
		//else  //jest rowne 
			//root->frequency += freq;
	}

	void print(Node* root)
	{
		if (!root)
			return;

		print(root->left);
		std::cout << "C:" << root->character << "\n";
		print(root->right);
	}

}

namespace List 
{
	struct Node {
		Tree::Node tree;
		int frequency;
		Node* next;

		Node(Tree::Node tree, int frequency, Node* next = nullptr) : tree(tree), frequency(frequency), next(next){}
	};

	void insert(Node*& head, Tree::Node tree, int freq = 1)
	{
		if (!head)
			head = new List::Node(tree, freq);	//Taki znak nie obecny

		else if (head->tree.character == tree.character)	//Znak obecny
			head->frequency += freq;
		else
			insert(head->next, tree, freq);
	}

	void print(Node* head)
	{
		if (!head)
			return;
		
		std::cout << "C: " << head->tree.character << " F: " << head->frequency << "\n";
		print(head->next);
	}

	void bubbleSort(Node*& head) 
	{
		if (!head) 
			return;

		bool swapped;
		Node* tgt;
		Node* l = nullptr;

		do 
		{
			swapped = false;
			tgt = head;

			while (tgt->next != l) 
			{
				if (tgt->frequency > tgt->next->frequency) 
				{
					std::swap(tgt->tree, tgt->next->tree);
					std::swap(tgt->frequency, tgt->next->frequency);
					swapped = true;
				}
				tgt = tgt->next;
			}
			l = tgt;
		} 
		while (swapped);
	}
}

Tree::Node mergeTrees(List::Node* head)
{
	while (head->next)
	{
		Tree::Node* t1 = new Tree::Node(head->tree);
		Tree::Node* t2 = new Tree::Node(head->next->tree);

		Tree::Node newTree(t1, t2);
		head->tree = newTree;
		head->frequency += head->next->frequency;

		//usun head->next;
		List::Node* tgt = head->next;
		head->next = head->next->next;
		delete tgt;

		std::cout << head->frequency << "\n";
	}

	return head->tree;
}

void getCodes(Tree::Node* tree, std::vector<std::string>& codes, std::string storage = "")
{
	if (!tree->left && !tree->right)
	{
		for (int i = 0; i < codes.size(); i++)
		{
			if (codes[i] == tree->character + "")
			{
				codes[i] = storage;
				return;
			}
		}
	}
	else
	{
		getCodes(tree->left, codes, storage += "0");
		getCodes(tree->right, codes, storage += "1");
	}
}

std::string encode(std::string message, std::string unique, std::vector<std::string> codes)
{
	std::string newMessage = "";

	for (int i = 0; i < message.size(); i++)
	{
		for (int j = 0; j < unique.size(); j++)
		{
			if (message[i] == unique[j])
			{
				newMessage += codes[j];
				break;
			}
		}
	}

	return newMessage;
}

int main()
{
	std::string input = "DAAFDDGFDSESESFSFDDFADFDAFDAFDDFSFDSFDSFDSDXFDDFSFDFFDAFDFDXFDFDGFDGFDSDAAAASAADSASASASASASASASAAAAAAAAASASSAWASAAAAAASASASDADDSADSADSSAASAAAADSADSSDAAAAADSASADSAAAAAAAASDADSADSADSASASASSSAAAAASSADSASADSAAAAFDFESDSADSADDSADADSFFFDSDSDAAAAAA";
	List::Node* list = nullptr;

	for (int i = 0; i < input.size(); i++)
		insert(list, Tree::Node(input[i]));

	std::string unique;
	List::Node* tgt = list;
	while (tgt)	//potrzebuje unikalnych znakow, a tak sie sklada, ze mam je w liscie
	{
		unique += tgt->tree.character;
		tgt = tgt->next;
	}

	Tree::Node result = mergeTrees(list);
	Tree::print(&result);

	std::vector<std::string> codes;
	for (int i = 0; i < unique.size(); i++)
		codes.push_back(unique[i] + "");

	getCodes(&result, codes);
	std::string encrypted = encode(input, unique, codes);

	std::cout << encrypted << "\n";
	for (int i = 0; i < unique.size(); i++)
	{
		std::cout << unique[i] << " " << codes[i] << "\n";
	}
}