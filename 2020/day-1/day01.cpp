#include <fstream>
#include <iostream>
#include <vector>

int main() {
  int goal = 2020;

  std::fstream input_file("input.txt", std::ifstream::in);

  if (!input_file) {
    std::cout << "Failed to open file";
    exit(1);
  }

  std::string number;

  std::vector<int> values;
  while (std::getline(input_file, number)) {
    values.push_back(std::stoi(number));
  }
  input_file.close();

  // We want to compare the first number to the rest then and only continue
  // If we don't find it. There is no point in comparing the previous
  // values to the current one  as we have already compared these values.
  // This will reduce the time taken.
  for (size_t i = 0; i <= values.size(); i++) {
    bool found_two_sum = false;
    bool found_three_sum = false;
    for (size_t k = i; k < values.size(); k++) {
      int sum = values.at(i) + values.at(k);
      if (sum == goal) {
        std::cout << "Two sum multiple: " << values[i] * values[k] << std::endl;
        std::cout << "Value i: " << values[i] << " Values k: " << values[k]
                  << std::endl;
        found_two_sum = true;
      }
      if (found_three_sum)
        break;
      for (size_t m = i; m < values.size(); m++) {
        int three_sum = values[i] + values[k] + values[m];
        if (three_sum == goal) {
          found_three_sum = true;
          std::cout << "Three sum multiple: "
                    << values[i] * values[k] * values[m] << std::endl;

          std::cout << "Value i: " << values[i] << " Values k: " << values[k]
                    << " Values m: " << values[m] << std::endl;
          break;
        }
      }
    }
    if (found_two_sum && found_three_sum) {
      break;
    }
  }

  return 0;
}
