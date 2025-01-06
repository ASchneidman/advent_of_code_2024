#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <unordered_map>
#include <cassert>

int main() {
  std::ifstream input_file("../day8.txt");
  if (!input_file.is_open()) {
    std::cout << "Failed to read file." << std::endl;
    return -1;
  }

  std::vector<std::vector<char>> grid;
  // Maps each antenna type to each antenna position in the grid by row and col
  std::unordered_map<char, std::vector<std::pair<int, int>>> antenna_positions;
  std::string line;
  while (getline(input_file, line)) {
    grid.push_back(std::vector<char>());
    for (int col = 0; col < line.length(); col++) {
        grid[grid.size() - 1].push_back(line[col]);
        if (line[col] != '.') {
            if (antenna_positions.find(line[col]) == antenna_positions.end()) {
                antenna_positions[line[col]] = std::vector<std::pair<int, int>>();
            }
            antenna_positions[line[col]].push_back({grid.size() - 1, col});
        }
    }
  }

  std::set<std::pair<int, int>> antinodes;

  // For each pairing of a given antenna type, find the two antinodes
  for (const auto& antenna_type_to_positions : antenna_positions) {
    const char& antenna_type = antenna_type_to_positions.first;
    const std::vector<std::pair<int, int>>& positions = antenna_type_to_positions.second;

    for (int i = 0; i < positions.size(); i++) {
        const auto& row_col = positions[i];
        for (int j = i + 1; j < positions.size(); j++) {
            const auto& partner_row_col = positions[j];

            // Since positions were inserted progressing down the grid, first pos of each pair should be higher up the grid than the second pos
            assert(row_col.first <= partner_row_col.first);
            
            std::pair<int, int> up_vector = {row_col.first - partner_row_col.first, row_col.second - partner_row_col.second};
            std::pair<int, int> down_vector = {-1 * up_vector.first, -1 * up_vector.second};

            std::pair<int, int> up_antinode = {row_col.first + up_vector.first, row_col.second + up_vector.second};
            std::pair<int, int> down_antinode = {partner_row_col.first + down_vector.first, partner_row_col.second + down_vector.second};

            if (up_antinode.first >= 0 && 
                up_antinode.first < grid.size() && 
                up_antinode.second >= 0 && 
                up_antinode.second < grid[0].size()) {
                antinodes.insert({up_antinode.first, up_antinode.second});
            }
            if (down_antinode.first >= 0 && 
                down_antinode.first < grid.size() && 
                down_antinode.second >= 0 && 
                down_antinode.second < grid[0].size()) {
                antinodes.insert({down_antinode.first, down_antinode.second});
            }
        }
    }
  }

  std::cout << antinodes.size() << std::endl;
}