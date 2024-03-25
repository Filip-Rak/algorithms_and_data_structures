#include <iostream>

struct Butelka {
private:
	static int ilosc;

public:
	int id, ilosc_wody;
	std::string kolor;

	Butelka(std::string kolor, int ilosc_wody) : kolor(kolor), ilosc_wody(ilosc_wody) {
		this->id = ilosc++;
	}
};

int Butelka::ilosc = 0;

struct Para {
	Butelka* a, * b;
	Para(Butelka* a = nullptr, Butelka* b = nullptr) : a(a), b(b) {}
};


Para* sparuj(Butelka* arr, int size)
{
	Para* pary = new Para[size / 2];


	bool* taken = new bool[size];
	for (int i = 0; i < size; i++) taken[i] = false;

	for (int i = 0; i < size / 2; i++)
	{
		pary[i].a = &arr[i];
		taken[i] = true;

		for (int j = 0; j < size; j++)
		{
			if (!taken[j])
			{
				if (arr[j].kolor != pary[i].a->kolor)
				{
					if (arr[j].ilosc_wody == pary[i].a->ilosc_wody)
					{
						pary[i].b = &arr[j];
						taken[j] = true;
						break;
					}
				}
			}
		}
	}


	return pary;
}

std::ostream& operator<< (std::ostream& out, Para p)
{
	out << "Woda: " << p.a->ilosc_wody << "\tKolory: ";
	out << p.a->kolor << " " << p.b->kolor << "\tID: " << p.a->id << " " << p.b->id;

	return out;
}


int main()
{
	Butelka b_arr[] = {
		Butelka("niebieski", 10),	//id 0  //id w struct jest przypisywane poczawszy od zera
		Butelka("czerwony", 30),	//id 1
		Butelka("czerwony", 20),	//id 2
		Butelka("niebieski", 20),	//id 3
		Butelka("czerwony", 10),	//id 4
		Butelka("niebieski", 30),	//id 5
	};

	int arr_size = sizeof(b_arr) / sizeof(Butelka);
	Para* sparowane = sparuj(b_arr, arr_size);


	for (int i = 0; i < arr_size / 2; i++)
		std::cout << sparowane[i] << "\n";
}