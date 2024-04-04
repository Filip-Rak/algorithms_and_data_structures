#include <iostream>
#include <fstream>

struct NodeLN {
	int relation, distance;
	NodeLN* next;

	NodeLN(int relation, int distance, NodeLN* next = nullptr)
		: relation(relation), distance(distance), next(next) {}
};

int** loadFrom(std::string filename, int& sizeOUT)
{
	std::fstream file(filename, std::ios::in);	//otworzenie pliku
	file >> sizeOUT;

	int** MN = new int* [sizeOUT];	//przygotowanie macierzy
	for (int i = 0; i < sizeOUT; i++)
		MN[i] = new int[sizeOUT];


	for (int i = 0; i < sizeOUT; i++)	//wczytywanie: dla linii
	{
		for (int j = 0; j < sizeOUT; j++)	//dla znakow w konkretnej linii
			file >> MN[i][j];
	}

	file.close();	//zamkniecie pliku

	return MN;
}

void insert(NodeLN*& head, int relation, int distance)
{
	if (!head)
	{
		head = new NodeLN(relation, distance);
		return;
	}
	else
		insert(head->next, relation, distance);
}

void clear(NodeLN*& head)
{
	if (!head)
		return;

	NodeLN* next = head->next;
	delete head;

	clear(next);
}

void insertionSort(NodeLN*& head) {
	if (head == nullptr || head->next == nullptr) {
		return; // Lista jest pusta lub ma tylko jeden element
	}

	NodeLN* sorted = nullptr; // Lista posortowanych elementów
	NodeLN* current = head; // Aktualny element do wstawienia

	while (current != nullptr) {
		NodeLN* next = current->next; // Zapamiêtujemy nastêpny element

		// Znajdujemy miejsce wstawienia dla current w posortowanej liœcie
		NodeLN** sortedPtr = &sorted;
		while (*sortedPtr != nullptr && (*sortedPtr)->distance < current->distance) {
			sortedPtr = &((*sortedPtr)->next);
		}

		// Wstawiamy current w posortowanej liœcie
		current->next = *sortedPtr;
		*sortedPtr = current;

		current = next; // Przechodzimy do nastêpnego elementu
	}

	head = sorted; // Aktualizujemy g³owê listy
}

void print(NodeLN** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "LN[" << i << "]->";

		NodeLN* tgt = arr[i];
		while (tgt)
		{
			std::cout << tgt->relation << "/" << tgt->distance << "->";
			tgt = tgt->next;
		}


		std::cout << "NULL\n";
	}
}

NodeLN** toLN(int** MN, int size)
{
	NodeLN** relations = new NodeLN * [size];
	for (int i = 0; i < size; i++)
		relations[i] = nullptr;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (MN[i][j] != 0)
				insert(relations[i], j, MN[i][j]);
		}
	}

	return relations;
}



NodeLE* kruskal(NodeLE* head)
{
	NodeLE* output = nullptr;

	while (head)	//dodawanie krawedzi do wyniku
	{
		//pomin dodawanie jezeli istnieje juz polaczenie z tym punktem
		if (!connection(output, head->from, head->to))
			insert(output, head->from, head->to, head->length);	//kopia nie przeniesienie. Nie chce zniszczyc oryginalu

		head = head->next;
	}
}

int main()
{
	int size;
	int** MN = loadFrom("graf.txt", size);	//przeczytanie z pliku i zapisanie jako MN
	NodeLN** LN = toLN(MN, size);
	print(LN, size);	//konwersja na LN

	print(LE);
	insertionSort(LE);
	std::cout << "\n\n";
	print(LE);

	//usuwanie pamieci
	for (int i = 0; i < size; i++)
		delete[] MN[i];

	delete MN;

	clear(LE);
}