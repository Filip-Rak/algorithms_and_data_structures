#include <iostream>

void quick_sort(int* tab, int lewy, int prawy)
{
	if (prawy <= lewy) return;

	int i = lewy - 1, j = prawy + 1,
		pivot = tab[(lewy + prawy) / 2];

	while (1)
	{
		while (pivot > tab[++i]);
		while (pivot < tab[--j]);

		if (i <= j)
			std::swap(tab[i], tab[j]);
		else
			break;
	}

	if (j > lewy)
		quick_sort(tab, lewy, j);
	if (i < prawy)
		quick_sort(tab, i, prawy);
}


int* triplet(int* nums, int size)  //funkcja zwraca tablice trzech liczb, ktore spelniaja warunki zadania
{
	if (size < 3) return nullptr;
	quick_sort(nums, 0, size - 1);

	int max_value1 = nums[0] * nums[1] * nums[size - 1];
	int max_value2 = nums[size - 1] * nums[size - 2] * nums[size - 3];

	int* result = new int[3];
	if (max_value1 > max_value2)
	{
		result[0] = nums[0];
		result[1] = nums[1];
		result[2] = nums[size - 1];
	}
	else
	{
		result[0] = nums[size - 1];
		result[1] = nums[size - 2];
		result[2] = nums[size - 3];
	}

	return result;
}

int main()
{
	int numbers[] = { 7, 5, 4, -3, -4, 5, 3, 8, 3, -6, -2, -8, -6, -3 };
	int size = sizeof(numbers) / sizeof(int);

	int* result = triplet(numbers, size);

	std::cout << "Trojka liczb o maksymalnym iloczynie\n";
	for (int i = 0; i < 3; i++)
		std::cout << result[i] << "\n";

	std::cout << "Iloczyn: " << result[0] * result[1] * result[2];
}