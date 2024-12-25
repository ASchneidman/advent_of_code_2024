#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <vector>

int main() {
  std::ifstream input_file("../day6.txt");
  if (!input_file.is_open()) {
    std::cout << "Failed to read file." << std::endl;
    return -1;
  }

  std::vector<std::vector<char>> grid;
  int x = 0;
  int guard_x = 0;
  int guard_y = 0;
  std::string line;
  while (getline(input_file, line)) {
    int y = 0;
    std::vector<char> row;
    for (char c : line) {
      row.push_back(c);
      if (c == '^' || c == '>' || c == 'v' || c == '<') {
        guard_x = x;
        guard_y = y;
      }
      y += 1;
    }
    grid.push_back(row);
    x += 1;
  }

  std::set<std::pair<int, int>> visited;
  while (guard_x >= 0 && guard_x < grid.size() && guard_y >= 0 &&
         guard_y < grid[0].size()) {
    std::cout << guard_x << " " << guard_y << std::endl;
    visited.insert({guard_x, guard_y});
    // Find next position
    while (true) {
      int maybe_next_x = 0;
      int maybe_next_y = 0;
      if (grid[guard_x][guard_y] == '^') {
        maybe_next_x = guard_x - 1;
        maybe_next_y = guard_y;
      }
      if (grid[guard_x][guard_y] == '>') {
        maybe_next_x = guard_x;
        maybe_next_y = guard_y + 1;
      }
      if (grid[guard_x][guard_y] == 'v') {
        maybe_next_x = guard_x + 1;
        maybe_next_y = guard_y;
      }
      if (grid[guard_x][guard_y] == '<') {
        maybe_next_x = guard_x;
        maybe_next_y = guard_y - 1;
      }

      if (maybe_next_x < 0 || maybe_next_x >= grid.size() || maybe_next_y < 0 ||
          maybe_next_y >= grid[0].size()) {
        // Done!
        guard_x = maybe_next_x;
        guard_y = maybe_next_y;
        break;
      }

      if (grid[maybe_next_x][maybe_next_y] == '#') {
        // Rotate 90 degrees right
        if (grid[guard_x][guard_y] == '^') {
          grid[guard_x][guard_y] = '>';
        } else if (grid[guard_x][guard_y] == '>') {
          grid[guard_x][guard_y] = 'v';
        } else if (grid[guard_x][guard_y] == 'v') {
          grid[guard_x][guard_y] = '<';
        } else if (grid[guard_x][guard_y] == '<') {
          grid[guard_x][guard_y] = '^';
        }
      } else {
        // It's open, so move
        std::swap(grid[guard_x][guard_y], grid[maybe_next_x][maybe_next_y]);
        guard_x = maybe_next_x;
        guard_y = maybe_next_y;
        // Done!
        break;
      }
    }
  }

  std::cout << visited.size() << std::endl;
}
