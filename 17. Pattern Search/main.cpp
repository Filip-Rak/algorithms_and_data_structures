#include <iostream>
#include <list> //uzywana do przechowywania wynikow

#define ALPHABET 256

int advanceState(std::string pattern, int patternLength, int state, int j)
{
    if (state < patternLength&& j == pattern[state])    //jezeli prawda, zwieksz stan o 1
        return state + 1;

    for (int i = state; i > 0; i--) //szuka najdluzszego prefixu, becadego suffixem. Powinno przyspieszyc wyszukiwanie, chyba
    {
        if (pattern[i - 1] == j)
        {
            int j = 0;
            for (j = 0; j < i - 1; j++)
            {
                if (pattern[j] != pattern[state - i + 1 + j])
                    break;
            }

            if (j == i - 1)
                return i;
        }
    }

    return 0;
}

void fillStates(const std::string pattern, int** states, int patternLength)
{
    for (int i = 0; i < patternLength + 1; i++)
    {
        for (int j = 0; j < ALPHABET; ++j)
            states[i][j] = advanceState(pattern, patternLength, i, j);
    }
}

std::list<int> findPattern(const std::string text, const std::string pattern) 
{
    int patternLength = pattern.length();   //przepisanie do int, by pozbyc sie bezsensownych warningow od VS
    int textLength = text.length();

    int** states = new int* [patternLength + 1];    //tworzneie masyzny stanowej
    for (int i = 0; i <= patternLength; i++)
        states[i] = new int[ALPHABET];

    fillStates(pattern, states, patternLength); //Uzupelnienie maszyny stanowej wartosciami

    std::list<int> indices; //lista przechowujaca wyniki
    int current = 0;   

    for (int i = 0; i < textLength; i++)    //Przepusc tekst przez masyzne stanowa
    {
        current = states[current][text[i]];
        if (current == patternLength)
            indices.push_back(i - patternLength + 1);
    }

    for (int i = 0; i < patternLength + 1; i++) //zwolnienie pamieci dynamicznej
        delete[] states[i];

    delete[] states;

    return indices; //zwrot wynikow
}

int main() 
{
    std::string text = "abababacaba";
    std::string pattern = "ababaca";

    std::list<int> result = findPattern(text, pattern); //funkcja szukajaca indeksy
    for (int i : result)    //wypisyanie wynikow
        std::cout << "INDEX: " << i << "\n";
}
