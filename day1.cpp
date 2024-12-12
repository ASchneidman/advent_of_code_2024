#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

void line_to_int_pairs(const std::string& line, int* a, int* b) {
    auto space = line.find_first_of("   ");
    if (space == std::string::npos) {
        throw std::runtime_error("Invalid line: " + line);
    }
    std::string a_str = line.substr(0, space);
    *a = atoi(a_str.c_str());
    std::string b_str = line.substr(space + 3);
    *b = atoi(b_str.c_str());
}

int main() {
    std::ifstream input_file("/home/alex/advent_of_code/2024/day1.txt");
    if (input_file.is_open()) {
        std::string line;
        std::vector<int> a;
        std::vector<int> b;
        while (getline(input_file, line)) {
            int a_sample = 0;
            int b_sample = 0;
            line_to_int_pairs(line, &a_sample, &b_sample);
            a.push_back(a_sample);
            b.push_back(b_sample);
        }
        input_file.close();

        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        int total = 0;
        for (int i = 0; i < a.size(); i++) {
            total += std::max(a[i], b[i]) - std::min(a[i], b[i]);
        }
        std::cout << total << std::endl;
    }
    return 0;
}