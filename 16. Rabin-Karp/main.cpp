#include <iostream>

struct List	//uzywana tylko do przechowywania wynikow
{
	int index;
	List* next;
	List(int index, List* next = nullptr) 
		: index(index), next(next){}
};

void insertList(List*& head, int index)
{
	if (!head)
		head = new List(index);
	else
		insertList(head->next, index);
}

void printList(List* head)
{
	if (!head)
		return;
	
	std::cout << head->index << " ";
	printList(head->next);
}

void deleteList(List*& head)
{
	if (!head)
		return;

	List* tgt = head->next;
	delete head;
	head = nullptr;

	deleteList(tgt);
}

List* findPattern(const std::string text, const std::string pattern, const int modulus = 67)	//Rabin-Karp
{
#define ALPHABET 256

	if (text.size() < pattern.size() || pattern == "")
		return nullptr;

	List* output = nullptr;	//W tej liscie beda zapisane i zwrocone wyniki

	int windowHash = 0;	//hasze 
	int patternHash = 0;

	int buffer = 1;	//pomoc dla mnoznika
	int leadMulti = 0;	//mnoznik dla znaku, przyda sie przy usuwaniu

	for (int i = 0; i < pattern.size(); i++)	//liczenie haszu
	{
		patternHash = (ALPHABET * patternHash + int(pattern[i])) % modulus;	//mno¿ymy ilosc znakow w alfabecie przez sume haszu
		windowHash = (ALPHABET * windowHash + int(text[i])) % modulus;	// w celu ograniczenia potencjalnych kolizji

		leadMulti = buffer;	//oblicznie mnoznika
		buffer = (ALPHABET * buffer) % modulus;	//uzywam takiej metody z dowma zmiennymi by osczedzic jednej petli / POW'a
	}

	for (int i = 0; i <= text.size() - pattern.size(); i++)
	{
		if (windowHash == patternHash)	//wartosci hashy sie zgadzaja
		{
			bool found = true;
			for (int j = 0; j < pattern.size(); j++)	//sprawdz czy ciagi znakow sa takie same
			{
				if (pattern[j] != text[j + i])
				{
					found = false;
					break;
				}
			}

			if (found)	//jezeli tak to dodaj indeks do listy
				insertList(output, i);
		}


		windowHash -= (int(text[i]) * leadMulti) % modulus;	//usuniecie znaku po lewej
			
		if (windowHash < 0)	//upewniamy sie, ze wartosc jest dodatnia
			windowHash += modulus;

		windowHash = (windowHash * ALPHABET + int(text[i + pattern.size()])) % modulus;	//uzupelniamy o wartosc po prawej
	}

	return output;
}

int main()
{
	List* indexes = findPattern("ABABCABAB", "AB");
	printList(indexes);
	deleteList(indexes);
}