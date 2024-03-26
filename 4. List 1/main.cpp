#include <iostream>

struct Node {
	Node* next;
	int val;

	Node(int val, Node* next = nullptr) : val(val), next(next){}
};

void insert_last(Node*& head, int val)
{
	if (head)
		insert_last(head->next, val);
	else
		head = new Node(val);
}

void insert_last(Node*& head, Node* valueNode)
{
	if (head)
		insert_last(head->next, valueNode->val);
	else
		head = valueNode;
}

void print_all(Node* head)
{
	if (head)
	{
		std::cout << head->val << "\n";
		print_all(head->next);
	}
}

//Zadania

void remove_each_second(Node*& head) //Zadanie 1
{
	if (!head)
		return;

	if (head->next)  //usun nastepny element, jezeli istnieje
	{
		Node* tgt = head->next;
		head->next = tgt->next;
		delete tgt;
	}

	remove_each_second(head->next);		//to jest inny head->next, poprzedni zostal usuniety
}

void double_elements(Node*& head)  //Zadanie 2
{
	if (!head)
		return;
	
	Node* afterCopied = head->next;
	head->next = new Node(head->val, afterCopied);

	double_elements(afterCopied);
	
}

void copy_elements(Node*& dest, Node* origin, int segmentSize) //Zadanie 3. jezeli origin == dest i segmentSize > origin.size(), to elementy beda sie powtarzac 
{
	if (origin && segmentSize > 0)
	{
		insert_last(dest, origin->val);
		copy_elements(dest, origin->next, --segmentSize);
	}
}

float get_avg(Node* head)  //Zadanie 4
{
	int i = 0, sum = 0;
	while (head)
	{
		sum += head->val;
		i++;
		head = head->next;
	}

	if (i > 0)
		return float(sum) / float(i);
	else
		return 0;
}

void switch_with_next(Node*& head, int querry)  //Zadanie 5
{
	if (!head)	//czy lista istnieje
		return;

	if (head->val == querry)	//zamiana dla glowy
	{
		if (head->next)  //czy jest co zamieniac
		{
			Node* tgt = head; 
			Node* afterNext = head->next->next;

			head = head->next;
			head->next = tgt;
			tgt->next = afterNext;
		}

		return;

	}

	Node* tgt = head;
	while (tgt->next)
	{
		if (tgt->next->val == querry)
		{
			if (tgt->next->next)  //sprawdzamy czy jest z czym przeprowadzic zamiane
			{
				Node* first = tgt->next;
				Node* second = tgt->next->next;
				
				tgt->next = second;
				first->next = second->next;
				second->next = first;
			}

			return;
		}

		tgt = tgt->next;
	}
}

void remove_even(Node* head)  //Zadanie 6 
{
	if (!head)
		return;
	
	if (head->val % 2 == 0)
	{
		Node* tgt = head;
		head = head->next;
		delete tgt;
	}

	while (head->next)
	{
		if (head->next->val % 2 == 0)
		{
			Node* tgt = head->next;
			head->next = head->next->next;
			delete tgt;
		}
		else  //usuwanie juz efektywnie przesuwa o jeden
			head = head->next;
	}
	
}

void swap_each_second(Node*& previous, Node* first)  //Zadanie 7.2 | Rekurencyjnie zamienia pozostale elementy
{
	if (!first || !first->next)
		return;

	previous->next = first->next;
	first->next = first->next->next;
	previous->next->next = first;

	swap_each_second(first, first->next);
}

void swap_each_second(Node*& head)	//Zadanie 7.1 | Zamienia glowe z drugim elementem
{
	if (!head || !head->next)
		return;

	Node* tgt = head; 
	head = head->next; 
	tgt->next = head->next;
	head->next = tgt;

	swap_each_second(tgt, tgt->next);
}	

int main() 
{
	Node* list = nullptr;
	for (int i = 0; i < 10; i++)	//insert 1 - 10
		insert_last(list, i + 1);

	//remove_each_second(list);
	//copy_elements(list, list, 10);
	
	//std::cout << get_avg(list);
	//remove_even(list);
	//switch_with_next(list, 1);
	//double_elements(list);
	swap_each_second(list);

	print_all(list);
}