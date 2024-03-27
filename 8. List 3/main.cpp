#include <iostream>

struct Node {
	int value;
	Node* parent, * left, * right;

	Node(int val, Node* parent, Node* left = nullptr, Node* right = nullptr)
		: value(val), parent(parent), left(left), right(right){}
};

struct List {
	int val;
	List* next;
	List(int val, List* next = nullptr): val(val), next(next){}
};

void pushFront(List*& head, int val)
{
	List* tgt = head;
	head = new List(val, tgt);
}

void insert(Node*& root, int val, Node* parent = nullptr)
{
	if (!root)
		root = new Node(val, parent);
	else if (root->value < val)
		insert(root->left, val, root);
	else
		insert(root->right, val, root);

}

void allVals(Node* root, List*& head)
{
	if (!root)
		return;

	allVals(root->left, head);
	pushFront(head, root->value);
	allVals(root->right, head);
}

void deleteList(List*& head)
{
	if (head)
	{
		deleteList(head->next);
		delete head;
		head = nullptr;
	}
}

void insert_fitting(Node*& root, int val, int margin = 5)
{
	List* head = nullptr;
	allVals(root, head);

	while (head)
	{
		if (abs(head->val - val) <= margin)
			return;

		head = head->next;
	}

	insert(root, val);
	deleteList(head);
}

void inorder(Node* root)
{
	if (!root)
		return;

	inorder(root->left);
	std::cout << root->value << "\n";
	inorder(root->right);
}

void bubbleSort(List*& head) 
{
	if (!head || !head->next) // lista jest pusta lub ma jeden element
		return; 

	bool swapped;
	do 
	{
		swapped = false;
		List* tgt = head;
		List** link = &head; // wskaznik do wskaznika do tgt

		while (tgt->next) 
		{
			if (tgt->val > tgt->next->val)	//Zamien
			{
				List* tmp = tgt->next;
				tgt->next = tmp->next;
				tmp->next = tgt;
				*link = tmp;

				swapped = true;
			}
			link = &(*link)->next;
			tgt = *link;
		}
	} 
	while (swapped); // Kontynuuj dopoki nie wykona sie zadna zamiana
}

void printList(List* head)
{
	if (head)
	{
		std::cout << head->val << "\n";
		printList(head->next);
	}
}

int main()
{
	Node* root = nullptr;
	int values[] = {-2, 2, 5, 7, 10, 11, -8};
	for (int i = 0; i < sizeof(values) / sizeof(int); i++)
		insert_fitting(root, values[i]);


	//inorder(root);

	List* l = nullptr;
	pushFront(l, 1);
	pushFront(l, -1);
	pushFront(l, 3);
	pushFront(l, -8);

	bubbleSort(l);
	printList(l);
}