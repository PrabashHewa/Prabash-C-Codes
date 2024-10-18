#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstdlib>

int main() {
    std::string filename;
    std::map<std::string, int> scores;


    std::cout << "Input file: ";
    std::cin >> filename;

    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error! The file " << filename << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }


    std::string line;
    while (std::getline(infile, line)) {
        size_t colon_pos = line.find(':');
        if (colon_pos == std::string::npos) {

            continue;
        }

        std::string player_name = line.substr(0, colon_pos);
        int points = std::stoi(line.substr(colon_pos + 1));

        scores[player_name] += points;
    }


    infile.close();

    std::cout << "Final scores:" << std::endl;
    for (const auto& entry : scores) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }

    return EXIT_SUCCESS;
}
