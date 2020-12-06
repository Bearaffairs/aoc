#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

namespace {
// Match (digit)-(digit) (Some Char) : (password)
// We don't want to match whitespace for P2 which will throw out
// the indexing by one if we decrement. If we include the whitespace, no need 
// to decrement...
std::string pat = "^(\\d+)-(\\d+)\\s+([A-Za-z]+):\\s+(\\w+)$";
std::regex pattern(pat);
}; // namespace
bool valid_password(const std::string &line, int *part_1_count,
                    int *part_2_count);

int main() {
  std::fstream input_file("input.txt", std::ifstream::in);

  if (!input_file) {
    exit(1);
  }

  int part_1_count = 0;
  int part_2_count = 0;
  std::string cur_line;
  while (std::getline(input_file, cur_line)) {
    valid_password(cur_line, &part_1_count, &part_2_count);
  }
  input_file.close();

  std::cout << "P1: Valid passwords: " << part_1_count << std::endl;
  std::cout << "P2: Valid passwords: " << part_2_count << std::endl;
  return 0;
}

bool valid_password(const std::string &line, int *part_1_count,
                    int *part_2_count) {
  std::smatch match;

  if (std::regex_match(line, match, pattern)) {
    std::string password = match.str(4);
    char tok = match.str(3)[0];
    int lower = std::stoi(match.str(1));
    int upper = std::stoi(match.str(2));
    int amount = std::count(password.begin(), password.end(), tok);
    // Part #1
    if (lower <= amount && amount <= upper) {
      *part_1_count += 1;
    }
    // Part #2 (XOR)
    if (password[--lower] == tok ^ password[--upper] == tok) {
      *part_2_count += 1;
    }
  }
  return true;
}
