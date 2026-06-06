#include <cassert>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

int createFile(const std::string_view filename, const std::string_view content) {

  std::filesystem::path outDir = std::filesystem::current_path() / "output";
  std::cout << "Output dir: " << outDir << "\n";
  std::filesystem::create_directories(outDir);
  std::filesystem::path filepath = outDir / std::string(filename);
  std::cout << "Creating file: " << filepath << "\n";

  // Open a file
  std::ofstream outf{filepath};
  if (!outf) {
    std::cerr << "Could not open " << std::string(filename) << "\n";
    return 1;
  }

  outf << content;

  return 0;
}

int toJson(const std::vector<std::string> &inputs) {

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
  // loop to open and read the given files
  for (int i = 2; i < inputs.size(); i++) {
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
  std::cout << "> " << inputs[1] << ".json succesfully created.\n";
  return 0;
}

int fromJson(const std::vector<std::string> &inputs) {

  // Print out the given filenames
  std::cout << "> Input arguments: ";
  for (auto &input : inputs) {
    std::cout << input << " ";
  }
  std::cout << "\n";

  std::string JsonFileName{inputs[1]};
  JsonFileName.append(".json");

  std::ifstream inf{JsonFileName}; // open the json file
  if (!inf) {
    std::cerr << "Could not open " << JsonFileName << "\n";
    return 1;
  }

  try {
    nlohmann::json data = nlohmann::json::parse(inf);
    for (auto &entry : data) {
      createFile(entry["filename"].get<std::string>(),
                 entry["content"].get<std::string>());
    }

  } catch (const nlohmann::json::parse_error &e) {
    std::cerr << "Invalid JSON: " << e.what() << "\n";
  }

  return 0;
}

int main(int argc, char *argv[]) {

  std::vector<std::string> inputs; // input  storage
  for (int i = 1; i < argc; i++) {
    inputs.push_back(argv[i]);
  }

  if (strcmp(argv[1], "I") == 0) {
    toJson(inputs);

  } else if (strcmp(argv[1], "O") == 0) {
    fromJson(inputs);

  } else {
    std::cerr << "> Incorrect arguments.\n";
  }

  return 0;
}