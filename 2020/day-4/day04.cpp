#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

namespace {
// Birth Yr, Issue Yr, Expiration Yr, Height, Hair Colour, Eye Colour, Passport
// ID, Country ID
std::vector<std::string> fields = {"byr", "iyr", "eyr", "hgt",
                                   "hcl", "ecl", "pid", "cid"};

std::string cm = "cm";
std::string inch = "in";
// key:value pattern
std::regex pattern("(\\w+):([#]?\\w+|\\d+)");
} // namespace

// bool flag if valid, string is contents
typedef std::pair<bool, std::string> bool_val;
typedef std::pair<std::string, std::string> key_val;
struct passport {
  std::map<std::string, bool_val> entries;
};

void valid_passports(const std::vector<passport> &all_passports);

bool is_field_valid(const key_val &key_value);
int main(int argc, char **argv) {
  std::fstream in_file((argc > 1 ? "example.txt" : "input.txt"));

  if (!in_file) {
    exit(1);
  }

  std::vector<passport> passports;
  std::string in;
  passport current_passport;

  while (std::getline(in_file, in)) {
    if (in.empty()) {
      passports.push_back(current_passport);
      //  std::cout << "Empty line. Storing current passport. Creating new one."
      //  << std::endl;
      current_passport.entries.clear();
      continue;
    }
    // std::cout <<"line: " <<in << std::endl;
    std::smatch match;
    while (std::regex_search(in, match, pattern)) {

      auto key_found = std::find(fields.begin(), fields.end(), match.str(1));
      if (key_found != fields.end()) {
           std::cout << "Found key: " << match.str(1) << std::endl;
           std::cout << "Related value: "<< match.str(2) << std::endl;
        current_passport.entries[match.str(1)] = {true, match.str(2)};
      }
      in = match.suffix().str();
    }
  }

  in_file.close();

  valid_passports(passports);
  return 0;
}

void valid_passports(const std::vector<passport> &all_passports) {

  int valid_count = 0;
  for (const auto &passport : all_passports) {
    if (passport.entries.size() == 7) {
      auto cid_entry = passport.entries.find("cid");
      if (cid_entry == passport.entries.end()) {
        valid_count++;
      }
    } else if (passport.entries.size() == 8) {
      valid_count++;
    }
  }
  std::cout << "Total Passports: " << all_passports.size() << std::endl;
  std::cout << "Valid Passports: " << valid_count << std::endl;
}

bool is_field_valid(const key_val &key_value) {

  if (key_value.first == "byr") {
    return (1920 <= std::stoi(key_value.second) &&
            std::stoi(key_value.second) <= 2002);
  } else if (key_value.first == "iyr") {
    return (2010 <= std::stoi(key_value.second) &&
            std::stoi(key_value.second) <= 2020);
  } else if (key_value.first == "eyr") {
    return (2020 <= std::stoi(key_value.second) &&
            std::stoi(key_value.second) <= 2030);
  } else if (key_value.first == "hgt") {
    std::string thing = key_value.second;
    size_t metric = key_value.second.find(cm);
    if (metric != std::string::npos) {
      thing.erase(metric, thing.size());
      return (150 <= std::stoi(thing) && std::stoi(thing) <= 193);
    }

    metric = key_value.second.find(inch);
    if (metric != std::string::npos) {
      thing.erase(metric, thing.size());
      return (59 <= std::stoi(thing) && std::stoi(thing) <= 76);
    }
  } else if (key_value.first == "hcl") {

  } else if (key_value.first == "ecl") {

  } else if (key_value.first == "pid") {

  } else if (key_value.first == "cid") {
    return true;
  }

  return false;
}
