#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <optional>

bool is_safe_recursive(std::optional<bool> ascending, bool removal_performed, const int* line, size_t length, size_t current_index, size_t next_index) {
    if (current_index >= length - 1) {
        return true;
    }
    if (!ascending.has_value()) {
        return is_safe_recursive(true, false, line, length, 0, 1)
        || is_safe_recursive(false, false, line, length, 0, 1);
    }
    bool is_safe = false;
    if (ascending.value()) {
        is_safe = line[current_index] < line[next_index] && line[next_index] - line[current_index] <= 3;
    } else {
        is_safe = line[current_index] > line[next_index] && line[current_index] - line[next_index] <= 3;
    }
    if (is_safe) {
        // try the rest
        return is_safe_recursive(ascending.value(), removal_performed, line, length, next_index, next_index + 1);
    }

    if (removal_performed) {
        // Already tried a removal, so fail
        return false;
    }
    // Try removing this one
    if (current_index == 0) {
        // Try removing the current one or next one, can only compare against this one
        if (is_safe_recursive(ascending.value(), true, line, length, next_index, next_index + 1)) {
            return true;
        }
        // Also try removing the next one if possible
        // If removing the next one is the last one, its possible
        if (next_index + 1 >= length) {
            return true;
        }
        return is_safe_recursive(ascending.value(), true, line, length, current_index, next_index + 1);
    }
    // Try removing this one or the next one
    if (is_safe_recursive(ascending.value(), true, line, length, current_index - 1, next_index)) {
        // current one
        return true;
    }
    // Try removing next one if possible
    if (next_index + 1 >= length) {
        return true;
    }
    return is_safe_recursive(ascending.value(), true, line, length, current_index, next_index + 1);
}

int main() {
    std::ifstream input_file("/home/alex/advent_of_code/2024/day2.txt");
    if (input_file.is_open()) {
        std::string line;
        int num_safe = 0;
        while (getline(input_file, line)) {
            std::vector<int> nums;
            std::string line_copy = line;
            while (true) {
                nums.push_back(atoi(line_copy.substr(0, line_copy.find_first_of(' ')).c_str()));
                if (line_copy.find_first_of(' ') == std::string::npos) {
                    break;
                }
                line_copy = line_copy.substr(line_copy.find_first_of(' ') + 1);
            }
            num_safe += is_safe_recursive(std::nullopt, false, nums.data(), nums.size(), 0, 1);
        }
        std::cout << num_safe << std::endl;
    } else {
        std::cout << "Failed to open file" << std::endl;
    }
}