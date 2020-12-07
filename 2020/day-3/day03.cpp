#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef std::pair<int, int> descent;
int how_many_trees(std::vector<std::vector<bool>> &hill, const descent &slope);

int main(int argc, char *argv[]) {

  std::ifstream in_file((argc > 1 ? "example.txt" : "input.txt"));

  if (!in_file) {
    exit(1);
  }

  std::vector<std::vector<bool>> slope;

  std::string in;
  while (std::getline(in_file, in)) {
    std::vector<bool> row;
    for (const auto &item : in) {
      (item == '#' ? row.push_back(true) : row.push_back(false));
    }
    slope.push_back(row);
  }

  in_file.close();

  // Dumb arrays need 3 braces for pair list initialisers
  std::array<descent, 5> list_slopes = {
      {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}}};

  long total_trees = 1;

  for (int i = 0; i < list_slopes.size(); i++) {
    int trees = how_many_trees(slope, list_slopes[i]);

    std::cout << "Slope: {" << list_slopes[i].first << ", "
              << list_slopes[i].second << "} "
              << " Trees: " << trees << std::endl;
    total_trees = total_trees * trees;
  }

  std::cout << "Total trees encountered: " << total_trees << std::endl;
  return 0;
}

int how_many_trees(std::vector<std::vector<bool>> &hill, const descent &slope) {

  int trees = 0;
  int hill_size = hill.size() - 1;
  int row_size = hill.front().size();
  descent pos{0, 0};
  std::cout << "Height of hill: " << hill_size
            << " Length of rows: " << row_size << std::endl;

  while (pos.second < hill_size) {
    pos.first = (pos.first + slope.first) % (row_size);
    pos.second = pos.second + slope.second;

    if (hill[pos.second][pos.first]) {
      trees++;
    }
  }

  return trees;
}
