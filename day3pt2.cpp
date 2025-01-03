include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

int main() {
  std::ifstream input_file("../day3.txt");
  if (!input_file.is_open()) {
    std::cout << "Failed to read file." << std::endl;
    return -1;
  }

  std::stringstream buffer;
  buffer << input_file.rdbuf();
  std::string corrupted_memory = buffer.str();

  std::regex mul("do\\(\\)|don't\\(\\)|mul\\([1-9]\\d*,[1-9]\\d*\\)");

  auto words_begin = std::sregex_iterator(corrupted_memory.begin(),
                                          corrupted_memory.end(), mul);
  auto words_end = std::sregex_iterator();
  int total = 0;
  bool ignore = false;
  for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
    std::smatch match = *i;
    std::string match_str = match.str();
    std::cout << match_str << '\n';

    if (match_str == "do()") {
      ignore = false;
      continue;
    } else if (match_str == "don't()") {
      ignore = true;
      continue;
    }
    if (ignore) {
      continue;
    }

    std::regex number("[1-9]\\d*");
    auto numbers_begin =
        std::sregex_iterator(match_str.begin(), match_str.end(), number);
    int numbers[2];
    int index = 0;
    for (std::sregex_iterator j = numbers_begin; j != std::sregex_iterator();
         ++j) {
      std::smatch number_match = *j;
      numbers[index] = atoi(number_match.str().c_str());
      index += 1;
    }
    total += (numbers[0] * numbers[1]);
  }

  std::cout << total << std::endl;

  return 0;
}
