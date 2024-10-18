#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

std::map<std::string, std::vector<std::string>> network;

std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void print_network(const std::string& id, int indent = 0) {
    for (int i = 0; i < indent; ++i) {
        std::cout << "..";
    }
    std::cout << id << std::endl;

    if (network.find(id) != network.end()) {
        for (const std::string& recruit : network[id]) {
            print_network(recruit, indent + 1);
        }
    }
}

int count_subnetwork(const std::string& id) {
    int count = 0;  // Start by not counting the given person themselves

    if (network.find(id) != network.end()) {
        for (const std::string& recruit : network[id]) {
            count += count_subnetwork(recruit) + 1;  // Add recruits and their recruits
        }
    }

    return count;  // Return the total count for this subnetwork, excluding the person
}

int depth_subnetwork(const std::string& id) {
    if (network.find(id) == network.end() || network[id].empty()) {
        return 1;  // No recruits or no children
    }

    int max_depth = 0;
    for (const std::string& recruit : network[id]) {
        max_depth = std::max(max_depth, depth_subnetwork(recruit));
    }
    return max_depth + 1;  // Include the current person
}


int main()
{

    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            if (network.find(id1) == network.end()) {
                network[id1] = {};
            }
            network[id1].push_back(id2);

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            if (network.find(id) == network.end()) {
                           std::cout << id << std::endl;
                       } else {
                           print_network(id);
                       }

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout << count_subnetwork(id) << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout << depth_subnetwork(id) << std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
