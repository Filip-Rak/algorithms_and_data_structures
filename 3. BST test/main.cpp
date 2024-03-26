#include <iostream>

const std::string alphabet = "0123456789ABCDEFGHIJKLMNOP!@#$%^&*()QRSTUVWXYZ";

struct Word
{;
	std::string content;
	Word* parent, * left, * right;

	Word(std::string content, Word* parent = nullptr, Word* left = nullptr, Word* right = nullptr)
		: content(content), parent(parent), left(left), right(right) {}
};


bool isAbove(std::string base, std::string comparison)  //sprawdza czy pierwsze slowo jest pierwsze alfabetycznie
{
	if (base.size() < comparison.size())
		return true;

	else if (base.size() == comparison.size())
	{

		for (int i = 0; i < base.size(); i++)
		{
			int baseScore = 0, comparisonScore = 0;

			for (int j = 0; j < alphabet.size(); j++)
			{
				if (base[i] == alphabet[j])
					baseScore = j;

				if (comparison[i] == alphabet[j])
					comparisonScore = j;
			}

			if (baseScore < comparisonScore)
				return true;
		}

		return false;

	}

	else
		return false;
}

bool isAWord(std::string word)  //sprawdza czy ciag znakow kwalifikuje sie jako slowo w naszym alfabecie
{
	for (int i = 0; i < word.size(); i++)
	{
		bool found = false;


		for (int j = 0; j < alphabet.size(); j++)
		{
			if (word[i] == alphabet[j])
			{
				found = true;
				break;
			}
		}

		if (!found)
			return false;
	}

	return true;
}

Word* findWord(Word* root, std::string word)  //zadanie 1
{
	if (root)
	{
		if (root->content == word)
			return root;

		Word* result = findWord(root->left, word);

		if (result)
			return result;

		result = findWord(root->right, word);

		if (result)
			return result;

		return nullptr;
	}
	else
		return nullptr;
	
}

Word* advancedSearch(Word* root, std::string quarry)  //zadanie 2
{
	if (root)
	{
		if (root->content.size() < quarry.size())
			return nullptr;
		else
		{
			std::string subs = root->content.substr(0, quarry.size());
			if (subs == quarry)
				return root;
		}

		if (root->content == quarry)
			return root;

		Word* result = advancedSearch(root->left, quarry);

		if (result)
			return result;

		result = advancedSearch(root->right, quarry);

		if (result)
			return result;

		return nullptr;
	}
	else
		return nullptr;
}

bool addWord(Word* &root, std::string word)  //zadanie 3
{
	if (isAWord(word) && !findWord(root, word))
	{
		Word* newWord = new Word(word);

		if (root)
		{
			Word* parent = root;
			Word* child = root;

			while (child)
			{
				parent = child;
				
				if (isAbove(word, child->content))
					child = child->right;
				else
					child = child->left;
			}

			newWord->parent = parent;

			if (isAbove(word, parent->content))
				parent->right = newWord;
			else
				parent->left = newWord;
				
			return true;

		}
		else
		{
			root = newWord;
			return true;
		}
			
	}
	else 
		return false;
}


bool editWord(Word* root, std::string word, std::string newWord) //zadanie 4
{
	Word* instance = findWord(root, word);
	
	if (instance)
	{
		if (isAWord(newWord))
		{
			if (!findWord(root, newWord))
			{
				instance->content = newWord;
				return true;
			}
		}
	}

	return false;
}


int main()
{
	Word* tree1 = nullptr;  //drzewo



	std::cout << "Sukces = 1\nZad 3: Dodawanie\n";
	std::cout << addWord(tree1, "Q4#EWWBC") << "\n";  
	std::cout << addWord(tree1, "ABB!WW") << "\n";
	std::cout << addWord(tree1, "jjj") << "\n";		//niepoprawne slowo
	std::cout << addWord(tree1, "Q4#EWWBC") << "\n";  //kopia 1-szego slowa
	//slowa po wykonaniu: Q4#EWWBC, ABB!WW

	std::cout << "\nZad 4: Edycja\n";
	std::cout << editWord(tree1, "Q4#EWWBC", "000BBC") << "\n";
	std::cout << editWord(tree1, "AWA", "BWW") << "\n";	//Proba zamiany niesistniejacego slowa
	std::cout << editWord(tree1, "ABB!WW", "Bjj") << "\n";	//Podanie niepoprawnego nowego slowa
	std::cout << editWord(tree1, "ABB!WW", "000BBC") << "\n";	//Nowe slowo juz w slowniku
	//slowa po wykonaniu: 000BBC, ABB!WW


	std::cout << "\nZad 1: Wyszukiwanie:\n";
	if (findWord(tree1, "ABB!WW"))
		std::cout << "1\n";
	else
		std::cout << "0\n";
	
	if (findWord(tree1, "AWA")) //nie ma takiego slowa
		std::cout << "1\n";
	else
		std::cout << "0\n";



	std::cout << "\nZad 2: Zaawansowane wyszukiwanie: \n";
	if (advancedSearch(tree1, "0"))
		std::cout << "1\n";
	else
		std::cout << "0\n";
}