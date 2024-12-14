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
    // For each X, check all directions to see if it forms XMAS
    for (int row = 0; row < crossword.size(); row++) {
        std::string line = crossword[row];
        for (int column = 0; column < line.length(); column++) {
            if (line[column] != 'X') {
                continue;
            }
            // X, so check all directions for xmas
            // West
            total += (column >= 3 && (line[column - 3] == 'S' && line[column - 2] == 'A' && line[column - 1] == 'M'));
            // East
            total += (column + 3 < line.length() && (line[column + 3] == 'S' && line[column + 2] == 'A' && line[column + 1] == 'M'));
            // North
            total += (row >= 3 && (crossword[row - 3][column] == 'S' && crossword[row - 2][column] == 'A' && crossword[row - 1][column] == 'M'));
            // South
            total += (row + 3 < crossword.size() && (crossword[row + 3][column] == 'S' && crossword[row + 2][column] == 'A' && crossword[row + 1][column] == 'M'));
            // North West
            total += (row >= 3 && column >= 3) && (crossword[row - 3][column - 3] == 'S') && (crossword[row - 2][column - 2] == 'A') && (crossword[row - 1][column - 1] == 'M');
            // North East
            total += (row >= 3 && column + 3 < line.length()) && (crossword[row - 3][column + 3] == 'S') && (crossword[row - 2][column + 2] == 'A') && (crossword[row - 1][column + 1] == 'M');
            // South West
            total += (row + 3 < crossword.size() && column >= 3) && (crossword[row + 3][column - 3] == 'S') && (crossword[row + 2][column - 2] == 'A') && (crossword[row + 1][column - 1] == 'M');
            // South East
            total += (row + 3 < crossword.size() && column + 3 < line.length()) && (crossword[row + 3][column + 3] == 'S') && (crossword[row + 2][column + 2] == 'A') && (crossword[row + 1][column + 1] == 'M');
        }
    }

    std::cout << total << std::endl;
    return 0;
}