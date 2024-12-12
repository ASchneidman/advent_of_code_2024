#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

bool is_safe(const std::string& line) {
    int last_pos = 0;
    int last_value = 0;
    bool ascending = true;
    int iteration = 0;
    while (true) {
        auto current_index = line.find_first_of(' ', last_pos);
        int current_value = atoi(line.substr(last_pos, current_index - last_pos).c_str());

        if (iteration == 0) {
            last_value = current_value;
        } else if (iteration == 1) {
            if (last_value < current_value && current_value - last_value <= 3) {
                // ascending!
            } else if (last_value > current_value && last_value - current_value <= 3) {
                // descending!
                ascending = false;
            } else {
                // equal, or differing by too much
                return false;
            }
        } else {
            bool valid_ascending = (current_value > last_value) && (current_value - last_value <= 3);
            bool valid_descending = (current_value < last_value) && (last_value - current_value <= 3);
            if ((ascending && !valid_ascending) || (!ascending && !valid_descending)) {
                return false;
            }
        }

        if (current_index == std::string::npos) {
            break;
        }
        last_value = current_value;
        last_pos = current_index + 1;
        iteration += 1;
    }
    return true;
}

int main() {
    std::ifstream input_file("/home/alex/advent_of_code/2024/day2.txt");
    if (input_file.is_open()) {
        std::string line;
        int num_safe = 0;
        while (getline(input_file, line)) {
            num_safe += is_safe(line);
        }
        std::cout << num_safe << std::endl;
    } else {
        std::cout << "Failed to open file" << std::endl;
    }
}