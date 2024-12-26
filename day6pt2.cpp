#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <vector>

std::string hash_pos(int x, int y, char direction) {
  return std::to_string(x) + "," + std::to_string(y) + "," + direction;
}

bool escapes(int x, int y, std::vector<std::vector<char>> grid) {
  std::set<std::string> positions;
  while (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size()) {
    if (positions.find(hash_pos(x, y, grid[x][y])) != positions.end()) {
      std::cout << "stuck at " << x << " " << y << std::endl;
      // Loop detected
      return false;
    }
    positions.insert(hash_pos(x, y, grid[x][y]));
    // Find next position
    while (true) {
      int maybe_next_x = 0;
      int maybe_next_y = 0;
      if (grid[x][y] == '^') {
        maybe_next_x = x - 1;
        maybe_next_y = y;
      }
      if (grid[x][y] == '>') {
        maybe_next_x = x;
        maybe_next_y = y + 1;
      }
      if (grid[x][y] == 'v') {
        maybe_next_x = x + 1;
        maybe_next_y = y;
      }
      if (grid[x][y] == '<') {
        maybe_next_x = x;
        maybe_next_y = y - 1;
      }

      if (maybe_next_x < 0 || maybe_next_x >= grid.size() || maybe_next_y < 0 ||
          maybe_next_y >= grid[0].size()) {
        // Done!
        x = maybe_next_x;
        y = maybe_next_y;
        break;
      }

      if (grid[maybe_next_x][maybe_next_y] == '#') {
        // Rotate 90 degrees right
        if (grid[x][y] == '^') {
          grid[x][y] = '>';
        } else if (grid[x][y] == '>') {
          grid[x][y] = 'v';
        } else if (grid[x][y] == 'v') {
          grid[x][y] = '<';
        } else if (grid[x][y] == '<') {
          grid[x][y] = '^';
        }
      } else {
        // It's open, so move
        std::swap(grid[x][y], grid[maybe_next_x][maybe_next_y]);
        x = maybe_next_x;
        y = maybe_next_y;
        // Done!
        break;
      }
    }
  }

  return true;
}

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

  int num_loops = 0;
  for (int pos = 0; pos < grid.size() * grid[0].size(); pos++) {
    auto grid_copy = grid;
    int x = pos / grid[0].size();
    int y = pos % grid[0].size();
    std::cout << x << " " << y << std::endl;
    if (grid_copy[x][y] == '.') {
      grid_copy[x][y] = '#';
      if (!escapes(guard_x, guard_y, grid_copy)) {
        num_loops += 1;
      }
    }
  }
  std::cout << num_loops << std::endl;
  return 0;
}
