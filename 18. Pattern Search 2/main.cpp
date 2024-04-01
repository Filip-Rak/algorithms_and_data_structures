#include <iostream>

int main()
{
    std::string text = "abababacaba", pattern = "ababaca";

    int patternLength = (int)pattern.size();
    int** states = new int* [patternLength + 1];
    for (int i = 0; i <= patternLength; i++) 
    {
        states[i] = new int[256]; // 256 dla wszystkich mo¿liwych znaków ASCII
        std::fill(states[i], states[i] + 256, 0);
    }

    for (int i = 0; i < patternLength; i++) 
    {
        for (int c = 0; c < 256; c++) 
        { // Iteracja przez wszystkie znaki ASCII
            if (c == pattern[i])
                states[i][c] = i + 1; // Przejœcie do nastêpnego stanu
            else
                states[i][c] = states[0][c]; // Pozostanie w obecnym stanie
        }
    }
    states[patternLength][pattern[patternLength - 1]] = patternLength;

    int state = 0;
    for (int i = 0; i < text.size(); i++) {
        state = states[state][text[i]];
        if (state == patternLength) {
            std::cout << "Wzorzec znaleziony na pozycji " << i - patternLength + 1 << std::endl;
        }
    }


}