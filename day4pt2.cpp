#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <regex>

int main() {
    std::ifstream input_file("/home/alex/advent_of_code/2024/day4.txt");
    if (!input_file.is_open()) {
        std::cout << "Failed to read file." << std::endl;
        return -1;
    }

    std::vector<std::string> crossword;
    {
        std::string line;
        while (getline(input_file, line)) {
            crossword.push_back(line);
        }
    }

    int total = 0;
    // For each A, check NW, SE to form MAS and NE, SW to form MAS in any order
    for (int row = 1; row < crossword.size() - 1; row++) {
        std::string line = crossword[row];
        for (int column = 1; column < line.length() - 1; column++) {
            if (line[column] != 'A') {
                continue;
            }
            /*
            if (row == 0 || row == crossword.size() - 1 || column == 0 || column == line.length() - 1) {
                continue;
            }
            */
            char NW = crossword[row - 1][column - 1];
            char NE = crossword[row - 1][column + 1];
            char SE = crossword[row + 1][column + 1];
            char SW = crossword[row + 1][column - 1];

            total += (
                ((NW == 'M' && SE == 'S') || (NW == 'S' && SE == 'M')) &&
                ((NE == 'M' && SW == 'S') || (NE == 'S' && SW == 'M'))
            );
        }
    }

    std::cout << total << std::endl;
    return 0;
}