#include <iostream>

const int Y = 13;

struct Node {
	std::string value;
	Node* next;

	Node(std::string value, Node* next = nullptr) : value(value), next(next) {}
};

void insert(Node*& head, std::string value)
{
	if (!head)
	{
		head = new Node(value);
		return;
	}

	else
		insert(head->next, value);
}

void print(Node* head, std::string delimiter = "\n")
{
	if (!head)
		return;

	std::cout << head->value << delimiter;
	print(head->next);
}

void printList(Node** l, int size, std::string delimiter = " ")
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "KOLUMNA " << i + 1 << ": ";
		Node* tgt = l[i];
		while (tgt)
		{
			std::cout << tgt->value << delimiter;
			tgt = tgt->next;
		}
		std::cout << "\n";
	}
}

int getHash(std::string entry)
{
	int score = 0;
	for (int i = 0; i < entry.size(); i++)
		score += int(entry[i]) - int('a') + 1;

	return score % Y;
}

int main() 
{
	std::string people[] = { //aktualnie tylko male litery
		"piotr", "michal", "ania", "martyna", "wojtek", 
		"rafal", "antoni", "michau3", "kazik", "michau2",
		"andrei", "daphne", "fred", "scooby", "shaggy",
		"santa", "adelbert", "albert", "piotr2", "ananas"
	}; 

	Node** list = new Node * [Y];	//tworzenie / zerowanie tablicy
	for (int i = 0; i < Y; i++)
		list[i] = nullptr;

	for (std::string p : people)
	{
		int hash = getHash(p);
		insert(list[hash], p);
	}

	printList(list, Y, ", ");
}