/* Chain stores
 *
 * Desc:
 *   This program reads input data concerning chain stores from an input
 * file, the lines of which are of the form:
 * chain_store;store_location;product_name;product_price.
 * The program checks if each line consists of the abovementioned four
 * data fields.
 *   The data written in the file is collected into an appropriate data
 * structure consisting of STL containers and structs. After that the user
 * can make searches for the data structure by using the commands
 * chains, stores, selection, cheapest, and products. These commands
 * have a varying number of parameters, and the program checks if the
 * user gave a correct number of parameters and if the given parameters
 * (chain store, store location, product name) can be found from the data
 * structure.
 *   The program terminates with the command quit.
 *
 * Program author (Fill with your own info)
 * Name: Prabash Madusanka
 *
 *
 */

// main.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>

// Struct to hold product information
struct Product {
    std::string product_name;
    double price;
};

// Data structure: Map from chain -> store -> vector of products
std::map<std::string, std::map<std::string, std::vector<Product>>> data;

// Helper function to split a string by a delimiter
std::vector<std::string> split(const std::string &s, const char delimiter, bool ignore_empty = false) {
    std::vector<std::string> result;
    std::string tmp = s;

    while (tmp.find(delimiter) != std::string::npos) {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if (!(ignore_empty && new_part.empty())) {
            result.push_back(new_part);
        }
    }
    if (!(ignore_empty && tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}

// Function to read the input file and store data into the map
bool readDataFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: the input file cannot be opened" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        auto fields = split(line, ';');
        if (fields.size() != 4) {
            std::cerr << "Error: the input file has an erroneous line" << std::endl;
            return false;
        }

        std::string chain = fields[0];
        std::string store = fields[1];
        std::string product_name = fields[2];
        std::string price_str = fields[3];
        double price;

        try {
            price = (price_str == "out-of-stock") ? -1 : std::stod(price_str);
        } catch (const std::invalid_argument &) {
            std::cerr << "Error: the input file has an erroneous line" << std::endl;
            return false;
        }

        auto &store_products = data[chain][store];
        auto it = std::find_if(store_products.begin(), store_products.end(),
            [&product_name](const Product &p) { return p.product_name == product_name; });

        if (it != store_products.end()) {

            it->price = price;
        } else {

            store_products.push_back({product_name, price});
        }
    }

    return true;
}


// Function to handle the 'chains' command
void handleChains() {
    std::set<std::string> chains;
    for (const auto &entry : data) {
        chains.insert(entry.first);
    }
    for (const auto &chain : chains) {
        std::cout << chain << std::endl;
    }
}


// Function to handle the 'stores ' command
void handleStores(const std::string &chain_name) {
    if (data.find(chain_name) == data.end()) {
        std::cerr << "Error: unknown chain name" << std::endl;
        return;
    }

    std::set<std::string> stores;
    for (const auto &store : data[chain_name]) {
        stores.insert(store.first);
    }

    for (const auto &store : stores) {
        std::cout << store << std::endl;
    }
}

// Function to handle the 'selection ' command
void handleSelection(const std::string &chain_name, const std::string &store_location) {
    if (data.find(chain_name) == data.end()) {
        std::cerr << "Error: unknown chain name" << std::endl;
        return;
    }

    if (data[chain_name].find(store_location) == data[chain_name].end()) {
        std::cerr << "Error: unknown store" << std::endl;
        return;
    }

    auto &products = data[chain_name][store_location];
    std::map<std::string, double> latest_products;

    for (const auto &product : products) {
        latest_products[product.product_name] = product.price;
    }

    for (const auto &product : latest_products) {
        if (product.second == -1) {
            std::cout << product.first << " out of stock" << std::endl;
        } else {
            std::cout << product.first << " " << std::fixed << std::setprecision(2) << product.second << std::endl;
        }
    }
}


// Function to handle the 'products' command
void handleProducts() {
    std::set<std::string> all_products;
    for (const auto &chain_entry : data) {
        for (const auto &store_entry : chain_entry.second) {
            for (const auto &product : store_entry.second) {
                all_products.insert(product.product_name);
            }
        }
    }

    for (const auto &product_name : all_products) {
        std::cout << product_name << std::endl;
    }
}

// Function to handle the 'cheapest ' command
void handleCheapest(const std::string &product_name) {
        double lowest_price = -1;
        std::vector<std::pair<std::string, std::string>> cheapest_locations;

        bool product_found = false;
        bool out_of_stock_everywhere = true;


        for (const auto &chain_entry : data) {
            const auto &chain = chain_entry.first;
            for (const auto &store_entry : chain_entry.second) {
                const auto &store = store_entry.first;


                std::map<std::string, double> latest_product_prices;

                for (const auto &product : store_entry.second) {
                    latest_product_prices[product.product_name] = product.price;
                }


                if (latest_product_prices.find(product_name) != latest_product_prices.end()) {
                    double price = latest_product_prices[product_name];
                    product_found = true;


                    if (price != -1) {
                        out_of_stock_everywhere = false;

                        if (lowest_price == -1 || price < lowest_price) {
                            lowest_price = price;
                            cheapest_locations.clear();
                            cheapest_locations.push_back({chain, store});
                        } else if (price == lowest_price) {

                            cheapest_locations.push_back({chain, store});
                        }
                    }
                }
            }
        }


        if (!product_found) {
            std::cout << "The product is not part of product selection" << std::endl;
        } else if (out_of_stock_everywhere) {
            std::cout << "The product is temporarily out of stock everywhere" << std::endl;
        } else {

            std::cout << std::fixed << std::setprecision(2) << lowest_price << " euros" << std::endl;

            std::sort(cheapest_locations.begin(), cheapest_locations.end());

            for (const auto &location : cheapest_locations) {
                std::cout << location.first << " " << location.second << std::endl;
            }
        }
    }



void handleCommands() {
    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);
        std::vector<std::string> parts = split(command, ' ');

        if (parts.empty()) {
            std::cerr << "Error: empty command" << std::endl;
            continue;
        }

        if (parts[0] == "quit") {
            break;
        } else if (parts[0] == "chains") {
            if (parts.size() == 1) {
                handleChains();
            } else {
                std::cerr << "Error: error in command chains" << std::endl;
            }
        } else if (parts[0] == "stores") {
            if (parts.size() == 2) {
                handleStores(parts[1]);
            } else {
                std::cerr << "Error: error in command stores" << std::endl;
            }
        } else if (parts[0] == "selection") {
            if (parts.size() == 3) {
                handleSelection(parts[1], parts[2]);
            } else {
                std::cerr << "Error: error in command selection" << std::endl;
            }
        } else if (parts[0] == "cheapest") {
            if (parts.size() == 2) {
                handleCheapest(parts[1]);
            } else {
                std::cerr << "Error: error in command cheapest" << std::endl;
            }
        } else if (parts[0] == "products") {
            if (parts.size() == 1) {
                handleProducts();
            } else {
                std::cerr << "Error: error in command products" << std::endl;
            }
        } else {
            std::cerr << "Error: unknown command: " << parts[0] << std::endl;
        }
    }
}


using namespace std;

int main() {

    string filename = "" ;
    cout <<"Input file: ";
    cin >> filename ;
    cin.ignore();


    if (!readDataFromFile(filename)) {
        return 1;
    }

        handleCommands();

    return 0;
}
