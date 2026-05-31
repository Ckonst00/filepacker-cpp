#include <cstring>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <vector>

int toJson(const std::vector<std::string>& inputs) {
  
  // Print out the given filenames
  std::cout << "> Input arguments: ";
  for (auto &input : inputs) {
    std::cout << input << " ";
  }
  std::cout << "\n";
  
  std::string JsonFileName{inputs[1]};
  JsonFileName.append(".json");
  
  
  
  std::ofstream outf{JsonFileName}; // open the json file
  if (!outf) {
    std::cerr << "Could not open " << JsonFileName << "\n";
    return 1;
  }
  
  nlohmann::ordered_json files = nlohmann::ordered_json::array();
  
  // Inputs[0] = I
  // Inputs[1] = json filename
  for (int i = 2; i < inputs.size(); i++) { // loop to open and read the given files
    std::ifstream inf(inputs[i]);
    if (!inf) {
      std::cerr << "Could not open: " << inputs[i] << "\n";
      continue;
    }

    // parse filename to get the type
    std::string fileType = inputs[i].substr(inputs[i].find(".") + 1);

    std::stringstream ss;
    ss << inf.rdbuf(); // read the whole file to ss buffer

    nlohmann::ordered_json entry;
    entry["filename"] = inputs[i];
    entry["type"] = fileType;
    entry["content"] = ss.str();
    files.push_back(entry);
  }

  outf << files;
  return 0;
}


int main(int argc, char *argv[]) {


  std::vector<std::string> inputs; // input  storage
  for (int i = 1; i < argc; i++) {
    inputs.push_back(argv[i]);
  }

  if (strcmp(argv[1], "I") == 0) {
    toJson(inputs);
  } else {
    std::cerr << "> Incorrect arguments.\n";
  }


  return 0;
}