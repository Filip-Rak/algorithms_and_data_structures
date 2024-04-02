#include <iostream>
#include <list>	//lista wykorzystywana do przechowania wynikow

int* createJumpTable(std::string pattern)
{
	int length = pattern.length();	//zapisane w zmiennej, by unikn¹c bledny warning VS "buffer overflow"
	int* table = new int[length];	//Utworzenie wskaznika do tablicy
	table[0] = 0;	//tylko pierwszy indeks musi byc rowny 0


	int j = 0;
	for (int i = 1; i < length;)	//Wypelnienie tablicy indeksami przeskokow
	{
		if (pattern[j] == pattern[i])	
			table[i++] = 1 + j++;

		else if (j > 0)
			j = table[j - 1];

		else
			table[i++] = 0;
	}

	return table;
}

std::list<int> findPattern(std::string text, std::string pattern)
{
	std::list<int> indices;	//lista przwchowywujaca wyniki

	if (text.empty() || pattern.empty())
		return indices;

	int* table = createJumpTable(pattern);	//utworznie tablicy opisujacej przeskoki

	int j = 0;
	for (int i = 0; i < text.length();)	//szukanie wzoru w tekscie
	{
		if (text[i] == pattern[j])
		{
			i++;	//zwiekszenie indeksow
			j++;

			if (j == pattern.length())	//j przekroczylo wielkosc wzoru, co oznacza, ze go znalezlismy
			{
				indices.push_back(i - j);	//zapisujemy wynik
				j = 0;	//szukamy wzoru od nowa
			}
		}
		else if (j > 0)	//jezeli znaki sie nie zgadzaja, cofnij sie w poprzendie potencjalne miejsce
		{
			j = table[j - 1];
		}
		else
			i++;
	}

	delete[] table;	//zwolnienie pamieci

	return indices;	//nie lubie miec obslugi wejscia/wyjscia w funkcjach bedacych implementacja algorytmu. Wyniki wypisuje w mainie
}

int main() 
{
	std::string text = "abxabcabcabyabcaby", pattern = "abcaby";
	std::list<int> indices = findPattern(text, pattern);

	for (int i : indices)
		std::cout << "Index: " << i << "\n";
}