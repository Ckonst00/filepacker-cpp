#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {

  std::string JsonFileName{argv[1]};
  JsonFileName.append(".json");

  std::vector<std::string> inputs; // filename storage
  for (int i = 2; i < argc; i++) {
    inputs.push_back(argv[i]); // add the filenames to inputs vector "storage"
  }

  // Print out the given filenames
  std::cout << "Input arguments: ";
  for (auto &input : inputs) {
    std::cout << input << " ";
  }
  std::cout << "\n";

  std::ofstream outf{JsonFileName}; // open the json file
  if (!outf) {
    std::cerr << "Could not open " << JsonFileName << "\n";
    return 1;
  }

  nlohmann::ordered_json files = nlohmann::ordered_json::array();

  for (auto &input : inputs) { // loop to open and read the given files
    std::ifstream inf(input);
    if (!inf) {
      std::cerr << "Could not open: " << input << "\n";
      continue;
    }

    // parse filename to get the type
    std::string fileType = input.substr(input.find(".") + 1);

    std::stringstream ss;
    ss << inf.rdbuf(); // read the whole file to ss buffer

    nlohmann::ordered_json entry;
    entry["filename"] = input;
    entry["type"] = fileType;
    entry["content"] = ss.str();
    files.push_back(entry);
  }

  outf << files;

  return 0;
}