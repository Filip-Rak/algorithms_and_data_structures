#include <iostream>

struct Node {
	int val;
	Node* next;

	Node(int val, Node* next = nullptr) : val(val), next(next){}
};

void insert_last(Node*& head, int val)
{
	if (head)
		insert_last(head->next, val);
	else
		head = new Node(val);
}

void insert_last(Node*& head, Node* newNode)
{
	if (head)
		insert_last(head->next, newNode);
	else
		head = newNode;
}

void insert_first(Node*& head, int val)
{
	Node* newElement = new Node(val, head);
	head = newElement;
}

void print_all(Node* head)
{
	if (head)
	{
		std::cout << head->val << "\n";
		print_all(head->next);
	}
}

void join_reversed_copy(Node* head)  //Zadanie 1, iteracyjnie
{
	if (!head)
		return;

	Node* newList = new Node(head->val);

	while (head->next)
	{
		insert_first(newList, head->next->val);
		head = head->next;
	}

	head->next = newList;
}

void merge(Node*& dest, Node*& originA, Node*& originB)  //rekurencyjnie. Przyjmuje, ze desc jest zawsze podany poprawny, tj. NULL
{

	if (originA && originB)	
	{
		Node* tgt = originA;	
		if (originA->val < originB->val) //A
			originA = originA->next;
		
		else
		{
			tgt = originB;	//B
			originB = originB->next;
		}

		tgt->next = nullptr;
		dest = tgt;
	}
	else 
	{
		if (originA)
			dest = originA;
		else
			dest = originB;

		return;
	}

	merge(dest->next, originA, originB);
	
}

void split(Node*& origin, Node*& destA, Node*& destB)
{
	bool swap = false;
	Node* startA = new Node(-1);	//tymczasowy poczatek dla nowych list
	Node* startB = new Node(-1);
	Node *tgtA = startA, *tgtB = startB;

	while (origin)	//uzupelnianie nowych list
	{
		if (swap){
			tgtA->next = origin;
			origin = origin->next;
			tgtA->next->next = nullptr;
			tgtA = tgtA->next;
		}
		else{
			tgtB->next = origin;
			origin = origin->next;
			tgtB->next->next = nullptr;
			tgtB = tgtB->next;
		}

		swap = !swap;	//zamiana listy docelowej
	}

	destA = startA->next;	//ustawianie wskaznikow list docelowych
	destB = startB->next;

	delete startA;	//usuwanie poczatkow list docelowych
	delete startB;	
}

int main()
{
	Node* list = nullptr;

	for(int i = 1; i <= 10; i++)
		insert_last(list, i);

	//join_reversed_copy(list);

	//Node* list1 = nullptr;
	//insert_last(list1, 1);
	//insert_last(list1, 8);
	//insert_last(list1, 13);
	//insert_last(list1, 54);

	Node* list2 = nullptr;
	insert_last(list2, 1);
	insert_last(list2, 2);
	insert_last(list2, 3);

	//merge(list, list1, list2);

	//split(list, list1, list2);

	//print_all(list);
	//std::cout << "\n";
	join_reversed_copy(list2);
	print_all(list2);

}