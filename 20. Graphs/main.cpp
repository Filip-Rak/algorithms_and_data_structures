#include <iostream>
#include <fstream>

struct NodeLN {
	int relation, distance;
	NodeLN* next;
	
	NodeLN(int relation, int distance, NodeLN* next = nullptr)
		: relation(relation), distance(distance), next(next) {}
};

struct NodeLE {
	int from, to, length;
	NodeLE* next;

	NodeLE(int from, int to, int length, NodeLE* next = nullptr)
		: from(from), to(to), length(length), next(next) {}
};

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

void insert(NodeLE*& head, int from, int to, int length)
{
	if (!head)
	{
		head = new NodeLE(from, to, length);
		return;
	}
	else
		insert(head->next, from, to, length);
}

void clear(NodeLN*& head)
{
	if (!head)
		return;

	NodeLN* next = head->next;
	delete head;

	clear(next);
}

void clear(NodeLE*& head)
{
	if (!head)
		return;

	NodeLE* next = head->next;
	delete head;

	clear(next);
}

int** loadFrom(std::string filename, int &sizeOUT)
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

int** toMN(NodeLE* head, int& sizeOUT)
{
	//Na start szukam najwiekszego numeru grafu na liscie, posluzy dla wielkosci tablicy
	sizeOUT = 0;	//przypisuje do zera, bo numery grafow nie moga byc ujemne	

	NodeLE* tgt = head;
	while (tgt)
	{
		if (tgt->from > sizeOUT)
			sizeOUT = tgt->from;

		if (tgt->to > sizeOUT)
			sizeOUT = tgt->to;

		tgt = tgt->next;
	}

	sizeOUT += 1;

	int** MN = new int*[sizeOUT];	//utworzenie tablicy 2d i wyzeorwanie jej
	for (int i = 0; i < sizeOUT; i++)
	{
		MN[i] = new int[sizeOUT];
		for (int j = 0; j < sizeOUT; j++)
			MN[i][j] = 0;
	}

	tgt = head; 
	while (tgt)	//przypisanie dlugosci
	{
		MN[tgt->from][tgt->to] = tgt->length;
		tgt = tgt->next;
	}


	return MN;
}

int** toMN(NodeLN** head, int size)
{
	int** MN = new int*[size];
	for (int i = 0; i < size; i++)
	{
		MN[i] = new int[size];	//utworzenie macierzy
		for (int j = 0; j < size; j++)	//wyzerowanie macierzy
			MN[i][j] = 0;
	}

	for (int i = 0; i < size; i++)	//przepisywanie z LN do MN
	{
		NodeLN* tgt = head[i];
		while (tgt)
		{
			MN[i][tgt->relation] = tgt->distance;
			tgt = tgt->next;
		}
	}

	return MN;
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

NodeLN** toLN(NodeLE* input, int& sizeOUT)
{
	//Na start szukam najwiekszego numeru grafu na liscie, posluzy dla wielkosci tablicy
	sizeOUT = 0;	//przypisuje do zera, bo numery grafow nie moga byc ujemne	

	NodeLE* tgt = input;
	while (tgt)
	{
		if (tgt->from > sizeOUT)
			sizeOUT = tgt->from;

		if (tgt->to > sizeOUT)
			sizeOUT = tgt->to;

		tgt = tgt->next;
	}

	sizeOUT += 1;

	NodeLN** output = new NodeLN * [sizeOUT];	//utworzenie list sasiedztwa
	for (int i = 0; i < sizeOUT; i++)
		output[i] = nullptr;

	tgt = input;
	while (tgt)	//wypelnienie listy
	{
		insert(output[tgt->from], tgt->to, tgt->length);
		tgt = tgt->next;
	}

	return output;
}

NodeLE* toLE(int** MN, int size)
{
	NodeLE* list = nullptr;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (MN[i][j] != 0)
				insert(list, i, j, MN[i][j]);
		}
	}

	return list;
}

NodeLE* toLE(NodeLN** arr, int size)
{
	NodeLE* output = nullptr;

	for (int i = 0; i < size; i++)
	{
		NodeLN* tgt = arr[i];
		while (tgt)
		{
			insert(output, i, tgt->relation, tgt->distance);
			tgt = tgt->next;
		}
	}

	return output;
}

void print(int** MN, int size)	//wypisanie macierzy
{
	for (int i = 0; i < size; i++)	//dla linii
	{
		for (int j = 0; j < size; j++)	//dla znakow w jednej linii
			std::cout << MN[i][j] << "\t";

		std::cout << "\n";
	}
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

void print(NodeLE* head)
{
	std::cout << "LE->";

	int line = head->from;
	while (head)
	{
		if (head->from != line) {	//dla poprawy czytelnosci
			std::cout << "\n";
			line = head->from;
		}

		std::cout << head->from << "-" << head->to << "/" << head->length << "->";
		head = head->next;
	}

	std::cout << "NULL";
}

int main()
{
	int size;
	int** MN = loadFrom("graf.txt", size);	//przeczytanie z pliku i zapisanie jako MN

	std::cout << "MN:\n";	
	print(MN, size);


	std::cout << "\n\nMN -> LN:\n";	//Konwersja MN na LN
	NodeLN** LN = toLN(MN, size);
	print(LN, size);
	

	std::cout << "\n\nMN -> LE (znaki nowej linii dla czytelnosci):\n";	//Konwersja MN na LE
	NodeLE* LE = toLE(MN, size);
	print(LE);
	

	std::cout << "\n\nLN -> MN:\n";	//Konwersja z LN na MN
	{
		int** MN2 = toMN(LN, size);	//size jest znany z LN
		print(MN2, size);

		//Czysczenie pamieci
		for (int i = 0; i < size; i++)
			delete[] MN2[i];

		delete MN2;
	}

	std::cout << "\n\nLN -> LE (znaki nowej linii dla czytelnosci):\n";	//Konwersja z LN na LE
	{
		NodeLE* LE2 = toLE(LN, size);	//size znamy z LN
		print(LE2);

		//czyszczenie pamieci
		clear(LE2);
	}

	std::cout << "\n\nLE -> MN:\n";	//Konwersja LE -> MN
	{
		int size2;	//size2 wyciagniemy z funkcji
		int** MN2 = toMN(LE, size2);
		print(MN2, size2);

		//Czysczenie pamieci
		for (int i = 0; i < size2; i++)
			delete[] MN2[i];

		delete MN2;
	}

	std::cout << "\n\nLE -> LN:\n";
	{
		int size2;
		NodeLN** LN2 = toLN(LE, size2);
		print(LN2, size2);

		//Czysczenie pamieci
		for (int i = 0; i < size2; i++)
			clear(LN2[i]);
	}



	//Czysczenie pamieci
	for (int i = 0; i < size; i++)
	{
		delete[] MN[i];
		clear(LN[i]);
	}
	
	delete MN;
	delete LN;
	clear(LE);
}