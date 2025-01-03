#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

void recursive_all_evaluations(const std::vector<uint64_t>& values, size_t index, std::vector<uint64_t>& results, uint64_t total) {
    if (index == values.size() - 1) {
        results.push_back(total);
        return;
    };

    recursive_all_evaluations(values, index + 1, results, total + values[index + 1]);
    recursive_all_evaluations(values, index + 1, results, total * values[index + 1]);
}

int main() {
  std::ifstream input_file("../day7.txt");
  if (!input_file.is_open()) {
    std::cout << "Failed to read file." << std::endl;
    return -1;
  }

  uint64_t total = 0;
  std::string line;
  while (getline(input_file, line)) {
    char* endptr; 
    uint64_t target = strtoull(line.substr(0, line.find(':')).c_str(), &endptr, 10);

    std::vector<uint64_t> nums;
    auto current_num_index = line.find_first_of(' ') + 1;
    while (true) {
        auto next = line.find_first_of(' ', current_num_index + 1);
        nums.push_back(atoi(line.substr(current_num_index, next - current_num_index).c_str()));
        if (next == std::string::npos) {
            break;
        }
        current_num_index = next + 1;
    }

    uint64_t result_size = std::exp2(nums.size() - 1);
    std::vector<uint64_t> results;
    results.reserve(result_size);

    recursive_all_evaluations(nums, 0, results, nums[0]);
    for (auto result : results) {
        if (result == target) {
            total += target;
            break;
        }
    }
  }

  std::cout << total << std::endl;
}