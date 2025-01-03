#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <vector>

int main() {
  std::ifstream input_file("../day5.txt");
  if (!input_file.is_open()) {
    std::cout << "Failed to read file." << std::endl;
    return -1;
  }

  std::unordered_map<int, std::set<int>> less_thans;
  std::vector<std::vector<int>> requests;
  std::string line;
  bool ordering = true;
  while (getline(input_file, line)) {
    if (line == "") {
      ordering = false;
      continue;
    }
    if (ordering) {
      auto pos = line.find("|");
      int first = atoi(line.substr(0, pos).c_str());
      int second = atoi(line.substr(pos + 1).c_str());
      if (less_thans.find(first) == less_thans.end()) {
        less_thans[first] = std::set<int>();
      }
      less_thans[first].insert(second);
    } else {
      std::vector<int> nums;
      std::regex num_regex("[1-9][0-9]*");
      auto nums_begin =
          std::sregex_iterator(line.begin(), line.end(), num_regex);
      for (auto i = nums_begin; i != std::sregex_iterator(); ++i) {
        nums.push_back(atoi((i->str()).c_str()));
      }
      requests.push_back(nums);
    }
  }

  int total = 0;
  for (auto &request : requests) {
    bool unsorted = false;
    bool bad_entry = false;
    do {
      unsorted = false;
      for (int i = 0; i < request.size(); i++) {
        for (int j = i + 1; j < request.size(); j++) {
          if (less_thans.find(request[j]) == less_thans.end()) {
            continue;
          }
          if (less_thans[request[j]].find(request[i]) !=
              less_thans[request[j]].end()) {
            unsorted = true;
            bad_entry = true;
            // need to be re ordered
            std::swap(request[i], request[j]);
            // repeat from the start
            break;
          }
        }
        if (unsorted) {
          // repeat from the start
          break;
        }
      }
    } while (unsorted);

    if (bad_entry) {
      total += request[request.size() / 2];
    }
  }
  std::cout << total << std::endl;
}
