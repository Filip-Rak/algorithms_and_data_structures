#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct Track
{
	int id, release_date;
	std::string performer, name, authors;
	Track* next;

	Track(int id, std::string performer, std::string name, int release, std::string authors, Track* next = nullptr) : id(id), performer(performer), name(name), release_date(release), authors(authors), next(next) {};
};

void push_front(Track*& head, Track* data)
{
	data->next = head;
	head = data;
}

void printAll(Track* head)
{
	Track* tgt = head;
	while (tgt)
	{
		std::cout << tgt->id << " " << tgt->performer << " " << tgt->release_date << " " << tgt->authors << "\n";
		tgt = tgt->next;
	}
}

Track* tracksThatYear(Track* head, int year)
{
	Track* newList = nullptr;

	Track* tgt = head;
	while (tgt)
	{
		if (tgt->release_date == year)
		{
			Track* newTrack = new Track(tgt->id, tgt->performer, tgt->name, tgt->release_date, tgt->authors);
			push_front(newList, newTrack);
		}

		tgt = tgt->next;
	}

	return newList;
}


bool isAnAuthor(Track* head, int performer_Id)
{
	Track* toFind = nullptr;

	Track* tgt = head;
	while (tgt)
	{
		if (tgt->id == performer_Id)
			toFind = tgt;

		tgt = tgt->next;
	}

	if (toFind)  //znalezlismy osobe
	{
		std::stringstream ss(toFind->performer);

		std::string extractedAuthor;
		while (std::getline(ss, extractedAuthor, ','))  //sprawdzamy imiona
		{
			if (extractedAuthor == toFind->performer)
				return true;
		}
	}
	
	return false;
}

//Dla podpunku 2

struct Performer
{
	std::string name;
	int occurances;
	Performer* next;

	Performer(std::string name, int occurances, Performer* next = nullptr) : name(name), occurances(occurances), next(next) {};
};

void printAll(Performer* head)
{
	Performer* tgt = head;
	while (tgt)
	{
		std::cout << tgt->name << " " << tgt->occurances << "\n";
		tgt = tgt->next;
	}
}

void push_front(Performer*& head, Performer* data)
{
	data->next = head;
	head = data;
}

Performer* findName(Performer* head, std::string name)
{
	Performer* tgt = head;
	while (tgt)
	{
		if (tgt->name == name)
			return tgt;

		tgt = tgt->next;
	}

	return nullptr;
}

Performer* multiple(Track* head)
{
	Performer* newList = nullptr;

	Track* tgt = head;
	while (tgt)
	{
		Performer* storage = findName(newList, tgt->performer);
		if (storage)
			storage->occurances++;
		else
		{
			Performer* newPerformer = new Performer(tgt->performer, 1);
			push_front(newList, newPerformer);
		}

		tgt = tgt->next;
	}

	//w tym momencie newList jest lista wszystkich wykonawcow oraz ich ilosci wystapien
	//teraz zrobie nowa liste, z tymi ktorych wystapienia sa wieksze niz 1

	Performer* newerList = nullptr;

	Performer* tgt2 = newList;
	while (tgt2)
	{
		if (tgt2->occurances != 1)
		{
			Performer* newPerformer = new Performer(tgt2->name, tgt2->occurances);
			push_front(newerList, newPerformer);
		}

		tgt2 = tgt2->next;
	}

	return newerList;
}

int main()
{
	Track* list1 = nullptr;

	std::fstream file("dane.txt", std::ios::in);

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string buffer, performer, name, authors;
		int id, release_date;

		std::getline(ss, buffer, ',');
		id = stoi(buffer);

		ss.ignore(); std::getline(ss, performer, ',');

		ss.ignore(); std::getline(ss, name, ',');

		ss.ignore(); std::getline(ss, buffer, ',');
		release_date = stoi(buffer);

		ss.ignore(); std::getline(ss, authors);


		Track* newTrack = new Track(id, performer, name, release_date, authors);
		push_front(list1, newTrack);

		//std::cout << id << " " << performer << " " << name << " " << release_date << " " << authors << "\n";
	}

	file.close();

	//printAll(list1);
	
	Performer* list3 = multiple(list1);
	std::cout << "Zadanie 1: \n"; printAll(list3);

	Track* list2 = tracksThatYear(list1, 1955);   //drugi argument to szukany rok
	std::cout << "\n\nZadanie 2:\n";printAll(list2);

	std::cout << "\n\nZadanie 3:\n";  
	std::cout << isAnAuthor(list1, 14);  //drugi argument to ID szukanego wykonawcy
}